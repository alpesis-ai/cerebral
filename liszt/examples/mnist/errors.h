#ifndef ERRORS_H
#define ERRORS_H

double square_error()
{
    double res = 0.0;
    for (int i = 1; i <= n3; ++i)
    {
        res += (out3[i] - expected[i]) * (out3[i] - expected[i]);
    }
    res *= 0.5;
    return res;
}

#endif
