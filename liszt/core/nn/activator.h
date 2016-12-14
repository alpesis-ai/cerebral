#ifndef ACTIVATOR_H
#define ACTIVATOR_H

#include <cmath>


double sigmoid(double x)
{
    return 1.0 / (1.0 + exp(-x));
}

#endif
