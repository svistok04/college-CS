#include "opencl_helper.h"
#include "matrix_mul_naive_NN.h"


int main()
{
  cl_int first_error = CL_SUCCESS;
  const char* error_context = NULL;
  init_opencl();
  cl_device_id dev = devices[0].device;
  print_device_info_str(dev, CL_DEVICE_NAME, "name");
  cl_int ret;

  cl_ulong max_alloc;
  ret = clGetDeviceInfo(dev, CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(cl_ulong), &max_alloc, NULL);
  printf("%lu \n", max_alloc);
  CHECK_CL_ERROR(ret, "Getting max allocation size");
  size_t vector_len = get_max_vector_len(dev, sizeof(float));
  printf("%lu \n", vector_len);
  size_t side = round_up((size_t)ceil(sqrt(vector_len)), LOCAL_ITEM_SIZE[0]);
  printf("%lu \n", side);
  size_t data_size[2] = {side, side};
  vector_len = side*side;
  // size_t data_size[2] = {64, 64};
  // size_t vector_len = data_size[0] * data_size[1];
  cl_context context = clCreateContext(NULL, 1, &dev, NULL, NULL, &ret);
  CHECK_CL_ERROR(ret, "Creating context");
  cl_command_queue command_queue = clCreateCommandQueueWithProperties(context, dev, 0, &ret);
  CHECK_CL_ERROR(ret, "Creating command queue");
  int* A = (int*)clSVMAlloc(context, CL_MEM_READ_ONLY, vector_len * sizeof(float), 0);
  CHECK_CL_ERROR(ret, "Creating buffer A");
  int* B = (int*)clSVMAlloc(context, CL_MEM_READ_ONLY, vector_len * sizeof(float), 0);
  CHECK_CL_ERROR(ret, "Creating buffer B");
  int* C = (int*)clSVMAlloc(context, CL_MEM_WRITE_ONLY, vector_len * sizeof(float), 0);
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
  const char* source = kernel_source_code;
  const size_t source_size = strlen(kernel_source_code);
  cl_program program = clCreateProgramWithSource(context, 1, &source, &source_size, &ret);
  RECORD_ERROR(ret, "Creating program from source");
  ret = clBuildProgram(program, 1, &dev, NULL, NULL, NULL);
  if (ret != CL_SUCCESS) {
    size_t log_size;
    clGetProgramBuildInfo(program, dev, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
    char* log = (char*)malloc(log_size);
    clGetProgramBuildInfo(program, dev, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
    fprintf(stderr, "Build error:\n%s\n", log);
    free(log);
    // free(A);
    // free(B);
    // free(C);
    clSVMFree(context, A);
    WARN_CL_RELEASE(ret, "buffer A");
    clSVMFree(context, B);
    WARN_CL_RELEASE(ret, "buffer B");
    clSVMFree(context, C);
    WARN_CL_RELEASE(ret, "buffer C");
    CHECK_CL_ERROR(ret, "whatever"); 
  }
  cl_kernel kernel = clCreateKernel(program, "matmul_naive", &ret);
  // ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&a_mem_obj);
  clSetKernelArgSVMPointer(kernel, 0, A);
  RECORD_ERROR(ret, "Setting kernel arg 0");
  // ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&b_mem_obj);
  clSetKernelArgSVMPointer(kernel, 1, B);
  RECORD_ERROR(ret, "Setting kernel arg 1");
  // ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&c_mem_obj);
  clSetKernelArgSVMPointer(kernel, 2, C);
  RECORD_ERROR(ret, "Setting kernel arg 2");
  int N = data_size[0];
  ret = clSetKernelArg(kernel, 3, sizeof(int), &N);
  size_t global_item_size = vector_len;

  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);
  ret = clEnqueueNDRangeKernel(command_queue, kernel, 2, NULL, data_size, LOCAL_ITEM_SIZE, 0, NULL, NULL);
  RECORD_ERROR(ret, "Enqueuing kernel");
  ret = clFinish(command_queue);
  RECORD_ERROR(ret, "Finishing queue");
  clock_gettime(CLOCK_MONOTONIC, &end);

  // ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0, vector_len * sizeof(float), C, 0, NULL, NULL);
  // RECORD_ERROR(ret, "Reading buffer C");
  double time_ms = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1e6;
  printf("Vector size: %zu elements (%.2f MB per buffer)\n", vector_len, data_size[0] * data_size[1] / (1024.0 * 1024.0));
  printf("Execution time: %.3f ms\n", time_ms);
  printf("-----------------------------\n");
  ret = clReleaseKernel(kernel);
  WARN_CL_RELEASE(ret, "kernel");
  ret = clReleaseProgram(program);
  WARN_CL_RELEASE(ret, "program");
  clSVMFree(context, A);
  // ret = clReleaseMemObject(a_mem_obj);
  WARN_CL_RELEASE(ret, "buffer A");
  clSVMFree(context, B);
  // ret = clReleaseMemObject(b_mem_obj);
  WARN_CL_RELEASE(ret, "buffer B");
  clSVMFree(context, C);
  // ret = clReleaseMemObject(c_mem_obj);
  WARN_CL_RELEASE(ret, "buffer C");
  ret = clReleaseCommandQueue(command_queue);
  WARN_CL_RELEASE(ret, "command queue");
  ret = clReleaseContext(context);
  WARN_CL_RELEASE(ret, "context");
  // free(A);
  // free(B);
  // free(C);
  if (first_error != CL_SUCCESS) {
    CHECK_CL_ERROR(first_error, error_context);
  }
  // cl_int CL_err = CL_SUCCESS;
  // cl_uint numPlatforms = 0;
  //
  // CL_err = clGetPlatformIDs( 0, NULL, &numPlatforms );
  //
  // if (CL_err == CL_SUCCESS)
  //   printf("%u platform(s) found\n", numPlatforms);
  // else
  //   printf("clGetPlatformIDs(%i)\n", CL_err);
  return 0;
}
