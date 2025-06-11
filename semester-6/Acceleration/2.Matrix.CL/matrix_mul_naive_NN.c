#define _POSIX_C_SOURCE 199309L
#include "matrix_mul_naive_NN.h"
#include "opencl_helper.h"
#include <time.h>

// const char *kernel_source_code =
//   #include "matrix_mul_naive_NN.cl"
// ;

void run_matrix_mul_naive_nn(
  cl_context context,
  cl_command_queue queue,
  cl_device_id device,
  size_t N, size_t K, size_t M,
  const size_t* global_size,
  const size_t* local_size,
  double *exec_time_ms
) {
  char* kernel_source_code = load_kernel_source("matrix_mul_naive_NN.cl");
  const char* source_str = kernel_source_code;
  cl_int first_error = CL_SUCCESS;
  char* error_context = NULL;
  cl_int ret = CL_SUCCESS;

  float* A = (float*)clSVMAlloc(context, CL_MEM_READ_ONLY, N * K * sizeof(float), 0);
  CHECK_CL_ERROR(ret, "Creating buffer A");
  float* B = (float*)clSVMAlloc(context, CL_MEM_READ_ONLY, K * M * sizeof(float), 0);
  CHECK_CL_ERROR(ret, "Creating buffer B");
  float* C = (float*)clSVMAlloc(context, CL_MEM_WRITE_ONLY, N * M * sizeof(float), 0);
  CHECK_CL_ERROR(ret, "Creating buffer C");
  // cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, vector_len * sizeof(float), NULL, &ret);
  // cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, vector_len * sizeof(float), NULL, &ret);
  // cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, vector_len * sizeof(float), NULL, &ret);
  // float* A = (float*)malloc(vector_len * sizeof(float));
  // float* B = (float*)malloc(vector_len * sizeof(float));
  // float* C = (float*)malloc(vector_len * sizeof(float));
  // ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0, vector_len * sizeof(float), A, 0, NULL, NULL);
  // RECORD_ERROR(ret, "Writing buffer A");
  // ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0, vector_len * sizeof(float), B, 0, NULL, NULL);
  // RECORD_ERROR(ret, "Writing buffer B");

  const size_t source_size = strlen(kernel_source_code);
  cl_program program = clCreateProgramWithSource(context, 1, &source_str, &source_size, &ret);
  RECORD_ERROR(ret, "Creating program from source");

  ret = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
  if (ret != CL_SUCCESS) {
    size_t log_size;
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
    char* log = (char*)malloc(log_size);
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
    fprintf(stderr, "Build error:\n%s\n", log);
    free(log);
    // free(A);
    // free(B);
    // free(C);
    clSVMFree(context, A);
    clSVMFree(context, B);
    clSVMFree(context, C);
    free((void*)kernel_source_code);
    free((void*)error_context);
    CHECK_CL_ERROR(ret, "Build program");
  }

  cl_kernel kernel = clCreateKernel(program, "matmul_naive", &ret);
  RECORD_ERROR(ret, "Creating kernel");

  // ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&a_mem_obj);
  ret = clSetKernelArgSVMPointer(kernel, 0, A);
  RECORD_ERROR(ret, "Setting kernel arg 0");
  // ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&b_mem_obj);
  ret = clSetKernelArgSVMPointer(kernel, 1, B);
  RECORD_ERROR(ret, "Setting kernel arg 1");
  // ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&2_mem_obj);
  ret = clSetKernelArgSVMPointer(kernel, 2, C);
  RECORD_ERROR(ret, "Setting kernel arg 2");
  ret = clSetKernelArg(kernel, 3, sizeof(int), &N);
  RECORD_ERROR(ret, "Setting kernel arg 3");
  ret = clSetKernelArg(kernel, 4, sizeof(int), &K);
  RECORD_ERROR(ret, "Setting kernel arg 4");
  ret = clSetKernelArg(kernel, 5, sizeof(int), &M);
  RECORD_ERROR(ret, "Setting kernel arg 5");

  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  ret = clEnqueueNDRangeKernel(queue, kernel, 2, NULL, global_size, local_size, 0, NULL, NULL);
  RECORD_ERROR(ret, "Enqueuing kernel");
  ret = clFinish(queue);
  RECORD_ERROR(ret, "Finishing queue");

  clock_gettime(CLOCK_MONOTONIC, &end);

  *exec_time_ms = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1e6;

  ret = clReleaseKernel(kernel);
  WARN_CL_RELEASE(ret, "kernel");
  ret = clReleaseProgram(program);
  WARN_CL_RELEASE(ret, "program");
  clSVMFree(context, A);
  // ret = clReleaseMemObject(a_mem_obj);
  // WARN_CL_RELEASE(ret, "buffer A");
  clSVMFree(context, B);
  // ret = clReleaseMemObject(b_mem_obj);
  // WARN_CL_RELEASE(ret, "buffer B");
  clSVMFree(context, C);
  // ret = clReleaseMemObject(c_mem_obj);
  // WARN_CL_RELEASE(ret, "buffer C");
  // free(A);
  // free(B);
  // free(C);
  if (first_error != CL_SUCCESS) {
    CHECK_CL_ERROR(first_error, error_context);
  }

  free((void*)kernel_source_code);
  free((void*)error_context);
}
