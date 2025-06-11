#pragma once
#include <CL/cl.h>
#include <CL/cl_platform.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define MB_FLOAT_BUFFER_ALLOC_CAP 1UL * 1024 * 1024

#define WARN_CL_RELEASE(retval, what) \
do { if ((retval) != CL_SUCCESS) { \
  fprintf(stderr, "Warning: Failed to release %s (code %d)\n", what, retval); \
} } while (0)

#define RECORD_ERROR(retval, msg) \
if ((retval) != CL_SUCCESS && first_error == CL_SUCCESS) { \
  first_error = retval; \
  error_context = msg; \
}

#define CHECK_CL_ERROR(err, msg) \
if ((err) != CL_SUCCESS) { \
  fprintf(stderr, "[OpenCL] %s\n ↳ Error code: %d\n ↳ Location: %s:%d\n", \
          msg, err, __FILE__, __LINE__); \
  check_succeeded(err); \
  exit(EXIT_FAILURE); \
}

typedef struct {
  cl_platform_id parent_platform;
  cl_device_id device;
} device_entry;

int init_opencl();
void print_device_info_str(cl_device_id device, cl_device_info param, const char* label);
int validate_matmul_dims(size_t N, size_t K, size_t M, size_t byte_cap);
void calc_dims_for_cap(size_t cap, double prop_N, double prop_K, double prop_M, size_t* out_N, size_t* out_K, size_t* out_M);
void print_run_summary(size_t N, size_t K, size_t M, double exec_time_ms);
size_t get_max_vector_len(cl_device_id dev, size_t element_size);
size_t round_up(size_t val, size_t multiple);
char* load_kernel_source(const char* filename);
void check_succeeded(cl_int err);

extern cl_platform_id* platforms;
extern cl_uint total_platforms;
extern device_entry* devices;
extern cl_uint total_devices;
