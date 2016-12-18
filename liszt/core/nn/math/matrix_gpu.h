#ifndef MATRIX_GPU_H
#define MATRIX_GPU_H

#include <curand.h>
#include <cublas_v2.h>


void fill_rand_gpu(float *A, int A_rows, int A_cols)
{
    // create a pseudo-random number generator
    curandGenerator_t curand_gen;
    curandCreateGenerator(&curand_gen, CURAND_RNG_PSEUDO_DEFAULT);

    // set the seed for the random number generator using the system clock
    curandSetPseudoRandomGeneratorSeed(curand_gen, (unsigned long long) clock());

    // fill the array with random numbers on the device
    curandGenerateUniform(curand_gen, A, A_rows * A_cols);
 
}


void cublas_mmul(const float *A,
                 const float *B,
                 float *C,
                 const int m,
                 const int k,
                 const int n)
{
    int lda = m;
    int ldb = k;
    int ldc = m;

    const float alf = 1;
    const float bet = 0;
    const float *alpha = &alf;
    const float *beta = &bet;

    // create a handle for cublas
    cublasHandle_t handle;
    cublasCreate(&handle);

    // do the actual multiplicatioin
    cublasSgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc);

    // destroy the handle
    cublasDestroy(handle);
}


void cublas_sgeam(float *A,
                  float *A_T,
                  int n_rows,
                  int n_cols)
{
    const float alpha = 1.0;
    const float beta = 1.0;

    cublasHandle_t handle;
    cublasCreate(&handle);

    cublasSgeam(handle, CUBLAS_OP_T, CUBLAS_OP_N, n_rows, n_cols, &alpha, A, n_cols, &beta, A, n_rows, A_T, n_rows);

    cublasDestroy(handle);
}

#endif
