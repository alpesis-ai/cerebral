#ifndef MATRIX_PROCESSOR_H
#define MATRIX_PROCESSOR


float* convert_matrix(fmat A)
{
    float *A_vec = (float*)malloc(A.n_rows * A.n_cols * sizeof(float));

    for (int i = 0; i < A.n_rows; i++)
    {
        for (int j = 0; j < A.n_cols; j++)
        {
            A_vec[i*j+j] = A(i, j);
        }
    }
    return A_vec;
}


#endif 
