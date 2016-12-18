#ifndef ELM_H_
#define ELM_H_

#include <stdint.h>
#include <armadillo>

using namespace arma;


class ELM
{
    private:
        
        // input parameters
        uint16_t N_Hidden;  // number of hidden neurons
        uint16_t Dim;         // data dimension
        uint16_t N_Samples;    // number of data samples

        // network parameters (cpu)
        mat weight;
        vec bias;
        mat beta;
        uint16_t activation;

        // evaluation
        double train_time;
        double test_time;
        double train_accuracy;
        double test_accuracy;


    public:

        // common
        void set_dim(uint16_t n_hidden, uint16_t dim, uint16_t n_samples);
        void save_model();

        // CPU
        // CPU: network
        void init_nn_params();  // initialize weights and biases
        void config_nn(uint16_t n_hidden, uint16_t dim, uint16_t n_samples);
        // CPU: train/test
        bool train(mat &train_X, mat &train_Y, uint16_t activation);
        bool test(mat &test_X, mat &test_Y, uint16_t activation);

};


class ELMGPU
{
    private:

        // input parameter
        uint16_t N_Hidden; // number of hidden neurons
        uint16_t Dim;      // data dimension
        uint16_t N_Samples;  // number of data samples

        // model parameters
        float *h_weight, *d_weight;
        float *h_bias, *d_bias;

    public:
        void set_dim(uint16_t n_hidden, uint16_t dim, uint16_t n_samples);
        void init_nn_params();
        void config_nn(uint16_t n_hidden, uint16_t dim, uint16_t n_samples);

        // train/test
        bool train(fmat train_X, fmat train_Y, uint16_t activation);
        bool test(float *h_test_X, float *h_test_Y, uint16_t activation);
};

#endif
