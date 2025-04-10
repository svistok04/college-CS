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


//program wykonywany na HOSCIE - host program
int main(void) {
    // Create the two input vectors
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
        printf("%d + %d = %d\n", A[i], B[i], C[i]);
 
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
    return 0;
}