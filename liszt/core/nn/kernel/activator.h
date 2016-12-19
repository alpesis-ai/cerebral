#ifndef ACTIVATOR_H
#define ACTIVATOR_H

void sigmoid_gpu(const float* A, float* B, int M);
void sigmoidOutput_gpu(const float* A, float* B, int M, int N);
void sigmoidGrad_gpu(const float* A, float* B, int M);
void tanh_gpu(const float* A, float* B, int M);
void sechSq_gpu(const float* A, float* B, int M);
void softmax_gpu(const float* A, float* B, int M);

__global__ void sigmoidKernel(const float* A, float* B, int M);
__global__ void sigmoidGradKernel(const float* A, float* B, int M);
__global__ void tanhKernel(const float* A, float* B, int M);
__global__ void sechSqKernel(const float* A, float* B, int M);
__global__ void softmaxKernal(const float* A, float* B, int M, int N);

#endif
