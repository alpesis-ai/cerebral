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

        // network parameters
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
        // initialize network
        void set_dim(uint16_t n_hidden, uint16_t dim, uint16_t n_samples);
        void init_nn_params();  // initialize weights and biases
        void config_nn(uint16_t n_hidden, uint16_t dim, uint16_t n_samples);
        
        // train/test process
        bool train(mat &train_X, mat &train_Y, uint16_t activation);
        bool test(mat &test_X, mat &test_Y, uint16_t activation);
        bool train_gpu(mat &train_X, mat &train_Y, uint16_t activation);
        bool test_gpu(mat &test_X, mat &test_Y, uint16_t activation);

        void save_model();
};

#endif
