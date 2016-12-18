#include <iostream>

using namespace std;


void print_matrix(const float *A, int A_rows, int A_cols)
{
    for (int i = 0; i < A_rows; ++i)
    {
        for (int j = 0; j < A_cols; ++j)
        {
            cout << A[A_rows * j + i] << "";
        }
        cout << endl;
    }
    cout << endl;
}
