#include <CL/cl_platform.h>
#include <cctype>
#include <cstddef>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <CL/cl.h>

// TODO attempt CL_MEM_USE_HOST_PTR if no SVM available and verify whether it assures zero-copy
#define MB_INT_BUFFER_ALLOC_CAP 1250UL * sizeof(int) * 1024 * 1024

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
  exit(EXIT_FAILURE); \
}

const char kernelSourceCode[]=
  "__kernel void vector_add(__global int *A, __global int *B, __global int *C) {	\n"
  "  int i = get_global_id(0);													\n"		
  "	  C[i] = A[i] + B[i];														\n"
  "}																				\n"
;

typedef struct {
  cl_platform_id parent_platform;
  cl_device_id device;
} device_entry;

cl_platform_id* platforms = NULL;
cl_uint total_platforms = 0;

device_entry* devices = NULL;
cl_uint total_devices = 0;

size_t local_item_size = 64;

void clear_screen();
int init_opencl();
void print_platform_info_str(cl_platform_id platform, cl_platform_info param, const char* label);
void print_device_info_str(cl_device_id device, cl_device_info param, const char* label);
void list_available_platforms(cl_platform_id* platforms, cl_uint num_platforms);
void list_platform_info(cl_platform_id platform);
void list_device_info(cl_device_id device);
void list_available_devices(device_entry* devices, cl_uint num_devices);
void menu();
void run_vector_add_on_device(cl_device_id dev, cl_ulong vector_len);
size_t get_max_vector_len(cl_device_id dev, size_t element_size);
size_t round_up(size_t val, size_t multiple); 
size_t read_size_t_safely(const char* prompt);
//program wykonywany na HOSCIE - host program
int main(void) {
  init_opencl();
  menu();
  free(devices);
  free(platforms);
  return 0;
}

void clear_screen() {
  printf("\033[2J\033[H");
}

void wait_for_enter() {
  printf("\nPress Enter to return to menu...");
  getchar();
}

void print_platform_info_str(cl_platform_id platform, cl_platform_info param, const char* label) {
  size_t size;
  cl_int err;
  err = clGetPlatformInfo(platform, param, 0, NULL, &size);
  CHECK_CL_ERROR(err, "Getting platform info size");

  char* value = (char*)malloc(size);
  err = clGetPlatformInfo(platform, param, size, value, NULL);
  if (err != CL_SUCCESS) {
    free(value);
    CHECK_CL_ERROR(err, "Getting platform info string");
  }

  printf("%s: %s\n", label, value);
  free(value);
}

void print_device_info_str(cl_device_id device, cl_device_info param, const char* label) {
  size_t size;
  cl_int err;
  err = clGetDeviceInfo(device, param, 0, NULL, &size);
  CHECK_CL_ERROR(err, "Getting device info size");

  char* value = (char*)malloc(size);
  err = clGetDeviceInfo(device, param, size, value, NULL);
  if (err != CL_SUCCESS) {
    free(value);
    CHECK_CL_ERROR(err, "Getting device info string");
  }

  printf("%s: %s\n", label, value);
  free(value);
}

int init_opencl() {
  cl_int err = clGetPlatformIDs(0, NULL, &total_platforms);
  CHECK_CL_ERROR(err, "Fetching number of OpenCL platforms");
  // if (total_platforms == 0) {
  //   printf("No OpenCL platforms found. Error code: %d\n", err);
  //   return 0;
  // }

  platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id) * total_platforms);
  err = clGetPlatformIDs(total_platforms, platforms, NULL);
  CHECK_CL_ERROR(err, "Fetching platform IDs");

  for (cl_uint i = 0; i < total_platforms; ++i) {
    cl_uint devices_on_this_platform = 0;
    err = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &devices_on_this_platform);
    if (err == CL_SUCCESS) {
      total_devices += devices_on_this_platform;
    }
  }

  if (total_devices == 0) {
    printf("No OpenCL devices found on any platform.\n");
    return 0;
  }

  devices = (device_entry*)malloc(sizeof(device_entry) * total_devices);

  cl_uint device_index = 0;
  for (cl_uint i = 0; i < total_platforms; ++i) {
    cl_uint devices_on_this_platform;
    err = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &devices_on_this_platform);
    if (err != CL_SUCCESS || devices_on_this_platform == 0) {
      fprintf(stderr, "Skipping platform %d: no devices. Code: %d\n", i, err);
      continue;
    }
    cl_device_id* temp_devices = (cl_device_id*)malloc(sizeof(cl_device_id) * devices_on_this_platform);
    err = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, devices_on_this_platform, temp_devices, NULL);
    if (err != CL_SUCCESS) {
      free(temp_devices);
      CHECK_CL_ERROR(err, "Fetching device IDs for platform");
    }
    for (cl_uint j = 0; j < devices_on_this_platform; ++j) {
      devices[device_index].device = temp_devices[j];
      devices[device_index].parent_platform = platforms[i];
      ++device_index;
    }
    free(temp_devices);
  }
  printf("Initialized OpenCL: %u platforms, %u devices.\n", total_platforms, total_devices);
  return 1;
}



void list_available_devices(device_entry* devices, cl_uint num_devices) {
  for (cl_uint i = 0; i < num_devices; ++i) {
    cl_int err;
    size_t device_name_size, platform_name_size;

    err = clGetDeviceInfo(devices[i].device, CL_DEVICE_NAME, 0, NULL, &device_name_size);
    CHECK_CL_ERROR(err, "Getting size of device name");
    char* device_name = (char*)malloc(device_name_size);
    err = clGetDeviceInfo(devices[i].device, CL_DEVICE_NAME, device_name_size, device_name, NULL);
    if (err != CL_SUCCESS) {
      free(device_name);
      CHECK_CL_ERROR(err, "Getting device name");
    }

    err = clGetPlatformInfo(devices[i].parent_platform, CL_PLATFORM_NAME, 0, NULL, &platform_name_size);
    CHECK_CL_ERROR(err, "Getting size of platform name");
    char* platform_name = (char*)malloc(platform_name_size);
    err = clGetPlatformInfo(devices[i].parent_platform, CL_PLATFORM_NAME, platform_name_size, platform_name, NULL);
    if (err != CL_SUCCESS) {
      free(device_name);
      free(platform_name);
      CHECK_CL_ERROR(err, "Getting platform name");
    }

    printf("%u. %s (Platform: %s)\n", i + 1, device_name, platform_name);

    free(device_name);
    free(platform_name);
  }
}


void list_available_platforms(cl_platform_id* platforms, cl_uint num_platforms) {
  for (cl_uint i = 0; i < num_platforms; ++i) {
    size_t infoSize;
    cl_int err = clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, 0, NULL, &infoSize);
    CHECK_CL_ERROR(err, "Getting platform name size");

    char* name = (char*)malloc(infoSize);

    err = clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, infoSize, name, NULL);
    if (err != CL_SUCCESS) {
      free(name);
      CHECK_CL_ERROR(err, "Getting platform name string");
    }

    printf("%u. %s\n", i + 1, name);
    free(name);
  }
}


void list_platform_info(cl_platform_id platform) {
  printf("\n");
  print_platform_info_str(platform, CL_PLATFORM_NAME, "Platform name");
  print_platform_info_str(platform, CL_PLATFORM_VENDOR, "Platform vendor");
  print_platform_info_str(platform, CL_PLATFORM_VERSION, "Platform version");

  cl_uint num_devices = 0;
  cl_int err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 0, NULL, &num_devices);
  if (err != CL_SUCCESS || num_devices == 0) {
    printf("No devices found on this platform.\n");
    return;
  }

  printf("Number of devices on this platform: %u\n", num_devices);

  cl_device_id* devs = (cl_device_id*)malloc(sizeof(cl_device_id) * num_devices);
  err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, num_devices, devs, NULL);
  if (err != CL_SUCCESS) {
    free(devs);
    CHECK_CL_ERROR(err, "Getting device list for platform");
  }

  printf("Devices: ");
  for (cl_uint i = 0; i < num_devices; ++i) {
    size_t name_size;
    err = clGetDeviceInfo(devs[i], CL_DEVICE_NAME, 0, NULL, &name_size);
    if (err != CL_SUCCESS) {
      free(devs);
      CHECK_CL_ERROR(err, "Getting size of device name");
    }

    char* name = (char*)malloc(name_size);
    err = clGetDeviceInfo(devs[i], CL_DEVICE_NAME, name_size, name, NULL);
    if (err != CL_SUCCESS) {
      free(name);
      free(devs);
      CHECK_CL_ERROR(err, "Getting device name");
    }

    printf("%s", name);
    if (i != num_devices - 1) printf(", ");
    free(name);
  }

  printf("\n");
  free(devs);
}

void list_device_info(cl_device_id device) {
  printf("\n");
  print_device_info_str(device, CL_DEVICE_NAME, "Device name");
  print_device_info_str(device, CL_DEVICE_VENDOR, "Device vendor");
  print_device_info_str(device, CL_DRIVER_VERSION, "Driver version");
  print_device_info_str(device, CL_DEVICE_VERSION, "Device version");
  print_device_info_str(device, CL_DEVICE_OPENCL_C_VERSION, "OpenCL C version");

  cl_device_svm_capabilities svm_caps = 0;
  cl_int err = clGetDeviceInfo(device, CL_DEVICE_SVM_CAPABILITIES, sizeof(svm_caps), &svm_caps, NULL);
  if (err == CL_SUCCESS && svm_caps != 0) {
    printf("SVM supported! Caps = 0x%lx\n", svm_caps);
  } else {
    printf("SVM not supported or OpenCL < 2.0\n");
  }
  // print_device_info_str(device, CL_DEVICE_SVM_CAPABILITIES, "svm");
  for (cl_uint i = 0; i < total_devices; ++i) {
    if (devices[i].device == device) {
      print_platform_info_str(devices[i].parent_platform, CL_PLATFORM_NAME, "Parent platform");
      break;
    }
  }
}

void menu() {
  size_t choice = SIZE_MAX;
  while (choice != 0) {
    clear_screen();
    printf("\n==== OpenCL Menu ====\n");
    printf("1. List platforms\n");
    printf("2. List devices\n");
    printf("3. Run test\n");
    printf("0. Exit\n");
    choice = read_size_t_safely("Choose an option: ");

    switch ((int)choice) {
      case 1: {
        clear_screen();
        list_available_platforms(platforms, total_platforms);
        size_t index = read_size_t_safely("Enter platform number (0 to cancel): ");
        if (index > 0 && index <= total_platforms) {
          clear_screen();
          list_platform_info(platforms[index - 1]);
        } else if (index == 0) {
          printf("Canceled\n");
        } else {
          printf("Invalid index.\n");
        }
        wait_for_enter();
        break;
      }
      case 2: {
        clear_screen();
        list_available_devices(devices, total_devices);
        size_t index = read_size_t_safely("Enter device number (0 to cancel): ");
        if (index > 0 && index <= total_devices) {
          clear_screen();
          list_device_info(devices[index - 1].device);
        } else if (index == 0) {
          printf("Canceled\n");
        } else {
          printf("Invalid index.\n");
        }
        wait_for_enter();
        break;
      }
      case 3: {
        clear_screen();
        size_t sub_choice = SIZE_MAX;
        while (sub_choice != 0) {
          printf("\n[Run Test Menu]\n");
          printf("1. Run on all devices\n");
          for (cl_uint i = 0; i < total_devices; ++i) {
            char name[256];
            clGetDeviceInfo(devices[i].device, CL_DEVICE_NAME, sizeof(name), name, NULL);
            printf("%u. Run on device %u: %s\n", i + 2, i, name);
          }
          printf("0. Back to main menu\n");
          sub_choice = read_size_t_safely("Choose an option: ");
          clear_screen();

          size_t user_len;
          if (sub_choice > 0) {
            user_len = read_size_t_safely("Enter vector length (0 for max per device): ");
            clear_screen();
          }

          if (sub_choice == 1) {

            for (cl_uint i = 0; i < total_devices; ++i) {
              size_t max_len = get_max_vector_len(devices[i].device, sizeof(int));
              size_t actual_len = (user_len == 0 || user_len > max_len)
                ? max_len
                : round_up(user_len, 64);  // or round down if you prefer strict caps

              if (user_len > max_len) {
                printf("Device %d: requested size %zu too large, using max %zu instead\n",
                       i, user_len, max_len);
              } else if (user_len % 64 != 0) {
                printf("Warning: vector length %zu is not divisible by local work-group size 64.\n", user_len);
                printf("Rounding up to %zu.\n\n", actual_len);
              }
              run_vector_add_on_device(devices[i].device, actual_len);
            }
            wait_for_enter();
            clear_screen();
          } else if (sub_choice >= 2 && sub_choice < (total_devices + 2)) {
            cl_uint target = sub_choice - 2;
            printf("Running test on device %u...\n", target);
            size_t max_len = get_max_vector_len(devices[target].device, sizeof(int));
              size_t actual_len = (user_len == 0 || user_len > max_len)
                ? max_len
                : round_up(user_len, 64);  // or round down if you prefer strict caps

              if (user_len > max_len) {
              printf("Requested size %zu too large, using max %zu instead\n", user_len, max_len);
              } else if (user_len % 64 != 0) {
                printf("Warning: vector length %zu is not divisible by local work-group size 64.\n", user_len);
                printf("Rounding up to %zu.\n\n", actual_len);
              }
            run_vector_add_on_device(devices[target].device, actual_len);
            wait_for_enter();
            clear_screen();
          } else if (sub_choice != 0) {
            printf("Invalid option.\n");
          }
        }
        break;
      }
      case 0:
        clear_screen();
        printf("Exiting...\n");
        break;
      default: 
        printf("Invalid option. Try again.\n");
    }
  }
}

void run_vector_add_on_device(cl_device_id dev, cl_ulong vector_len) {
  cl_int ret;
  cl_int first_error = CL_SUCCESS;
  const char* error_context = NULL;

  printf("\n");
  print_device_info_str(dev, CL_DEVICE_NAME, "Device name");

  cl_ulong max_alloc;
  ret = clGetDeviceInfo(dev, CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(cl_ulong), &max_alloc, NULL);
  size_t max_vector_len = get_max_vector_len(dev, sizeof(int));
  size_t data_size = vector_len * sizeof(int);

  cl_context context = clCreateContext(NULL, 1, &dev, NULL, NULL, &ret);
  CHECK_CL_ERROR(ret, "Creating context");
  cl_command_queue command_queue = clCreateCommandQueueWithProperties(context, dev, 0, &ret);
  // CHECK_CL_ERROR(ret, "Creating command queue");
  // cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, vector_len * sizeof(int), NULL, &ret);
  // CHECK_CL_ERROR(ret, "Creating buffer A");
  // cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, vector_len * sizeof(int), NULL, &ret);
  // CHECK_CL_ERROR(ret, "Creating buffer B");
  // cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, vector_len * sizeof(int), NULL, &ret);
  // CHECK_CL_ERROR(ret, "Creating buffer C");

  int* A = (int*)clSVMAlloc(context, CL_MEM_READ_ONLY, vector_len * sizeof(int), 0);
  int* B = (int*)clSVMAlloc(context, CL_MEM_READ_ONLY, vector_len * sizeof(int), 0);
  int* C = (int*)clSVMAlloc(context, CL_MEM_WRITE_ONLY, vector_len * sizeof(int), 0);
  for (size_t i = 0; i < vector_len; ++i) {
    A[i] = i;
    B[i] = vector_len - i;
  }
  // ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0, vector_len * sizeof(int), A, 0, NULL, NULL);
  // RECORD_ERROR(ret, "Writing buffer A");
  // ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0, vector_len * sizeof(int), B, 0, NULL, NULL);
  // RECORD_ERROR(ret, "Writing buffer B");
  const char* source = kernelSourceCode;
  const size_t source_size = strlen(kernelSourceCode);
  cl_program program = clCreateProgramWithSource(context, 1, &source, &source_size, &ret);
  RECORD_ERROR(ret, "Creating program from source");

  ret = clBuildProgram(program, 1, &dev, NULL, NULL, NULL);
  RECORD_ERROR(ret, "Building program");
  if (ret != CL_SUCCESS) {
    size_t log_size;
    clGetProgramBuildInfo(program, dev, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
    char* log = (char*)malloc(log_size);
    clGetProgramBuildInfo(program, dev, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
    fprintf(stderr, "Build error:\n%s\n", log);
    free(log);
    free(A);
    free(B);
    free(C);
    CHECK_CL_ERROR(first_error, error_context); 
  }

  cl_kernel kernel = clCreateKernel(program, "vector_add", &ret);
  RECORD_ERROR(ret, "Creating kernel");

  clSetKernelArgSVMPointer(kernel, 0, A);
  RECORD_ERROR(ret, "Setting kernel arg 0");
  clSetKernelArgSVMPointer(kernel, 1, B);
  RECORD_ERROR(ret, "Setting kernel arg 1");
  clSetKernelArgSVMPointer(kernel, 2, C);
  RECORD_ERROR(ret, "Setting kernel arg 2");
  // ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&a_mem_obj);
  // ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&b_mem_obj);
  // ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&c_mem_obj);
  // ret = clSetKernelArg(kernel, 3, sizeof(int), (void*)&vector_len);
  // RECORD_ERROR(ret, "Setting kernel arg 3");

  size_t global_item_size = vector_len;

  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
  RECORD_ERROR(ret, "Enqueuing kernel");
  ret = clFinish(command_queue);
  RECORD_ERROR(ret, "Finishing queue");

  clock_gettime(CLOCK_MONOTONIC, &end);

  // ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0, vector_len * sizeof(int), C, 0, NULL, NULL);
  // RECORD_ERROR(ret, "Reading buffer C");

  // for(int i = 0; i < vector_len; i++)
  //printf("%d + %d = %d\n", A[i], B[i], C[i]);

  double time_ms = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1e6;
  printf("Vector size: %zu elements (%.2f MB per buffer)\n", vector_len, data_size / (1024.0 * 1024.0));
  printf("Execution time: %.3f ms\n", time_ms);
  printf("-----------------------------\n");
  ret = clReleaseKernel(kernel);
  WARN_CL_RELEASE(ret, "kernel");
  ret = clReleaseProgram(program);
  WARN_CL_RELEASE(ret, "program");
  clSVMFree(context, A);
  // ret = clReleaseMemObject(a_mem_obj);
  WARN_CL_RELEASE(ret, "buffer A");
  // ret = clReleaseMemObject(b_mem_obj);
  clSVMFree(context, B);
  WARN_CL_RELEASE(ret, "buffer B");
  // ret = clReleaseMemObject(c_mem_obj);
  clSVMFree(context, C);
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
}

size_t get_max_vector_len(cl_device_id dev, size_t element_size) {
  cl_ulong max_alloc;
  cl_int ret = clGetDeviceInfo(dev, CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(cl_ulong), &max_alloc, NULL);

  CHECK_CL_ERROR(ret, "Getting max allocation size");
  cl_ulong safe_alloc = (MB_INT_BUFFER_ALLOC_CAP < max_alloc) ? MB_INT_BUFFER_ALLOC_CAP : max_alloc;

  return safe_alloc / element_size;
}

size_t round_up(size_t val, size_t multiple) {
  return (val + multiple - 1) / multiple * multiple;
}

size_t read_size_t_safely(const char* prompt) {
  char buffer[128];
  while (1) {
    printf("%s", prompt);
    if (!fgets(buffer, sizeof(buffer), stdin)) {
      printf("Input error.\n");
      continue;
    }

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
      buffer[len - 1] = '\0';

    char* ptr = buffer;
    while (isspace(*ptr)) ptr++;

    if (*ptr == '\0') {
      printf("Empty input. Please enter a number.\n");
      continue;
    }

    char* endptr;
    unsigned long long temp = strtoull(ptr, &endptr, 10);

    while (isspace(*endptr)) endptr++;
    if (*endptr != '\0') {
      printf("Invalid input. Please enter a non-negative integer.\n");
      continue;
    }

    return (size_t)temp;
  }
}
