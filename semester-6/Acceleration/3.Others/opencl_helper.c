#include "opencl_helper.h"

cl_platform_id* platforms = NULL;
device_entry* devices = NULL;
cl_uint total_platforms = 0;
cl_uint total_devices = 0;

int init_opencl() {
  cl_int err = clGetPlatformIDs(0, NULL, &total_platforms);
  CHECK_CL_ERROR(err, "Fetching number of OpenCL platforms");

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

char* load_kernel_source(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) { perror("fopen"); exit(1); }
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);
    char* buf = malloc(size + 1);
    fread(buf, 1, size, fp);
    buf[size] = 0;
    fclose(fp);
    return buf;
}

void check_succeeded(cl_int err) {
  switch(err) {
    case -1: printf("Device not found\n"); break;
    case -2: printf("Device not available\n"); break;
    case -3: printf("Compiler not available\n"); break;
    case -4: printf("Memory object allocation failure\n"); break;
    case -5: printf("Out of resources\n"); break;
    case -6: printf("Out of host memory\n"); break;
    case -7: printf("Profiling info not available\n"); break;
    case -8: printf("Memory copy overlap\n"); break;
    case -9: printf("Image format mismatch\n"); break;
    case -10: printf("Image format not supported\n"); break;
    case -11: printf("Build program failure\n"); break;
    case -12: printf("Map failure\n"); break;
    case -30: printf("Invalid value\n"); break;
    case -31: printf("Invaid device type\n"); break;
    case -32: printf("Invalid platform\n"); break;
    case -33: printf("Invalid device\n"); break;
    case -34: printf("Invalid context\n"); break;
    case -35: printf("Invalid queue properties\n"); break;
    case -36: printf("Invalid command queue\n"); break;
    case -37: printf("Invalid host pointer\n"); break;
    case -38: printf("Invalid memory object\n"); break;
    case -39: printf("Invalid image format descriptor\n"); break;
    case -40: printf("Invalid image size\n"); break;
    case -41: printf("Invalid sampler\n"); break;
    case -42: printf("Invalid binary\n"); break;
    case -43: printf("Invalid build options\n"); break;
    case -44: printf("Invalid program\n"); break;
    case -45: printf("Invalid program executable\n"); break;
    case -46: printf("Invalid kernel name\n"); break;
    case -47: printf("Invalid kernel defintion\n"); break;
    case -48: printf("Invalid kernel\n"); break;
    case -49: printf("Invalid argument index\n"); break;
    case -50: printf("Invalid argument value\n"); break;
    case -51: printf("Invalid argument size\n"); break;
    case -52: printf("Invalid kernel arguments\n"); break;
    case -53: printf("Invalid work dimension\n"); break;
    case -54: printf("Invalid work group size\n"); break;
    case -55: printf("Invalid work item size\n"); break;
    case -56: printf("Invalid global offset\n"); break;
    case -57: printf("Invalid event wait list\n"); break;
    case -58: printf("Invalid event\n"); break;
    case -59: printf("Invalid operation\n"); break;
    case -60: printf("Invalid GL object\n"); break;
    case -61: printf("Invalid buffer size\n"); break;
    case -62: printf("Invalid mip level\n"); break;
    case -63: printf("Invalid global work size\n"); break;
  }
}
