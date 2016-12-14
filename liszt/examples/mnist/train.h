#ifndef TRAIN_H
#define TRAIN_H

#include <fstream>
#include <iostream>

#include "settings.h"
#include "init_params.h"
#include "../../core/model/mlp.h"
#include "preprocessor.h"
#include "../../core/nn/errors.h"
#include "../../core/ops/io/model_saver.h"

using namespace std;


void desc_train()
{
    // descriptions
    cout << "*************************************************" << endl;
    cout << " MNIST Training System                           " << endl;
    cout << "*************************************************" << endl;
    cout << endl;
    cout << " - No. of input neurons: " << n1 << endl;
    cout << " - No. of hidden neurons: " << n2 << endl;
    cout << " - No. of output neurons: " << n3 << endl;
    cout << endl;
    cout << " - No. of iterations: " << epochs << endl;
    cout << " - Learning rate: " << learning_rate << endl;
    cout << " - Momentum: " << momentum << endl;
    cout << " - epsilon: " << epsilon << endl;
    cout << endl;
    cout << " - Training image X: " << training_image_fn << endl;
    cout << " - Training label Y: " << training_label_fn << endl;
    cout << " - No. of training samples: " << n_train << endl << endl;
}



int learning_process()
{
    // initialize delta1
    for (int i = 1; i <= n1; ++i)
    {
        for (int j = 1; j <= n2; ++j)
        {
            delta1[i][j] = 0.0;
        }
    }

    // initialize delta2
    for (int i = 1; i <= n2; ++i)
    {
        for (int j = 1; j <= n3; ++j)
        {
            delta2[i][j] = 0.0;
        }
    }

    // learning process: epoch loop
    for (int i = 1; i <= epochs; ++i)
    {
        forward();
        backward();
        if(square_error() < epsilon)
        {
           return i;
        }
    }
    return epochs;
}



void train_process()
{
    // file loading
    report.open(report_fn_train.c_str(), ios::out);
    image.open(training_image_fn.c_str(), ios::in | ios::binary);  // binary image file
    label.open(training_label_fn.c_str(), ios::in | ios::binary);  // binary label file


    // read the image and label files
    char number;
    for (int i = 1; i <= 16; ++i)
    {
        image.read(&number, sizeof(char));
    }
    for (int i = 1; i <= 8; ++i)
    {
        label.read(&number, sizeof(char));
    }

    init_params_train();

    for (int sample = 1; sample <= n_train; ++sample)
    {
        cout << "Sample " << sample << endl;
        preprocess();
        int n_iter = learning_process();
        // log the square error
        cout << "No. of iterations: " << n_iter << endl;
        printf("Error: %0.61f\n\n", square_error());
        report << "Sample " << sample << ": iters = " << n_iter << ", Error = " << square_error() << endl;

        /*
        // save the current network (weights)
        if (sample % 100 == 0)
        {
            cout << "Saving the network to " << model_fn << "." << endl;
            save_model(model_fn);
        }
        */
    }

    model_save(model_fn);

    // file closed
    image.close();
    label.close();
    report.close();
}


int train()
{
    desc_train();  // model definition
    train_process();  // training process

    return 0;
}


#endif
