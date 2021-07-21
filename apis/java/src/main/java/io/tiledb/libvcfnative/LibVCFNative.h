/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class io_tiledb_libvcfnative_LibVCFNative */

#ifndef _Included_io_tiledb_libvcfnative_LibVCFNative
#define _Included_io_tiledb_libvcfnative_LibVCFNative
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_alloc
 * Signature: ([J)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1alloc
  (JNIEnv *, jclass, jlongArray);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_free
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1free
  (JNIEnv *, jclass, jlong);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_init
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1init
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_set_samples_file
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1set_1samples_1file
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_set_bed_file
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1set_1bed_1file
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_set_samples
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1set_1samples
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_set_regions
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1set_1regions
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_set_sort_regions
 * Signature: (JZ)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1set_1sort_1regions
  (JNIEnv *, jclass, jlong, jboolean);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_set_region_partition
 * Signature: (JII)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1set_1region_1partition
  (JNIEnv *, jclass, jlong, jint, jint);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_set_sample_partition
 * Signature: (JII)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1set_1sample_1partition
  (JNIEnv *, jclass, jlong, jint, jint);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_set_buffer_values
 * Signature: (JLjava/lang/String;Ljava/nio/ByteBuffer;)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1set_1buffer_1values
  (JNIEnv *, jclass, jlong, jstring, jobject);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_set_buffer_offsets
 * Signature: (JLjava/lang/String;Ljava/nio/ByteBuffer;)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1set_1buffer_1offsets
  (JNIEnv *, jclass, jlong, jstring, jobject);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_set_buffer_list_offsets
 * Signature: (JLjava/lang/String;Ljava/nio/ByteBuffer;)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1set_1buffer_1list_1offsets
  (JNIEnv *, jclass, jlong, jstring, jobject);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_set_buffer_validity_bitmap
 * Signature: (JLjava/lang/String;Ljava/nio/ByteBuffer;)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1set_1buffer_1validity_1bitmap
  (JNIEnv *, jclass, jlong, jstring, jobject);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_set_memory_budget
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1set_1memory_1budget
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_set_max_num_records
 * Signature: (JJ)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1set_1max_1num_1records
  (JNIEnv *, jclass, jlong, jlong);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_set_tiledb_config
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1set_1tiledb_1config
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_read
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1read
  (JNIEnv *, jclass, jlong);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_get_status
 * Signature: (J[I)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1get_1status
  (JNIEnv *, jclass, jlong, jintArray);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_get_result_num_records
 * Signature: (J[J)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1get_1result_1num_1records
  (JNIEnv *, jclass, jlong, jlongArray);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_get_result_size
 * Signature: (JLjava/lang/String;[J[J[J)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1get_1result_1size
  (JNIEnv *, jclass, jlong, jstring, jlongArray, jlongArray, jlongArray);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_get_attribute_type
 * Signature: (JLjava/lang/String;[I[I[I[I)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1get_1attribute_1type
  (JNIEnv *, jclass, jlong, jstring, jintArray, jintArray, jintArray, jintArray);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_get_attribute_count
 * Signature: (J[I)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1get_1attribute_1count
  (JNIEnv *, jclass, jlong, jintArray);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_get_attribute_name
 * Signature: (JI[B)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1get_1attribute_1name
  (JNIEnv *, jclass, jlong, jint, jbyteArray);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_get_materialized_attribute_count
 * Signature: (J[I)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1get_1materialized_1attribute_1count
  (JNIEnv *, jclass, jlong, jintArray);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_get_materialized_attribute_name
 * Signature: (JI[B)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1get_1materialized_1attribute_1name
  (JNIEnv *, jclass, jlong, jint, jbyteArray);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_get_fmt_attribute_count
 * Signature: (J[I)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1get_1fmt_1attribute_1count
  (JNIEnv *, jclass, jlong, jintArray);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_get_fmt_attribute_name
 * Signature: (JI[B)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1get_1fmt_1attribute_1name
  (JNIEnv *, jclass, jlong, jint, jbyteArray);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_get_info_attribute_count
 * Signature: (J[I)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1get_1info_1attribute_1count
  (JNIEnv *, jclass, jlong, jintArray);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_get_info_attribute_name
 * Signature: (JI[B)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1get_1info_1attribute_1name
  (JNIEnv *, jclass, jlong, jint, jbyteArray);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_get_dataset_version
 * Signature: (J[I)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1get_1dataset_1version
  (JNIEnv *, jclass, jlong, jintArray);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_set_verbose
 * Signature: (JZ)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1set_1verbose
  (JNIEnv *, jclass, jlong, jboolean);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_set_buffer_percentage
 * Signature: (JF)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1set_1buffer_1percentage
  (JNIEnv *, jclass, jlong, jfloat);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_set_tiledb_tile_cache_percentage
 * Signature: (JF)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1set_1tiledb_1tile_1cache_1percentage
  (JNIEnv *, jclass, jlong, jfloat);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_get_last_error_message
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1get_1last_1error_1message
  (JNIEnv *, jclass, jlong);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_set_tiledb_stats_enabled
 * Signature: (JZ)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1set_1tiledb_1stats_1enabled
  (JNIEnv *, jclass, jlong, jboolean);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_tiledb_stats_enabled
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1tiledb_1stats_1enabled
  (JNIEnv *, jclass, jlong);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_tiledb_stats
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1tiledb_1stats
  (JNIEnv *, jclass, jlong);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_version
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1version
  (JNIEnv *, jclass);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_set_enable_progress_estimation
 * Signature: (JZ)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1set_1enable_1progress_1estimation
  (JNIEnv *, jclass, jlong, jboolean);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_set_debug_print_vcf_regions
 * Signature: (JZ)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1set_1debug_1print_1vcf_1regions
  (JNIEnv *, jclass, jlong, jboolean);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_set_debug_print_sample_list
 * Signature: (JZ)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1set_1debug_1print_1sample_1list
  (JNIEnv *, jclass, jlong, jboolean);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_set_debug_print_tiledb_query_ranges
 * Signature: (JZ)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1set_1debug_1print_1tiledb_1query_1ranges
  (JNIEnv *, jclass, jlong, jboolean);

/*
 * Class:     io_tiledb_libvcfnative_LibVCFNative
 * Method:    tiledb_vcf_reader_set_large_attribute_buffer_factor
 * Signature: (JJ)I
 */
JNIEXPORT jint JNICALL Java_io_tiledb_libvcfnative_LibVCFNative_tiledb_1vcf_1reader_1set_1large_1attribute_1buffer_1factor
  (JNIEnv *, jclass, jlong, jlong);

#ifdef __cplusplus
}
#endif
#endif
