#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>

#include "settings.h"


void net_mlp() 
{
	// Layer 1 - Layer 2 = Input layer - Hidden layer
    for (int i = 1; i <= n1; ++i) {
        w1[i] = new double [n2 + 1];
        delta1[i] = new double [n2 + 1];
    }
    
    out1 = new double [n1 + 1];

	// Layer 2 - Layer 3 = Hidden layer - Output layer
    for (int i = 1; i <= n2; ++i) {
        w2[i] = new double [n3 + 1];
        delta2[i] = new double [n3 + 1];
    }
    
    in2 = new double [n2 + 1];
    out2 = new double [n2 + 1];
    theta2 = new double [n2 + 1];

	// Layer 3 - Output layer
    in3 = new double [n3 + 1];
    out3 = new double [n3 + 1];
    theta3 = new double [n3 + 1];
    
    // Initialization for weights from Input layer to Hidden layer
    for (int i = 1; i <= n1; ++i) {
        for (int j = 1; j <= n2; ++j) {
            int sign = rand() % 2;

            // Another strategy to randomize the weights - quite good 
            // w1[i][j] = (double)(rand() % 10 + 1) / (10 * n2);
            
            w1[i][j] = (double)(rand() % 6) / 10.0;
            if (sign == 1) {
				w1[i][j] = - w1[i][j];
			}
        }
	}
	
	// Initialization for weights from Hidden layer to Output layer
    for (int i = 1; i <= n2; ++i) {
        for (int j = 1; j <= n3; ++j) {
            int sign = rand() % 2;
			
			// Another strategy to randomize the weights - quite good 
            // w2[i][j] = (double)(rand() % 6) / 10.0;

            w2[i][j] = (double)(rand() % 10 + 1) / (10.0 * n3);
            if (sign == 1) {
				w2[i][j] = - w2[i][j];
			}
        }
	}
}

#endif
