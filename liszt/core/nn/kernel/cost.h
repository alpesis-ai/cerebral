#ifndef COST_H
#define COST_H

void negLnMax_gpu(float* h, float* y, float* J, int M);
void crossEntropy_gpu(float* h, float* y, float* J, int M);


__global__ void negLnMaxKernel(float* h, float* y, float* J, int M);
__global__ void crossEntropyKernel(float* h, float* y, float* J, int M);

#endif
