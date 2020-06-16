/**
 * @section LICENSE
 *
 * The MIT License
 *
 * @copyright Copyright (c) 2019 TileDB, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "write/writer_worker_v3.h"

namespace tiledb {
namespace vcf {

WriterWorkerV3::WriterWorkerV3()
    : dataset_(nullptr) {
}

void WriterWorkerV3::init(
    const TileDBVCFDataset& dataset,
    const IngestionParams& params,
    const std::vector<SampleAndIndex>& samples) {
  dataset_ = &dataset;

  for (const auto& s : samples) {
    std::unique_ptr<VCF> vcf(new VCF);
    vcf->set_max_record_buff_size(params.max_record_buffer_size);
    vcf->open(s.sample_uri, s.index_uri);
    vcfs_.push_back(std::move(vcf));
  }

  for (const auto& attr : dataset.metadata().extra_attributes)
    buffers_.extra_attrs()[attr] = Buffer();
}

const AttributeBufferSet& WriterWorkerV3::buffers() const {
  return buffers_;
}

uint64_t WriterWorkerV3::records_buffered() const {
  return records_buffered_;
}

uint64_t WriterWorkerV3::anchors_buffered() const {
  return anchors_buffered_;
}

bool WriterWorkerV3::parse(const Region& region) {
  if (!record_heap_.empty())
    throw std::runtime_error(
        "Error in parsing; record heap unexpectedly not empty.");

  region_ = region;

  // Initialize the record heap with the first record from each sample.
  const auto& metadata = dataset_->metadata();
  const uint32_t contig_offset = metadata.contig_offsets.at(region.seq_name);
  for (auto& vcf : vcfs_) {
    vcf->seek(region.seq_name, region.min);

    bcf1_t* r = vcf->curr_rec();
    if (r == nullptr) {
      // Sample has no records at this region, skip it.
      continue;
    }

    // If a record exists but it's outside the region max, skip it.
    if (static_cast<uint32_t>(r->pos) > region.max)
      continue;

    const uint32_t sample_id = metadata.sample_ids.at(vcf->sample_name());
    const uint32_t end_pos =
        contig_offset + VCF::get_end_pos(vcf->hdr(), r, &val_);
    const uint32_t start_pos = contig_offset + r->pos;
    const uint32_t length = end_pos - start_pos + 1;

    const unsigned num_anchors =
        length > 1 ? (end_pos - start_pos - 1) / metadata.anchor_gap : 0;

    record_heap_.insert(
        vcf.get(),
        RecordHeapV3::NodeType::Record,
        r,
        start_pos,
        sample_id,
        num_anchors == 0 ? true : false);

    for (unsigned i = 1; i <= num_anchors; i++) {
      uint32_t anchor_start = start_pos + i * metadata.anchor_gap;
      record_heap_.insert(
          vcf.get(),
          RecordHeapV3::NodeType::Anchor,
          r,
          anchor_start,
          sample_id,
          i == num_anchors);
      // Sanity check
      if (anchor_start >= end_pos)
        throw std::runtime_error("Ingestion error; anchor >= end.");
    }
  }

  // Start buffering records (which can possibly be incomplete if the buffers
  // run out of space).
  return resume();
}

bool WriterWorkerV3::resume() {
  buffers_.clear();
  records_buffered_ = 0;
  anchors_buffered_ = 0;

  const auto& metadata = dataset_->metadata();
  const uint32_t contig_offset = metadata.contig_offsets.at(region_.seq_name);
  while (!record_heap_.empty()) {
    const RecordHeapV3::Node& top = record_heap_.top();
    const uint32_t sample_id = top.sample_id;
    VCF* vcf = top.vcf;

    // Copy the record into the buffers. If the record caused the buffers to
    // exceed the max memory allocation, we'll stop processing at this record.
    bool overflowed = !buffer_record(contig_offset, top);

    record_heap_.pop();
    if (top.end_node && vcf->is_open() && vcf->next()) {
      bcf1_t* r = vcf->curr_rec();

      const uint32_t local_end_pos = VCF::get_end_pos(vcf->hdr(), r, &val_);
      if (local_end_pos <= region_.max) {
        const uint32_t end_pos = contig_offset + local_end_pos;
        const uint32_t start_pos = contig_offset + r->pos;
        const uint32_t length = end_pos - start_pos + 1;

        const unsigned num_anchors =
            length > 1 ? (end_pos - start_pos - 1) / metadata.anchor_gap : 0;

        record_heap_.insert(
            vcf,
            RecordHeapV3::NodeType::Record,
            r,
            start_pos,
            sample_id,
            num_anchors == 0 ? true : false);

        for (unsigned i = 1; i <= num_anchors; i++) {
          uint32_t anchor_start = start_pos + i * metadata.anchor_gap;
          record_heap_.insert(
              vcf,
              RecordHeapV3::NodeType::Anchor,
              r,
              anchor_start,
              sample_id,
              i == num_anchors);
          // Sanity check
          if (anchor_start >= end_pos)
            throw std::runtime_error("Ingestion error; anchor >= end.");
        }
      }
    }

    if (overflowed)
      return false;
  }

  return true;
}

bool WriterWorkerV3::buffer_record(
    uint32_t contig_offset, const RecordHeapV3::Node& node) {
  VCF* vcf = node.vcf;
  bcf1_t* r = node.record;
  bcf_hdr_t* hdr = vcf->hdr();
  const std::string contig = vcf->contig_name();
  const uint32_t row = node.sample_id;
  const uint32_t col = node.sort_start_pos;
  const uint32_t pos = contig_offset + r->pos;
  const uint32_t end_pos = contig_offset + VCF::get_end_pos(hdr, r, &val_);

  buffers_.sample().append(&row, sizeof(uint32_t));
  buffers_.start_pos().append(&col, sizeof(uint32_t));
  buffers_.qual().append(&r->qual, sizeof(float));
  buffers_.real_start_pos().append(&pos, sizeof(uint32_t));
  buffers_.end_pos().append(&end_pos, sizeof(uint32_t));

  // ID string (include null terminator)
  const size_t id_size = strlen(r->d.id) + 1;
  buffers_.id().offsets().push_back(buffers_.id().size());
  buffers_.id().append(r->d.id, id_size);

  // Alleles
  buffer_alleles(r, &buffers_.alleles());

  // Filter IDs
  buffers_.filter_ids().offsets().push_back(buffers_.filter_ids().size());
  buffers_.filter_ids().append(&(r->d.n_flt), sizeof(int32_t));
  buffers_.filter_ids().append(r->d.flt, sizeof(int32_t) * r->d.n_flt);

  // Start expecting info on all the extra buffers
  for (auto& it : buffers_.extra_attrs())
    it.second.start_expecting();

  // Extract INFO fields into separate attributes
  std::vector<bool> infos_extracted(r->n_info, false);
  unsigned n_info_as_attr = 0;
  for (unsigned i = 0; i < r->n_info; i++) {
    bcf_info_t* info = r->d.info + i;
    int info_id = info->key;
    const char* key = bcf_hdr_int2id(hdr, BCF_DT_ID, info_id);

    // No need to store END.
    if (strcmp("END", key) == 0) {
      infos_extracted[i] = true;
      n_info_as_attr++;
      continue;
    }

    Buffer* buff;
    if (buffers_.extra_attr(std::string("info_") + key, &buff)) {
      // No need to store the string key, as it's an extracted attribute.
      const bool include_key = false;
      buffer_info_field(hdr, r, info, include_key, &val_, buff);
      // Mark key so we don't add it again in the info blob attribute
      infos_extracted[i] = true;
      n_info_as_attr++;
    }
  }

  // Extract FMT fields into separate attributes
  std::vector<bool> fmts_extracted(r->n_fmt, false);
  unsigned n_fmt_as_attr = 0;
  for (unsigned i = 0; i < r->n_fmt; i++) {
    bcf_fmt_t* fmt = r->d.fmt + i;
    int fmt_id = fmt->id;
    const char* key = bcf_hdr_int2id(hdr, BCF_DT_ID, fmt_id);
    Buffer* buff;
    if (buffers_.extra_attr(std::string("fmt_") + key, &buff)) {
      // No need to store the string key, as it's an extracted attribute.
      const bool include_key = false;
      buffer_fmt_field(hdr, r, fmt, include_key, &val_, buff);
      // Mark key so we don't add it again in the fmt blob attribute
      fmts_extracted[i] = true;
      n_fmt_as_attr++;
    }
  }

  // Remaining INFO/FMT fields go into blob attributes
  Buffer& info = buffers_.info();
  info.offsets().push_back(info.size());
  const uint32_t non_attr_info = r->n_info - n_info_as_attr;
  info.append(&non_attr_info, sizeof(uint32_t));
  for (unsigned i = 0; i < r->n_info; i++) {
    if (!infos_extracted[i]) {
      bcf_info_t* info_field = r->d.info + i;
      buffer_info_field(hdr, r, info_field, true, &val_, &info);
    }
  }

  Buffer& fmt = buffers_.fmt();
  fmt.offsets().push_back(fmt.size());
  const uint32_t non_attr_fmt = r->n_fmt - n_fmt_as_attr;
  fmt.append(&non_attr_fmt, sizeof(uint32_t));
  for (unsigned i = 0; i < r->n_fmt; i++) {
    if (!fmts_extracted[i]) {
      bcf_fmt_t* fmt_field = r->d.fmt + i;
      buffer_fmt_field(hdr, r, fmt_field, true, &val_, &fmt);
    }
  }

  // Make sure any extra attributes get dummy values if no info was written.
  for (auto& it : buffers_.extra_attrs())
    it.second.stop_expecting();

  if (node.type == RecordHeapV3::NodeType::Record)
    records_buffered_++;
  else
    anchors_buffered_++;

  // TODO: make this max buffer size check a parameter.
  const uint64_t buffer_size = buffers_.total_size();
  if (buffer_size > ((uint64_t)1 * 1024 * 1024 * 1024)) {
    return false;
  }

  return true;
}

void WriterWorkerV3::buffer_alleles(bcf1_t* record, Buffer* buffer) {
  buffer->offsets().push_back(buffer->size());

  // Alleles list is null-separated but we store as null-terminated CSV to make
  // it easier to interact with on export.
  char* allele_ptr = record->d.als;
  for (unsigned i = 0; i < record->n_allele; i++) {
    const char comma = ',';
    auto len = std::strlen(allele_ptr);
    buffer->append(allele_ptr, len);
    if (i < static_cast<unsigned>(record->n_allele - 1))
      buffer->append(&comma, sizeof(char));
    allele_ptr += len + 1;
  }

  const char nul = '\0';
  buffer->append(&nul, sizeof(char));
}

void WriterWorkerV3::buffer_info_field(
    const bcf_hdr_t* hdr,
    bcf1_t* r,
    const bcf_info_t* info,
    bool include_key,
    HtslibValueMem* val,
    Buffer* buff) {
  int info_id = info->key;
  const char* key = bcf_hdr_int2id(hdr, BCF_DT_ID, info_id);
  int type = bcf_hdr_id2type(hdr, BCF_HL_INFO, info->key);
  val->ndst = HtslibValueMem::convert_ndst_for_type(
      val->ndst, type, &val->type_for_ndst);
  int num_vals = bcf_get_info_values(hdr, r, key, &val->dst, &val->ndst, type);
  if (num_vals < 0)
    throw std::runtime_error(
        "Error reading INFO value for '" + std::string(key) + "'; " +
        std::to_string(num_vals));

  if (buff->expecting())
    buff->offsets().push_back(buff->size());

  // Write an INFO value: [keystr],type,nvalues,values
  if (include_key)
    buff->append(key, strlen(key) + 1);
  buff->append(&type, sizeof(int));
  buff->append(&num_vals, sizeof(int));
  buff->append(val->dst, num_vals * utils::bcf_type_size(type));
}

void WriterWorkerV3::buffer_fmt_field(
    const bcf_hdr_t* hdr,
    bcf1_t* r,
    const bcf_fmt_t* fmt,
    bool include_key,
    HtslibValueMem* val,
    Buffer* buff) {
  const char* key = bcf_hdr_int2id(hdr, BCF_DT_ID, fmt->id);

  // Header says GT is str, but it's encoded as an int (index into alleles)
  int type = std::strcmp("GT", key) == 0 ?
                 BCF_HT_INT :
                 bcf_hdr_id2type(hdr, BCF_HL_FMT, fmt->id);
  val->ndst = HtslibValueMem::convert_ndst_for_type(
      val->ndst, type, &val->type_for_ndst);
  int num_vals =
      bcf_get_format_values(hdr, r, key, &val->dst, &val->ndst, type);
  if (num_vals < 0)
    throw std::runtime_error(
        "Error reading FMT field '" + std::string(key) + "'; " +
        std::to_string(num_vals));

  if (buff->expecting())
    buff->offsets().push_back(buff->size());

  // Write a FMT value: [keystr],type,nvalues,values
  if (include_key)
    buff->append(key, strlen(key) + 1);
  buff->append(&type, sizeof(int));
  buff->append(&num_vals, sizeof(int));
  buff->append(val->dst, num_vals * utils::bcf_type_size(type));
}

}  // namespace vcf
}  // namespace tiledb
