#include "elm.h"
#include "../nn/math/matrix_gpu.h"
#include "../util/matrix_processor.h"
#include "../nn/math/matrix_gpu.h"


void ELMGPU::set_dim(uint16_t n_hidden, uint16_t dim, uint16_t n_samples)
{
    N_Hidden = n_hidden;
    Dim = dim;
    N_Samples = n_samples;
}


void ELMGPU::init_nn_params()
{
    // generate the weights
    h_weight = (float*)malloc(N_Hidden * Dim * sizeof(float));
    cudaMalloc(&d_weight, N_Hidden * Dim * sizeof(float));
    fill_rand_gpu(d_weight, N_Hidden * Dim * sizeof(float), cudaMemcpyDeviceToHost);
    
    // generate the bais
    h_bias = (float*)malloc(N_Hidden * 1 * sizeof(float));
    cudaMalloc(&d_bias, N_Hidden * 1 * sizeof(float));
    fill_rand_gpu(d_bias, N_Hidden, 1);  
}


void ELMGPU::config_nn(uint16_t n_hidden, uint16_t dim, uint16_t n_samples)
{
    set_dim(n_hidden, dim, n_samples);
    init_nn_params();
}


bool ELMGPU::train(fmat train_X, fmat train_Y, uint16_t activation)
{

    // host
    float* h_train_X = convert_matrix(train_X);
    float* h_train_Y = convert_matrix(train_Y);

    // device
    float *d_train_X;
    float *d_train_Y;
    cudaMalloc((void**)&d_train_X, train_X.n_rows * train_X.n_cols * sizeof(float));
    cudaMalloc((void**)&d_train_Y, train_Y.n_rows * train_Y.n_cols * sizeof(float));

    // host -> device
    cudaMemcpy(d_train_X, h_train_X, train_X.n_rows * train_X.n_cols * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_train_Y, h_train_Y, train_X.n_rows * train_X.n_cols * sizeof(float), cudaMemcpyHostToDevice);

    // transpose weight
    float* d_weight_t = (float*)malloc(N_Hidden * Dim * sizeof(float));
    cublas_sgeam(d_weight, d_weight_t, N_Hidden, Dim);
    // train_X * weight.t()
    // float* d_hidden = (float*)malloc(train_X.n_rows * N_Hidden * sizeof(float));
    // cublas_mmul(d_train_X, d_weight_t, d_hidden, train_X.n_rows, train_X.n_cols, N_Hidden);

    cudaFree(d_train_X);
    cudaFree(d_train_Y);
    cudaFree(d_weight_t);
    // cudaFree(d_hidden);

    return true;
}


bool ELMGPU::test(float *h_test_X, float *h_test_Y, uint16_t activation)
{
    return true;
}

