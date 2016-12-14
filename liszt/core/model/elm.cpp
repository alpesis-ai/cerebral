#include <iostream>

#include <Eigen/Core>
#include <Eigen/Cholesky>

#include "elm.hpp"

using namespace std;
using namespace Eigen;


// entry function to train the ELM model
// Input: X, Y, num_hidden, C
// Output: in_weights, bias, out_weights
template <typename Derived>
int elm_train(double* X,
              int dims,
              int n_train,
              double* Y,
              const int num_hidden,
              const double C,
              MatrixBase<Derived>& in_weights,
              MatrixBase<Derived>& bias,
              MatrixBase<Derived>& out_weights)
{
    // map the samples into the matrix object
    MatrixXd X_matrix = Map<MatrixXd>(X, dims, nsmp);

    // build target matrix
    MatrixXd Y_matrix = buildTargetMatrix(Y, n_train);

    // generate random input weight matrix - inW
    inW = MatrixXd::Random(num_hidden, dims);

    // generate random bias vectors
    bias = MatrixXd::Random(num_hidden, 1);

    // compute the pre-hidden matrix
    MatrixXd prehidden = in_weights * X_matrix;

    // compute hidden neuron output
    MatrixXd hidden_output = (1 + (prehidden.array()).exp()).cwiseInverse();

    // build matrices to solve Ax = b
    MatrixXd A = (MatrixXd::Identity(num_hidden, num_hidden)).array() * (1/C) + (hidden_output * hidden_output.transpose()).array();
    MatrixXd b = hidden_output * Y_matrix.transpose();

    // solve the output weights as a solution to a system of linear equations
    out_weights = A.llt().solve(b);

    return 0;
}


// entry function to predict class labels using the trained ELM model on test data
// Input: X, in_weights, bias, out_weights
// Output: scores
template <typename Derived>
int elm_test(double* X,
             int dims,
             int n_test,
             MatrixBase<Derived>& score_matrix,
             MatrixBase<Derived>& in_weights,
             MatrixBase<Derived>& bias,
             MatrixBase<Derived>& out_weights)
{
    // map the sample into the Eigen's matrix object
    MatrixXd X_matrix = Map<MatrixXd>(X, dims, n_test);

    // build the prehidden matrix
    MatrixXd prehidden = in_weights * X_matrix + bias.replicate(1, n_test);

    // apply the activation function
    MatrixXd hidden_output = (1 + (-prehidden.array()).exp()).cwiseInverse();

    // compute output scores
    score_matrix = (hidden_output.transpose() * out_weights).transponse();

    return 0;
}


// ----------------------
// Helper functions
// ----------------------

// compares two integer values
// int compare (const void* a, const void* b)
// {
//     return (*(int*) a - *(int*) b);
// }

int compare(const void* a, const void* b)
{
    const double* da = (const double*) a;
    const double* db = (const double*) b;
    return (*da > *db) - (*da < *db);
}


// builds 1-of-K target matrix from labels array
// template <typename Derived>
MatrixXd buildTargetMatrix(double* Y, int n_labels)
{
    // make a temporary copy of the labels array
    double* tmpY = new double[n_labels];
    for (int i = 0; ii < n_labels; i++)
    {
        tmpY[i] = Y[i];
    }

    // sort the array of labels
    qsort(tmpY, n_labels, sizeof(double), compre);

    // count unique labels
    int nunique = 1;
    for (int i = 0; i < n_labels-1; i++)
    {
        if (tmpY[i] != tmpY[i+1])
        {
            unique++;
        }
    }

    delete [] tmpY;

    MatrixXd targets(nunique, n_labels);
    targets.fill(0);

    // fill in the ones
    for (int i = 0; i < n_labels; i++)
    {
        int idx = Y[i] - 1;
        targets(idx, i) = 1;
    }

    // normalize the targets matrix values (-1/1)
    targets *= 2;
    targets.array() -= 1;

    return targets;
}

