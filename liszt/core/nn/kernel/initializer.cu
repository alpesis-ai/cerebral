#include "initializer.h"

void fill(int *d_a, int n)
{
    int nThreadsPerBlock = 1024;
    int nBlocks = n / nThreadsPerBlock + ((n % nThreadsPerBlock) ? 1:0);

    fillKernel<<<nBlocks, nThreadsPerBlock>>>(d_a, n);
}


void randomInit(float* theta, int in, int out, int M)
{
    randomInitKernel<<<N_BLOCKS(M), THREADS_PER_BLOCK>>>(theta, in, out, M);
}


__global__ void fillKernel(int *a, int n)
{
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if (tid < n)
    {
        a[tid] = 0;
    }
}


__global__ void randomInitKernel(float* theta, int in, int out, int M)
{
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    if (i < M)
    {
        float epsilon = (1 / sqrt((float)in));
        theta[i] = theta[i] * 2 * epsilon - epsilon;
    }
}
