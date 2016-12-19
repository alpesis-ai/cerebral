#ifndef INITIALIZER_H
#define INITIALIZER_H

void fill(int *d_a, int);
void randomInit(float* theta, int in, int out, int M);

__global__ void fillKernel(int *a, int n);
__global__ void randomInitKernel(float* theta, int in, int out, int M);

#endif
