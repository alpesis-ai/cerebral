#ifndef ELM_H
#define ELM_H

// ELM train
// input: X, Y, num_hidden, C
// output: in_weights, bias, out_weights
template <typename Derived>
int elm_train(double* X,
              int dims,
              int n_train,
              double* Y,
              const int num_hidden,
              const double C,
              MatrixBase<Derived>& in_weights,
              MatrixBase<Derived>& bias,
              MatrixBase<Derived>& out_weights);


// ELM tst
// input: X, in_weights, bias, out_weights
// output: scores
template <typename Derived>
int elm_test(double* X,
             int dims,
             int n_test,
             MatrixBase<Derived>& score_matrix,
             MatrixBase<Derived>& in_weights,
             MatrixBase<Derived>& bias,
             MatrixBase<Derived>& out_weights);


// helpers
int compare(const void* a, const void* b);
MatrixXd buildTargetMatrix(double* Y, int n_labels);

#endif
