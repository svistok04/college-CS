#include "opencl_helper.h"
#include "pgm.h"

int main() {
    int width, height;
    unsigned char* input = read_pgm("output.pgm", &width, &height);
    if (!input) {
        fprintf(stderr, "Failed to read input PGM file.\n");
        return 1;
    }

    unsigned char* output = malloc(width * height);
    if (!output) {
        fprintf(stderr, "Failed to allocate output buffer.\n");
        free(input);
        return 1;
    }

    init_opencl();
    char* error_context;
    cl_device_id dev = devices[0].device;
    cl_int ret;

    cl_context context = clCreateContext(NULL, 1, &dev, NULL, NULL, &ret);
    cl_command_queue queue = clCreateCommandQueueWithProperties(context, dev, 0, &ret);

    char* source = load_kernel_source("img_rotation.cl");
    size_t source_size = strlen(source);
    cl_program program = clCreateProgramWithSource(context, 1, (const char**)&source, &source_size, &ret);
    clBuildProgram(program, 1, &dev, NULL, NULL, NULL);

    cl_kernel kernel = clCreateKernel(program, "rotate_90", &ret);

    cl_mem input_buf = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, width * height, input, &ret);
    cl_mem output_buf = clCreateBuffer(context, CL_MEM_WRITE_ONLY, width * height, NULL, &ret);

    ret  = clSetKernelArg(kernel, 0, sizeof(cl_mem), &input_buf);
    RECORD_ERROR(ret, "Arg 0");
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), &output_buf);
    RECORD_ERROR(ret, "Arg 1");
    ret = clSetKernelArg(kernel, 2, sizeof(int), &width);
    RECORD_ERROR(ret, "Arg 2");
    ret = clSetKernelArg(kernel, 3, sizeof(int), &height);
    RECORD_ERROR(ret, "Arg 3");

    size_t global_size[2] = {width, height};
    clEnqueueNDRangeKernel(queue, kernel, 2, NULL, global_size, NULL, 0, NULL, NULL);
    RECORD_ERROR(ret, "Enqueue Kernel");
    clFinish(queue);
    RECORD_ERROR(ret, "Finish");

    clEnqueueReadBuffer(queue, output_buf, CL_TRUE, 0, width * height, output, 0, NULL, NULL);

    write_pgm("output_rotated.pgm", output, height, width);

    clReleaseMemObject(input_buf);
    clReleaseMemObject(output_buf);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);
    free(source);
    free(input);
    free(output);

    printf("saved as output_rotated.pgm\n");
    return 0;
}
