#include <math.h>
#include <random>

#include "elm.h"

using namespace std;

// ---------------------------------------------------------------------------
// initialize network


void ELM::set_dim(uint16_t n_hidden, uint16_t dim, uint16_t n_samples)
{
    N_Hidden = n_hidden;
    Dim = dim;
    N_Samples = n_samples;
}



// initialize weights and bias
void ELM::init_nn_params()
{
    mt19937 engine(time(0));  // Mersenne twister random number engine
    uniform_real_distribution<double> distr(1.0, 2.0);
    weight.set_size(N_Hidden, Dim);
    // cout << "n_hidden" << N_Hidden << endl;
    // cout << "weight: " << weight << endl;
    weight.imbue([&](){ return distr(engine); });

    bias.randu(N_Hidden, 1);
}


void ELM::config_nn(uint16_t n_hidden, uint16_t dim, uint16_t n_samples)
{
    set_dim(n_hidden, dim, n_samples);
    arma_rng::set_seed_random();
    init_nn_params();
}


// ---------------------------------------------------------------------------
// train/test process


bool ELM::train(mat &train_X, mat &train_Y, uint16_t activation)
{
    wall_clock timer;
    mat param;

    timer.tic();
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

    return true;
        
}


bool ELM::test(mat &test_X, mat &test_Y, uint16_t activation)
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


void ELM::save_model()
{
    weight.save("weights.csv", csv_ascii);
    bias.save("bias.csv", csv_ascii);
    beta.save("beta.csv", csv_ascii); 
}

