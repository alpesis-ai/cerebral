#include <math.h>
#include <random>

#include <cuda_runtime.h>
#include "cublas_v2.h"
#include "thrust/host_vector.h"
#include "thrust/device_vector.h"

#include "elm.h"

using namespace std;


// ---------------------------------------------------------------------------
// train/test: GPU


bool ELM::train_gpu(mat &train_X, mat &train_Y, uint16_t activation)
{
    wall_clock timer;
    mat param;

    // set up cuda and cublas
    cudaError_t cudaStat;     // cudaMalloc status
    cublasStatus_t stat;      // CUBLAS function status
    cublasHandle_t handle;    // CUBLAS context

    // initialization: gpu
    // thrust::device_vector<float> d_train_X(train_X.n_rows * train_X.n_cols);
    // thrust::device_vector<float> d_weight_t(weight.n_rows * weight.n_cols);
    float* d_train_X;
    float* d_weight_t;
    cudaStat = cudaMalloc((void**)& d_train_X, train_X.n_rows * train_X.n_cols);
    cudaStat = cudaMalloc((void**)& d_weight_t, weight.n_cols * weight.n_rows);

    stat = cublasCreate(&handle);
    //stat = cublasSetMatrix(

    timer.tic();
    /*
        param = train_X * weight.t(); 
        mat hidden = zeros(N_Samples, N_Hidden);

        double alpha = 0.2;
        double lambda = 5;
        activation = activation;

        cout << "activation: " << activation << endl;
        switch (activation)
        {
            case 0: // sigmoid
                for (int i = 0; i < hidden.n_rows; ++i)
                {
                    for (int j = 0; j < hidden.n_cols; ++j)
                    {
                        hidden(i, j) = 1.0 / (1.0 + exp(-(param(i,j) + bias(j))));
                    }
                }
                break;

            default:
                cout << "undefined activation function." << endl;
                return false;
        }

        mat hidden_inv = pinv(hidden);
        // cout << "hidden pseudoinverse: " << hidden_inv;

        beta = hidden_inv * train_Y;
        // cout << "beta: " << beta << endl;
    train_time = timer.toc();

    mat Y_hat = hidden * beta;
    vec temp = train_Y - Y_hat;

    double error = stddev(temp);
    cout << "(Train) RMSE = " << error << endl;
    cout << "Training time = " << train_time << endl;

    save_model();
    */

    return true;
        
}


bool ELM::test_gpu(mat &test_X, mat &test_Y, uint16_t activation)
{
    wall_clock timer;
    mat param;

    timer.tic();
        param = test_X * weight.t();
        mat hidden = zeros(N_Samples, N_Hidden);

        double alpha = 0.2;
        double lambda = 5;

        cout << "activation: " << activation << endl;
        switch(activation)
        {
            case 0:  // sigmoid
                for (int i = 0; i < hidden.n_rows; ++i)
                {
                    for (int j = 0; j < hidden.n_cols; ++j)
                    {
                        hidden(i, j) = 1.0 / (1.0 + exp(-(param(i,j) + bias(j))));
                    }
                }
                break;

            default:
                cout << "undefined activation function." << endl;
                return false;
        }

    test_time = timer.toc();
    
    mat Y_hat = hidden * beta;
    vec temp = test_Y - Y_hat;

    double error = stddev(temp);
    cout << "Test RMSE = " << error << endl;
    cout << "Testing time = " << test_time << " seconds." << endl;

    Y_hat.save("y_hat.csv", csv_ascii);

    return true;
}


