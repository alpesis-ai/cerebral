#include "cost.h"


void negLnMax_gpu(float* h, float* y, float* J, int M)
{
    negLnMaxKernel<<<N_BLOCKS(M), THREADS_PER_BLOCK>>>(h, y, J, M);
}


void crossEntropy_gpu(float* h, float* y, float* J, int M)
{
    crossEntropyKernel<<<N_BLOCKS(M), THREADS_PER_BLOCK>>>(h, y, J, M);
}


__global__ void negLnMaxKernel(float* h, float* y, float* J, int M)
{
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    if (i < M)
    {
        J[i] = -y[i] * log(h[i]) - (1 - y[i]) * log(1 - h[i]);
    }
}


__global__ void crossEntropyKernel(float* h, float* y, float* J, int M)
{
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    if (i < M)
    {
        J[i] = -y[i] * log(h[i]);
    }
}
