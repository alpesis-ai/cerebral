#include "activator.h"


void sigmoid_gpu(const float* A, float* B, int M)
{
    sigmoidKernel<<<N_BLOCKS(M), THREADS_PER_BLOCK>>>(A, B, M);
}


void sigmoidOutput_gpu(const float* A, float* B, int M, int N)
{
    sigmoidKernel<<<N_BLOCKS(M), THREADS_PER_BLOCK>>>(A, B, M*N);
}


void sigmoidGrad_gpu(const float* A, float* B, int M)
{
    sigmoidGradKernel<<<N_BLOCKS(M), THREADS_PER_BLOCK>>>(A, B, M);
}


void tanh_gpu(const float* A, float* B, int M)
{
    tanhKernel<<<N_BLOCKS(M), THREADS_PER_BLOCK>>>(A, B, M);
}


void sechSq_gpu(const float* A, float* B, int M)
{
    sechSqKernel<<<N_BLOCKS(M), THREADS_PER_BLOCK>>>(A, B, M);
}


void softmax_gpu(const float* A, float* B, int M)
{
    softmaxKernel<<<N_BLOCKS(M), THREADS_PER_BLOCK>>>(A, B, M);
}


__global__ void sigmoidKernel(const float* A, float* B, int M)
{
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    if (i < M)
    {
        B[i] = 1 / (1 + exp(-A[i]));
    }
}


__global__ void sigmoidGradKernel(const float* A, float* B, int M)
{
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    if (i < M)
    {
        float a = 1 / (1 + exp(-A[i]));
        B[i] = a * (1 - a);
    }
}


__global__ void tanhKernel(const float* A, float* B, int M)
{
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    if (i < M)
    {
        B[i] = tanh(A[i]);
    }
}


__global__ void sechSqKernel(const float* A, float* B, int M)
{
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    if (i < M)
    {
        float c = cosh(A[i]);
        B[i] = 1 / (c * c);
    }
}


__global__ void softmaxKernel(const float* A, float* B, int M, int N)
{
    // the idiot-proof un-optimised algorithm
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    if (i < M)
    {
        float total = 0;
        for (int j = 0; j < N; j++)
            total += exp(A[IDX2C(i, j, M)]);

        for (int j = 0; j < N; j++)
            B[IDX2C(i, j, M)] = exp(A[IDX2C(i, j, M)]) / total;
    }
}
