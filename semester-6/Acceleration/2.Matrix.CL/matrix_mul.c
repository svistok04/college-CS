#include "opencl_helper.h"
#include "matrix_mul_naive_NN.h"


int main() {
  cl_int first_error = CL_SUCCESS;
  const char* error_context = NULL;
  init_opencl();
  cl_device_id dev = devices[0].device;
  print_device_info_str(dev, CL_DEVICE_NAME, "name");
  cl_int ret;

  cl_ulong max_alloc;
  ret = clGetDeviceInfo(dev, CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(cl_ulong), &max_alloc, NULL);
  printf("max alloc %lu \n", max_alloc);
  CHECK_CL_ERROR(ret, "Getting max allocation size");
  double prop_N = 1.0, prop_K = 10.0, prop_M = 1.0;
  size_t N, K, M;
  calc_dims_for_cap(MB_FLOAT_BUFFER_ALLOC_CAP * 7, prop_N, prop_K, prop_M, &N, &K, &M);

  size_t max_work_group_size;
  clGetDeviceInfo(dev, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t), &max_work_group_size, NULL);
  printf("max work group size: %zu\n", max_work_group_size);

  size_t local_size[2] = {16, 15};
  // N = round_up(N, local_size[0]);
  // M = round_up(M, local_size[1]);
  size_t global_size[2] = {round_up(N, local_size[0]), round_up(M, local_size[1])};
  printf("Using N = %zu, K = %zu, M = %zu\n", N, K, M);
  printf("Global size is: %zu %zu", global_size[0], global_size[1]);
  cl_context context = clCreateContext(NULL, 1, &dev, NULL, NULL, &ret);
  CHECK_CL_ERROR(ret, "Creating context");
  cl_command_queue queue = clCreateCommandQueueWithProperties(context, dev, 0, &ret);
  CHECK_CL_ERROR(ret, "Creating command queue");
  double exec_time_ms;
  run_matrix_mul_naive_nn(context, queue, dev, N, K, M, global_size, local_size, &exec_time_ms);

  print_run_summary(N, K, M, exec_time_ms);

  ret = clReleaseCommandQueue(queue);
  WARN_CL_RELEASE(ret, "command queue");
  ret = clReleaseContext(context);
  WARN_CL_RELEASE(ret, "context");
  if (first_error != CL_SUCCESS) {
    CHECK_CL_ERROR(first_error, error_context);
  }
  return 0;
}
