#pragma once
#include "opencl_helper.h"
#include <time.h>

void run_matrix_mul_naive_nn(
    cl_context context,
    cl_command_queue queue,
    cl_device_id device,
    size_t N, size_t K, size_t M,
    const size_t* global_size,
    const size_t* local_size, 
    double *exec_time_ms
);
