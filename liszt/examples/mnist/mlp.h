#ifndef MLP_H
#define MLP_H

#include "activator.h"

void forward()
{
    // initialize in2
    for (int i = 1; i <= n2; ++i)
    {
        in2[i] = 0.0;
    }

    // initialize in3
    for (int i = 1; i <= n3; ++i)
    {
        in3[i] = 0.0;
    }

    for (int i = 1; i <= n1; ++i)
    {
        for (int j = 1; j <= n2; ++j)
        {
            in2[j] += out1[i] * w1[i][j];
        }
    }

    for (int i = 1; i <= n2; ++i)
    {
        out2[i] = sigmoid(in2[i]);
    }

    for (int i = 1; i <= n2; ++i)
    {
        for (int j = 1; j <= n2; ++j)
        {
            in3[j] += out2[i] * w2[i][j];
        }
    }

    for (int i = 1; i <= n3; ++i)
    {
        out3[i] = sigmoid(in3[i]);
    }
    
}


void backward()
{
    double sum;

    for (int i = 1; i <= n3; ++i)
    {
        theta3[i] = out3[i] * (1 - out3[i]) * (expected[i] - out3[i]);
    }

    for (int i = 1; i <= n2; ++i)
    {
        sum = 0.0;
        for (int j = 1; j <= n2; ++j)
        {
            sum += w2[i][j] * theta3[j];
        }
        theta2[i] = out2[i] * (1 - out2[i]) * sum;
    }

    for (int i = 1; i <= n2; ++i)
    {
        for (int j = 1; j <= n3; ++j)
        {
            delta2[i][j] = (learning_rate * theta3[j] * out2[i]) + (momentum * delta2[i][j]);
            w2[i][j] += delta2[i][j];
        }
    }

    for (int i = 1; i <= n1; ++i)
    {
        for (int j = 1; j <= n2; j++)
        {
            delta1[i][j] = (learning_rate * theta2[j] * out1[i]) + (momentum * delta1[i][j]);
            w1[i][j] += delta1[i][j];
        }
    }
}



#endif
