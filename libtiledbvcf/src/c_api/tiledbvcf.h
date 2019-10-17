/**
 * @file   tiledbvcf.h
 *
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
 *
 * @section DESCRIPTION
 *
 * This file declares the C API for TileDB-VCF.
 */

#ifndef TILEDB_VCF_H
#define TILEDB_VCF_H

// Generated by CMake; defines TILEDBVCF_EXPORT (etc) macros.
#include "tiledbvcf_export.h"

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ********************************* */
/*             CONSTANTS             */
/* ********************************* */

/** Success */
#define TILEDB_VCF_OK 0
/** General error */
#define TILEDB_VCF_ERR (-1)

/* ********************************* */
/*               ENUMS               */
/* ********************************* */

/** Reader status. */
typedef enum {
/** Helper macro for defining read reader status enums. */
#define TILEDB_VCF_READ_STATUS_ENUM(id) TILEDB_VCF_##id
#include "tiledbvcf_enum.h"
#undef TILEDB_VCF_READ_STATUS_ENUM
} tiledb_vcf_read_status_t;

/** Attribute datatype. */
typedef enum {
/** Helper macro for defining attribute datatype enums. */
#define TILEDB_VCF_ATTR_DATATYPE_ENUM(id) TILEDB_VCF_##id
#include "tiledbvcf_enum.h"
#undef TILEDB_VCF_ATTR_DATATYPE_ENUM
} tiledb_vcf_attr_datatype_t;

/* ********************************* */
/*           STRUCT TYPES            */
/* ********************************* */

/** Reader object. */
typedef struct tiledb_vcf_reader_t tiledb_vcf_reader_t;

/** Writer object. */
typedef struct tiledb_vcf_writer_t tiledb_vcf_writer_t;

/** Error object. */
typedef struct tiledb_vcf_error_t tiledb_vcf_error_t;

/* ********************************* */
/*              READER               */
/* ********************************* */

/**
 * Allocates a VCF reader object.
 *
 * A VCF reader is used for reading from existing TileDB-VCF datasets. Reading
 * from a TileDB-VCF dataset is accomplished by specifying a set of sample
 * names, a set of genomic regions, and a set of "attributes" per sample to read
 * from the dataset.
 *
 * @param reader Will be set to point at the allocated reader object.
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t tiledb_vcf_reader_alloc(tiledb_vcf_reader_t** reader);

/**
 * Frees the given VCF reader object, freeing any held memory or resources.
 *
 * @param reader Pointer to reader object to free.
 */
TILEDBVCF_EXPORT void tiledb_vcf_reader_free(tiledb_vcf_reader_t** reader);

/**
 * Initializes the reader for reading from the dataset at the given URI.
 *
 * @param reader VCF reader object
 * @param dataset_uri URI of TileDB VCF dataset
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t
tiledb_vcf_reader_init(tiledb_vcf_reader_t* reader, const char* dataset_uri);

/**
 * Sets the URI of a file containing sample names to read. The file should
 * contain, one per line, the names of samples in the dataset to be read.
 *
 * You can also manually specify sample names without a file with the
 * `tiledb_vcf_reader_set_samples()` function.
 *
 * If you specify both a CSV samples list and a samples file, samples from both
 * will be included in the read.
 *
 * @param reader VCF reader object
 * @param samples_uri URI of file containing sample names.
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t tiledb_vcf_reader_set_samples_file(
    tiledb_vcf_reader_t* reader, const char* uri);

/**
 * Sets the URI of a BED file containing regions to be read.
 *
 * The BED file is assumed to follow the format of bcftools: a tab-separated
 * file of the format `contig   start   end` where the start/end interval
 * is a 0-indexed, half-open interval.
 *
 * You can also manually specify regions without a BED file with the
 * `tiledb_vcf_reader_set_regions()` function.
 *
 * If you specify both a CSV regions list and a BED file, regions from both
 * will be included in the read.
 *
 * @param reader VCF reader object
 * @param uri URI of BED file
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t
tiledb_vcf_reader_set_bed_file(tiledb_vcf_reader_t* reader, const char* uri);

/**
 * Given a CSV string of sample names, sets the samples to be read.
 *
 * If you specify both a CSV samples list and a samples file, samples from both
 * will be included in the read.
 *
 * @param reader VCF reader object
 * @param samples CSV list of sample names.
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t
tiledb_vcf_reader_set_samples(tiledb_vcf_reader_t* reader, const char* samples);

/**
 * Given a CSV string of genomic regions, sets the regions to be read.
 *
 * Each region string should be in the form "contig:start-end". The start/end
 * interval should be a 1-indexed, inclusive interval. This is different from
 * the intervals specified in a BED file (which are 0-indexed, half-open
 * intervals).
 *
 * If you specify both a CSV regions list and a BED file, regions from both
 * will be included in the read.
 *
 * @param reader VCF reader object
 * @param ranges CSV list of region strings
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t
tiledb_vcf_reader_set_regions(tiledb_vcf_reader_t* reader, const char* regions);

/**
 * Sets whether or not to sort the regions to be read. By default, the regions
 * from the BED file (if specified) and the CSV regions (if specified) are
 * combined and then sorted. This can be slow if there are many regions in
 * total.
 *
 * If you are only specifying a BED file, and you are certain that the regions
 * within it are already sorted, you can disable sorting here to gain some
 * performance. The behavior is undefined if you disable sorting but the BED
 * file is not actually sorted.
 *
 * The sorting order is first on contig (in the order specified in the VCF
 * header of the ingested samples), and then on start position.
 *
 * @param reader VCF reader object
 * @param sort_regions If `1`, regions will be sorted (the default). If `0`,
 *      region sorting is disabled.
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t tiledb_vcf_reader_set_sort_regions(
    tiledb_vcf_reader_t* reader, int32_t sort_regions);

/**
 * Sets the region partitioning info for the reader. The partitioning divides
 * the reader genomic regions (e.g. the BED ranges) according to a simple block
 * distribution.
 *
 * For example, suppose a BED file is specified that contains 1,000 regions.
 * With 10 partitions, each partition would be responsible for 100 regions of
 * the BED file. Partition index 0 would take regions [0, 99], index 1 would
 * take regions [100, 199], etc.
 *
 * You can combine region and sample partitioning.
 *
 * @param reader VCF reader object
 * @param partition Index of region partition that this reader object should
 *      process.
 * @param num_partitions Total number of region partitions.
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t tiledb_vcf_reader_set_region_partition(
    tiledb_vcf_reader_t* reader, int32_t partition, int32_t num_partitions);

/**
 * Sets the sample partitioning info for the reader. The partitioning divides
 * the samples being read according to a simple block distribution.
 *
 * For example, suppose a samples file is specified that contains 1,000 sample
 * names. With 10 partitions, each partition would be responsible for reading
 * 100 samples. Partition index 0 would take samples [0, 99], index 1 would take
 * samples [100, 199], etc.
 *
 * You can combine region and sample partitioning.
 *
 * @param reader VCF reader object
 * @param partition Index of sample partition that this reader object should
 *      process.
 * @param num_partitions Total number of sample partitions.
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t tiledb_vcf_reader_set_sample_partition(
    tiledb_vcf_reader_t* reader, int32_t partition, int32_t num_partitions);

/**
 * Sets a filter on record variant types that are included/excluded during
 * export.
 *
 * @param reader VCF reader object
 * @param include If `1`, the variant types will be included. Else they will be
 *      excluded.
 * @param types CSV string of variant types to filter, one of 'ref'.
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t tiledb_vcf_reader_set_variant_filter(
    tiledb_vcf_reader_t* reader, int32_t include, const char* types);

/**
 * Sets a buffer to hold values for a specific attribute being read. This is the
 * main interface by which VCF data is returned from a read operation.
 *
 * The in-memory format of the returned data follows the Apache Arrow
 * specification for fixed-length, variable-length (e.g. List<char>), and list
 * variable-length (e.g. List<List<char>>)values. The values are all
 * little-endian.
 *
 * The allowed attributes and their Arrow-like datatypes are:
 *
 * - "sample_name": The sample name  (List<char>, non-nullable)
 * - "contig": The contig name of record  (List<char>, non-nullable)
 * - "pos_start": The 1-based start position of record  (int32, non-nullable)
 * - "pos_end": The 1-based end position of record  (int32, non-nullable)
 * - "query_bed_start": The 0-based start position of the query BED range that
 *    intersected the record.  (int32, non-nullable)
 * - "query_bed_end": The 1-based end position of the query BED range that
 *    intersected the record.  (int32, non-nullable)
 * - "alleles": List of allele names  (List<List<char>>, non-nullable)
 * - "id": ID string  (List<char>, non-nullable)
 * - "filters": List of filter names  (List<List<char>>, nullable)
 * - "qual": The quality value  (float32, non-nullable)
 * - "info_*": A specific INFO field value  (List<?>, nullable)
 * - "fmt_*": A specific FMT field value  (List<?>, nullable)
 * - "fmt": Format byte blob of non-attribute fields  (List<byte>, nullable)
 * - "info": Info byte blob of non-attribute fields  (List<byte>, nullable)
 *
 * See the specific notes below for more information.
 *
 * (1) Variable-length vs fixed-length
 * Fixed-length attributes, such as `pos_start` or `qual`, contain a
 * single value per result record. Variable-length attributes, such as
 * `sample_name` or `info_* / fmt_*`, contain a variable number of values per
 * result record, which may be 0.
 *
 * For variable-length attributes, such as `sample_name`, an extra "offsets"
 * buffer must be provided. This will be populated with the starting offset of
 * the variable-length value in the associated data buffer, for each record.
 *
 * For list variable length attributes, such as `alleles`, in addition to an
 * offsets buffer, a separate "list offsets" buffer must also be provided.
 *
 * The contents of the values and offset buffers follow the Apache Arrow
 * semantics.
 *
 * (2) INFO/FMT fields
 * In general to access specific INFO or FMT field values, you should
 * use the special `fmt_*` / `info_*` attribute names. For example, to
 * retrieve the values of the `MIN_DP` format field, set a buffer for
 * attribute `fmt_MIN_DP`. The generic `fmt` and `info` byte blob attributes
 * are mostly available as an escape hatch.
 *
 * When retrieving info/fmt fields, the values stored in the buffers are typed
 * according to the actual field type. For example, the `fmt_GT` attribute
 * extracts the `GT` FMT field for a record. In the VCF specification, `GT` is
 * defined as a list of integer values. This means the bytes stored in the
 * `fmt_GT` result buffer will be integer values.
 *
 * All of the `info_*`/`fmt_*` attributes are variable-length. The offset buffer
 * combined with the datatype of the attribute allows you to interpret the
 * returned bytes appropriately (number and type of values).
 *
 * (3) Nullable attributes
 * Most attributes are non-nullable, meaning a value will be stored for the
 * attribute for every result record. The nullable attributes are:
 *
 * - "filters"
 * - "info"
 * - "info_*"
 * - "fmt"
 * - "fmt_*"
 *
 * For the nullable attributes, a validity bitmap buffer must also be provided.
 * For a result record at index `i`, the bit index `i` will be set if the value
 * of the nullable attribute has a valid (non-null) value. See the function
 * `tiledb_vcf_reader_set_validity_bitmap`.
 *
 * (4) Apache Arrow integration
 * The offsets and nullable-attribute bitmap formats adhere to the Apache Arrow
 * semantics for offsets and validity bitmaps. This is to allow zero-copy
 * conversion to Arrow Tables.
 *
 * If you are using the Arrow interface to the TileDB-VCF reader class, note
 * that your buffers must be allocated according to the Arrow requirements,
 * which are, briefly:
 * - 8-byte aligned
 * - Length-padded to a multiple of 8 bytes
 *
 * **Example**:
 *
 * Suppose you want to read attributes `pos_start` and `filters`. You would
 * provide 5 buffers:
 * - pos_start: Values buffer only
 * - filters: Values, offsets, list offsets, and validity bitmap buffers.
 *
 * Suppose the read result contained three records with the following data:
 *     pos_start  |  filters
 *   -------------+------------
 *     100        |  "f1"
 *     200        |
 *     300        |  "f2", "f3"
 *
 * The buffers would contain the following result bytes:
 *
 * pos_start values (little-endian int32 values, one per record):
 *   0x64 0x00 0x00 0x00 0xc8 0x00 0x00 0x00 0x2c 0x01 0x00 0x00
 * filters values (ASCII char values)
 *   0x66 0x31 0x66 0x32 0x66 0x33
 * filters offsets (little-endian int32 values)
 *   0x00 0x00 0x00 0x00 0x02 0x00 0x00 0x00 0x02 0x00 0x00 0x00
 *   0x04 0x00 0x00 0x00 0x06 0x00 0x00 0x00
 * filters list offsets (little-endian int32 values)
 *   0x00 0x00 0x00 0x00 0x01 0x00 0x00 0x00 0x02 0x00 0x00 0x00
 *   0x04 0x00 0x00 0x00 0x05 0x00 0x00 0x00
 * filters validity bitmap
 *   0x05
 *
 * The validity bitmap value 0x05 corresponds to binary value 0b00000101, which
 * indicates that the `filters` list for record index 0 is non-null (valid),
 * for record index 1 is null, and for record index 2 is non-null.
 *
 * @param reader VCF reader object
 * @param attribute Name of attribute
 * @param buff_size Size (in bytes) of `buff`.
 * @param buff Buffer to receive data.
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t tiledb_vcf_reader_set_buffer_values(
    tiledb_vcf_reader_t* reader,
    const char* attribute,
    int64_t buff_size,
    void* buff);

/**
 * Sets the value offsets buffer for a variable-length attribute.
 *
 * Fixed-length attributes, such as `pos_start` or `qual`, contain a
 * single value per result record. Variable-length attributes, such as
 * `sample_name` or `info_* / fmt_*`, contain a variable number of values per
 * result record, which may be 0.
 *
 * For variable-length attributes, an extra "offsets" buffer must be provided.
 * This will be populated with the starting offset of the variable-length value
 * in the associated data buffer, for each record.
 *
 * @param reader VCF reader object
 * @param attribute Name of attribute
 * @param buff_size Size (in bytes) of `buff`.
 * @param buff Buffer to receive offsets.
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t tiledb_vcf_reader_set_buffer_offsets(
    tiledb_vcf_reader_t* reader,
    const char* attribute,
    int64_t buff_size,
    int32_t* buff);

/**
 * Sets the list offsets buffer for a list var-len attribute. The list var-len
 * attributes are:
 * - "filters"
 * - "alleles"
 *
 * List attributes contain a multiple variable-length values per result record.
 * For example, a record that has CSV alleles `C,<NON_REF>` has 2
 * variable-length string values, `C` and `<NON_REF>`. To distinguish the
 * values, an extra "list offset" buffer must be provided.
 *
 * **Example:**
 *
 * Suppose the read results contain three records, with CSV alleles
 * `C,<NON_REF>`, `T,<NON_REF>` and `G,<NON_REF>` respectively.
 *
 * The *values* buffer would contain the chars:
 *   char:  C < N O N _ R E F > T < N O N _ R E F > G < N O N _ R E F >
 *   index: 0                   1                   2
 *          0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9
 *
 * The *offsets* buffer contains the positions of the individual strings ("G",
 * "<NON_REF>" etc). The offsets buffer therefore contains:
 *   [0, 1, 10, 11, 20, 21, 30]
 * e.g. the string starting at offset 11 and continuing to 19 is "<NON_REF>".
 *
 * The *list offsets* buffer contains the positions in the offsets buffer
 * associating the pairs of values with the actual records. The list offsets
 * buffer therefore contains:
 *   [0, 2, 4, 6]
 * because each record has exactly two allele strings.
 *
 * @param reader VCF reader object
 * @param attribute Name of attribute
 * @param buff_size Size (in bytes) of `buff`.
 * @param buff Buffer to receive list offsets.
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t tiledb_vcf_reader_set_buffer_list_offsets(
    tiledb_vcf_reader_t* reader,
    const char* attribute,
    int64_t buff_size,
    int32_t* buff);

/**
 * Sets the validity bitmap buffer for a nullable attribute.
 *
 * Most attributes are non-nullable, meaning a value will be stored for the
 * attribute for every result record. The nullable attributes are:
 *
 * - "filters"
 * - "info"
 * - "info_*"
 * - "fmt"
 * - "fmt_*"
 *
 * For the nullable attributes, a validity bitmap buffer must also be provided.
 * For a result record at index `i`, the bit index `i` will be set if the value
 * of the nullable attribute has a valid (non-null) value.
 *
 * @param reader VCF reader object
 * @param attribute Name of attribute
 * @param buff_size Size (in bytes) of `buff`.
 * @param buff Buffer to receive bitmap.
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t tiledb_vcf_reader_set_buffer_validity_bitmap(
    tiledb_vcf_reader_t* reader,
    const char* attribute,
    int64_t buff_size,
    uint8_t* buff);

/**
 * Sets a rough memory budget for the reader's internal allocations. This budget
 * is divided up equally between attribute buffers used for internal TileDB
 * queries, and the TileDB storage manager's memory budget parameters.
 *
 * The memory budget is split 50/50 between TileDB-VCF's and TileDB's internal
 * memory budget, including query buffers. For the TileDB query buffers, we
 * allocate two sets (due to double-buffering). That means the allocation size
 * of the query buffers *per attribute* is:
 *
 *   ((mem_budget / 2) / num_query_buffers) / 2.
 *
 * Example: Suppose you want to target a TileDB query buffer size of 100MB per
 * attribute. Suppose the query needs 3 fixed-len attributes and 2 var-len.
 * That is a total of 3 + 4 = 7 query buffers that need to be allocated. So:
 *
 *   required_mem_budget = 100 * 2 * 7 * 2 = 2800 MB
 *
 * The default memory budget is 2GB.
 *
 * @param reader VCF reader object
 * @param memory_mb Memory budget (in MB).
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t tiledb_vcf_reader_set_memory_budget(
    tiledb_vcf_reader_t* reader, int32_t memory_mb);

/**
 * Sets the max number of records that will be read until the read status is
 * considered complete.
 *
 * If instead you want to receive all records, but only process them a chunk
 * at a time, you should set your buffer sizes to be of the desired chunk size,
 * and then repeatedly resubmit the read operation until the read status is
 * complete, processing the results in between read operations.
 *
 * @param reader VCF reader object
 * @param max_num_records Max number of records
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t tiledb_vcf_reader_set_max_num_records(
    tiledb_vcf_reader_t* reader, int64_t max_num_records);

/**
 * Sets configuration parameters on the TileDB context used for internal
 * processing.
 *
 * The string should be of the format: "sm.option1=1000,sm.option2=baz,..."
 * with multiple TileDB config params separated by commas.
 *
 * @param reader VCF reader object
 * @param config CSV string of TileDB config param values.
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t tiledb_vcf_reader_set_tiledb_config(
    tiledb_vcf_reader_t* reader, const char* config);

/**
 * Performs a blocking read operation. This reads data from the dataset into the
 * buffers that have been set on the reader.
 *
 * If all records in the dataset satisfying the query (genomic regions and
 * samples) are returned in the read operation, the read status is set to
 * 'complete'. If the buffers provided were too small to hold all records,
 * the read status is set to 'incomplete'. Simply process the partial results,
 * and resubmit the read operation until the status becomes 'complete'.
 *
 * @param reader VCF reader object
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t tiledb_vcf_reader_read(tiledb_vcf_reader_t* reader);

/**
 * Get the read status of the given reader.
 *
 * @param reader VCF reader object
 * @param status Set to the current read status
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t tiledb_vcf_reader_get_status(
    tiledb_vcf_reader_t* reader, tiledb_vcf_read_status_t* status);

/**
 * Get the number of records in the result of the previous read operation.
 *
 * @param reader VCF reader object
 * @param num_records Set to the number of records in the result
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t tiledb_vcf_reader_get_result_num_records(
    tiledb_vcf_reader_t* reader, int64_t* num_records);

/**
 * After reading some data, gets the sizes of reader results for an attribute.
 *
 * @param reader VCF reader object
 * @param attribute Name of attribute
 * @param num_offsets Set to the number of offsets in the result offsets buffer.
 * @param num_data_elements Set to the number of elements in the result values
 *      buffer. This will be the number of data elements across all cells,
 *      variable-length included.
 * @param num_data_bytes Set to the number of bytes in the result values buffer
 *      across all cells.
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t tiledb_vcf_reader_get_result_size(
    tiledb_vcf_reader_t* reader,
    const char* attribute,
    int64_t* num_offsets,
    int64_t* num_data_elements,
    int64_t* num_data_bytes);

/**
 * Gets the number of buffers that have been set on the reader.
 *
 * @param reader VCF reader object
 * @param num_buffers Set to the number of buffers
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t tiledb_vcf_reader_get_num_buffers(
    tiledb_vcf_reader_t* reader, int32_t* num_buffers);

/**
 * Gets the values buffer (by index) that was set on the reader.
 *
 * @param reader VCF reader object
 * @param buffer_idx Index of buffer to get
 * @param name Set to the name of the buffer
 * @param buff Set to the data buffer.
 * @return
 */
TILEDBVCF_EXPORT int32_t tiledb_vcf_reader_get_buffer_values(
    tiledb_vcf_reader_t* reader,
    int32_t buffer_idx,
    const char** name,
    void** buff);

/**
 * Gets the offsets buffer (by index) that was set on the reader.
 *
 * @param reader VCF reader object
 * @param buffer_idx Index of buffer to get
 * @param name Set to the name of the buffer
 * @param buff Set to the offsets buffer.
 * @return
 */
TILEDBVCF_EXPORT int32_t tiledb_vcf_reader_get_buffer_offsets(
    tiledb_vcf_reader_t* reader,
    int32_t buffer_idx,
    const char** name,
    int32_t** buff);

/**
 * Gets the list offsets buffer (by index) that was set on the reader.
 *
 * @param reader VCF reader object
 * @param buffer_idx Index of buffer to get
 * @param name Set to the name of the buffer
 * @param buff Set to the list offsets buffer.
 * @return
 */
TILEDBVCF_EXPORT int32_t tiledb_vcf_reader_get_buffer_list_offsets(
    tiledb_vcf_reader_t* reader,
    int32_t buffer_idx,
    const char** name,
    int32_t** buff);

/**
 * Gets the validity bitmap buffer (by index) that was set on the reader.
 *
 * @param reader VCF reader object
 * @param buffer_idx Index of buffer to get
 * @param name Set to the name of the buffer
 * @param buff Set to the bitmap buffer.
 * @return
 */
TILEDBVCF_EXPORT int32_t tiledb_vcf_reader_get_buffer_validity_bitmap(
    tiledb_vcf_reader_t* reader,
    int32_t buffer_idx,
    const char** name,
    uint8_t** buff);

/**
 * Gets the datatype of a particular attribute.
 *
 * Returns an error if the specified attribute is unknown.
 *
 * @param reader VCF reader object
 * @param attribute Name of attribute to retrieve type of
 * @param datatype Set to the datatype of the attribute
 * @param var_len Set to `1` if the attribute is variable-length, else `0`
 * @param nullable Set to `1` if the attribute is nullable, else `0`
 * @param list Set to `1` if the attribute is a var-len list, else `0`
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t tiledb_vcf_reader_get_attribute_type(
    tiledb_vcf_reader_t* reader,
    const char* attribute,
    tiledb_vcf_attr_datatype_t* datatype,
    int32_t* var_len,
    int32_t* nullable,
    int32_t* list);

/**
 * Returns the version number of the TileDB VCF dataset.
 *
 * @param reader VCF reader object
 * @param version Set to the version number
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t tiledb_vcf_reader_get_dataset_version(
    tiledb_vcf_reader_t* reader, int32_t* version);

/**
 * Resets the reader without discarding any parameters or configuration
 * settings. This allows the same reader instance to be used for another read
 * operation, without having to reopen/reinitialize the dataset.
 *
 * @param reader VCF reader object
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t tiledb_vcf_reader_reset(tiledb_vcf_reader_t* reader);

/**
 * Gets the last error from the reader object. Don't forget to free the error
 * object.
 *
 * @param reader VCF reader object
 * @param error Set to a newly allocated error object holding the last error.
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t tiledb_vcf_reader_get_last_error(
    tiledb_vcf_reader_t* reader, tiledb_vcf_error_t** error);

/* ********************************* */
/*              WRITER               */
/* ********************************* */

/**
 * Allocate a VCF writer object.
 *
 * @param writer Will be set to point at the allocated writer object.
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t tiledb_vcf_writer_alloc(tiledb_vcf_writer_t** writer);

/**
 * Free the given VCF writer object.
 *
 * @param writer Pointer to writer object to free.
 */
TILEDBVCF_EXPORT void tiledb_vcf_writer_free(tiledb_vcf_writer_t** writer);

/**
 * Initializes the writer for writing to a dataset at the given URI.
 *
 * @param writer VCF writer object
 * @param dataset_uri URI of dataset to be written to
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t
tiledb_vcf_writer_init(tiledb_vcf_writer_t* writer, const char* dataset_uri);

/**
 * Sets the sample files to be registered or ingested.
 *
 * @param writer VCF writer object
 * @param sample_uris CSV list of sample URIs to be registered or ingested.
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t tiledb_vcf_writer_set_samples(
    tiledb_vcf_writer_t* writer, const char* sample_uris);

/**
 * [Creation only] Sets the info and fmt fields that should be extracted as
 * separate TileDB attributes.
 *
 * @param writer VCF writer object
 * @param attributes CSV list of fields in the format `info_*` or `fmt_*`.
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t tiledb_vcf_writer_set_extra_attributes(
    tiledb_vcf_writer_t* writer, const char* attributes);

/**
 * Creates a new TileDB-VCF dataset, using previously set parameters.
 *
 * @param writer VCF writer object
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t
tiledb_vcf_writer_create_dataset(tiledb_vcf_writer_t* writer);

/**
 * Registers new samples into an existing TileDB-VCF dataset, using previously
 * set parameters.
 *
 * @param writer VCF writer object
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t
tiledb_vcf_writer_register(tiledb_vcf_writer_t* writer);

/**
 * Ingests (stores) new samples into an existing TileDB-VCF dataset, using
 * previously set parameters.
 *
 * @param writer VCF writer object
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t tiledb_vcf_writer_store(tiledb_vcf_writer_t* writer);

/**
 * Gets the last error from the writer object. Don't forget to free the error
 * object.
 *
 * @param writer VCF writer object
 * @param error Set to a newly allocated error object holding the last error.
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t tiledb_vcf_writer_get_last_error(
    tiledb_vcf_writer_t* writer, tiledb_vcf_error_t** error);

/* ********************************* */
/*               ERROR               */
/* ********************************* */

/**
 * Gets the error message string from the error object.
 *
 * @param error VCF error object
 * @param errmsg Set to the error string
 * @return `TILEDB_VCF_OK` for success or `TILEDB_VCF_ERR` for error.
 */
TILEDBVCF_EXPORT int32_t
tiledb_vcf_error_get_message(tiledb_vcf_error_t* error, const char** errmsg);

/**
 * Free the given error object.
 *
 * @param reader Pointer to error object to free.
 */
TILEDBVCF_EXPORT void tiledb_vcf_error_free(tiledb_vcf_error_t** error);

#ifdef __cplusplus
}
#endif

#endif  // TILEDB_VCF_H
