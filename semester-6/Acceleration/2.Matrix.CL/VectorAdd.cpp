#include <CL/cl_platform.h>
#include <stdio.h>
#include <stdlib.h>
 
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

//#define vector_len  1024
const int vector_len = 1024;

const char kernelSourceCode[]=
"__kernel void vector_add(__global int *A, __global int *B, __global int *C) {	\n"
"  int i = get_global_id(0);													\n"		
"	  C[i] = A[i] + B[i];														\n"
"}																				\n"
;

void list_available_platforms(cl_platform_id* platforms, cl_uint num_platforms) {
  for (cl_uint i = 0; i < num_platforms; ++i) {
    char* name = NULL;
    size_t infoSize;
    clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, 0, NULL, &infoSize);
    name = (char*)malloc(infoSize);
    printf("%u. %s", i+1, name);
    free(name);
  }
}

void list_platform_info(cl_platform_id platform) {
  printf();

}

void list_device_info(cl_device_id device) {
  printf();
  
}

void list_available_devices() {
  printf();
}

//program wykonywany na HOSCIE - host program
int main(void) {
    cl_uint num_platforms = 0;
    cl_int err = clGetPlatformIDs(0, NULL, &num_platforms);
    if (err != CL_SUCCESS || num_platforms == 0) {
        printf("No OpenCL platforms found. Error code: %d\n", err);
        return 1;
    }

    printf("Number of platforms available: %u\n", num_platforms);

    cl_platform_id* platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id) * num_platforms);
    clGetPlatformIDs(num_platforms, platforms, NULL);

    for (cl_uint i = 0; i < num_platforms; ++i) {
        printf("\nPlatform %u\n", i);

        char* info = NULL;
        size_t infoSize;

        clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, 0, NULL, &infoSize);
        info = (char*)malloc(infoSize);
        clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, infoSize, info, NULL);
        printf("Platform name: %s\n", info);
        free(info);

        clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, 0, NULL, &infoSize);
        info = (char*)malloc(infoSize);
        clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, infoSize, info, NULL);
        printf("Platform vendor: %s\n", info);
        free(info);

        clGetPlatformInfo(platforms[i], CL_PLATFORM_VERSION, 0, NULL, &infoSize);
        info = (char*)malloc(infoSize);
        clGetPlatformInfo(platforms[i], CL_PLATFORM_VERSION, infoSize, info, NULL);
        printf("Platform version: %s\n", info);
        free(info);

        cl_uint num_devices = 0;
        err = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &num_devices);
        if (err != CL_SUCCESS || num_devices == 0) {
            printf("No devices found on this platform. Error code: %d\n", err);
            continue;
        }

        printf("Number of devices on this platform: %u\n", num_devices);

        cl_device_id* devices = (cl_device_id*)malloc(sizeof(cl_device_id) * num_devices);
        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, num_devices, devices, NULL);

        for (cl_uint j = 0; j < num_devices; ++j) {
            printf("\nDevice %u\n", j);

            clGetDeviceInfo(devices[j], CL_DEVICE_NAME, 0, NULL, &infoSize);
            info = (char*)malloc(infoSize);
            clGetDeviceInfo(devices[j], CL_DEVICE_NAME, infoSize, info, NULL);
            printf("  Device name: %s\n", info);
            free(info);

            clGetDeviceInfo(devices[j], CL_DEVICE_VENDOR, 0, NULL, &infoSize);
            info = (char*)malloc(infoSize);
            clGetDeviceInfo(devices[j], CL_DEVICE_VENDOR, infoSize, info, NULL);
            printf("  Device vendor: %s\n", info);
            free(info);

            clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, 0, NULL, &infoSize);
            info = (char*)malloc(infoSize);
            clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, infoSize, info, NULL);
            printf("  Driver version: %s\n", info);
            free(info);

            clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, 0, NULL, &infoSize);
            info = (char*)malloc(infoSize);
            clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, infoSize, info, NULL);
            printf("  Device version: %s\n", info);
            free(info);

            clGetDeviceInfo(devices[j], CL_DEVICE_OPENCL_C_VERSION, 0, NULL, &infoSize);
            info = (char*)malloc(infoSize);
            clGetDeviceInfo(devices[j], CL_DEVICE_OPENCL_C_VERSION, infoSize, info, NULL);
            printf("  OpenCL C version: %s\n", info);
            free(info);
        }

        free(devices);
    }

    free(platforms);   // Create the two input vectors
    int i;
    int *A = (int*)malloc(sizeof(int)*vector_len); 
    int *B = (int*)malloc(sizeof(int)*vector_len);
    for(i = 0; i < vector_len; i++) {
        A[i] = i;
        B[i] = vector_len - i;
    }
 	// start kodu w OpenCL
    // Get platform information
    cl_platform_id platform_id = NULL; 
    cl_device_id device_id = NULL;   
    cl_uint ret_num_devices; 
    cl_uint ret_num_platforms;
	
	cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	// Get device information
    	ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
	
	// Create an OpenCL context
	cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);
	
    // Create a command queue
	cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
	// Create memory buffers on the device for each vector 
    cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, vector_len * sizeof(int), NULL, &ret);
    cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, vector_len * sizeof(int), NULL, &ret);
	cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, vector_len * sizeof(int), NULL, &ret);
 
	// Copy the lists A and B to their respective memory buffers
	ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0, vector_len * sizeof(int), A, 0, NULL, NULL);
    ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0, vector_len * sizeof(int), B, 0, NULL, NULL);
 
    // Create a program from the kernel source
    const char* source = kernelSourceCode;
	const size_t source_size = sizeof(kernelSourceCode);
	cl_program program = clCreateProgramWithSource(context, 1, &source, &source_size, &ret);
	
    // Build the program
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
	
    // Create the OpenCL kernel
	cl_kernel kernel = clCreateKernel(program, "vector_add", &ret);
 
    // Set the arguments of the kernel
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&b_mem_obj);
    ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&c_mem_obj);
	//ret = clSetKernelArg(kernel, 3, sizeof(int), (void *)&vector_len);
    
	// Execute the OpenCL kernel on the list
	// def rozmiaru NDRange
	// rozmiar globalny
    size_t global_item_size = vector_len; // Process the entire lists//
	size_t local_item_size = 64; // Divide work items into groups of 64
	//uruchomienie kernela na NDRange
    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
	
	ret = clFinish(command_queue);

    // Read the memory buffer C on the device to the local variable C
    int *C = (int*)malloc(sizeof(int)*vector_len);
    // Read the result
	ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0, vector_len * sizeof(int), C, 0, NULL, NULL);

    // Display the result to the screen
	for(i = 0; i < vector_len; i++)
        //printf("%d + %d = %d\n", A[i], B[i], C[i]);
 
    // Clean up
	ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(a_mem_obj);
    ret = clReleaseMemObject(b_mem_obj);
    ret = clReleaseMemObject(c_mem_obj);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);
    free(A);
    free(B);
    free(C);
    char buf[100];
    fgets(buf, 100, stdin);
    return 0;
}
