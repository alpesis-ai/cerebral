#ifndef SETTINGS_H
#define SETTINGS_H

#include <fstream>
#include <iostream>

using namespace std;

// -----------------------------------------------------------------------
// common

// model parameters
const int width = 28;
const int height = 28;
const int n1 = width * height;
const int n2 = 128;
const int n3 = 10;

// layer parameters
double *w1[n1+1], *out1;              // layer1
double *w2[n2+1], *in2, *out2;        // layer2
double *in3, *out3;                   // layer3
double expected[n3+1];

// convert image vector to image
int digit[width+1][height+1];

// model file
const string model_fn = "model_mlp.dat";


// File stream to read data (image, label) and write down a report
ifstream image;
ifstream label;
ofstream report;

// -----------------------------------------------------------------------
// train

// Layer parameters
double *delta1[n1+1];  // layer1
double *delta2[n2+1], *theta2;  // layer2
double *theta3; // layer3


// train process
const int epochs = 512;
const double learning_rate = 1e-3;
const double momentum = 0.9;
const double epsilon = 1e-3;


// input data
const string training_image_fn = "data/mnist/train-images-idx3-ubyte";
const string training_label_fn = "data/mnist/train-labels-idx1-ubyte";
const int n_train = 10;  // number of training samples, default: 60000


// logs
const string report_fn_train = "training_report.dat";


// -----------------------------------------------------------------------
// test

// input data
const string testing_image_fn = "data/mnist/t10k-images-idx3-ubyte";
const string testing_label_fn = "data/mnist/t10k-labels-idx1-ubyte";
const int n_test = 10;  // default: 10000

// logs
const string report_fn_test = "testing_report.dat";

#endif
