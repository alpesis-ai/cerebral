#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>

using namespace std;


// Model parameters
const int width = 28;
const int height = 28;
const int n1 = width * height;
const int n2 = 128;
const int n3 = 10;
// Layer parameters
double *w1[n1+1], *delta1[n1+1], *out1;  // layer1
double *w2[n2+1], *delta2[n2+1], *in2, *out2, *theta2;  // layer2
double *in3, *out3, *theta3; // layer3
double expected[n3+1];


// train process
const int epochs = 512;
const double learning_rate = 1e-3;
const double momentum = 0.9;
const double epsilon = 1e-3;


// input data
const string training_image_fn = "data/mnist/train-images-idx3-ubyte";
const string training_label_fn = "data/mnist/train-labels-idx1-ubyte";
const int n_train = 60000;  // number of training samples


// logs
const string report_fn = "training_report.dat";
const string model_fn = "model_mlp.dat";

// evaluation
// convert image vector to image
int digit[width+1][height+1];


#endif
