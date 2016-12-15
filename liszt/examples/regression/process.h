#ifndef PROCESS_H
#define PROCESS_H


#include "../../core/model/elm.h"


void elm_cpu()
{

    // initialize data
    mat x;
    mat y;
    x.load("data/regression_dummy/x_train.csv", csv_ascii);
    y.load("data/regression_dummy/y_train.csv", csv_ascii);

    // initialize model params
    int n_hidden = 2000;
    int dim = x.n_cols;
    int n_samples = x.n_rows;
    int activation = 0;  // sigmoid
    // initialize nn
    ELM elm;
    elm.config_nn(n_hidden, dim, n_samples);

    // train
    bool r = elm.train(x, y, activation);

    // test
    x.load("data/regression_dummy/x_test.csv", csv_ascii);
    y.load("data/regression_dummy/y_test.csv", csv_ascii);
    r = elm.test(x, y, activation);

}


void elm_gpu()
{

    cout << "ELM GPU" << endl;

    // initialize data
    mat x;
    mat y;
    x.load("data/regression_dummy/x_train.csv", csv_ascii);
    y.load("data/regression_dummy/y_train.csv", csv_ascii);

    // initialize model params
    int n_hidden = 2000;
    int dim = x.n_cols;
    int n_samples = x.n_rows;
    int activation = 0;  // sigmoid
    // initialize nn
    ELM elm;
    elm.config_nn(n_hidden, dim, n_samples);

    // train
    bool r = elm.train_gpu(x, y, activation);

    // test
    // x.load("data/regression_dummy/x_test.csv", csv_ascii);
    // y.load("data/regression_dummy/y_test.csv", csv_ascii);
    // r = elm.test(x, y, activation);

}

#endif
