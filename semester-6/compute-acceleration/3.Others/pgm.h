#pragma once
#include "opencl_helper.h"

unsigned char* read_pgm(const char* filename, int* width, int* height);
void write_pgm(const char* filename, const unsigned char* data, int width, int height);
