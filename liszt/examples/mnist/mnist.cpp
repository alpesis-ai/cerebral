#include <fstream>
#include <iostream>

#include "settings.h"
#include "graph.h"
#include "mlp.h"

using namespace std;


// file stream to read data (image, label) and write down a report
ifstream image;
ifstream label;
ofstream report;

void desc()
{
    // descriptions
    cout << "*************************************************" << endl;
    cout << " MNIST Training System                           " << endl;
    cout << "*************************************************" << endl;
    cout << endl;
    cout << " - No. of input neurons: " << n1 << endl;
    cout << " - No. of hidden neurons: " << n2 << endl;
    cout << " - No. of output neurons: " << n3 << endl;
    cout << endl;
    cout << " - No. of iterations: " << epochs << endl;
    cout << " - Learning rate: " << learning_rate << endl;
    cout << " - Momentum: " << momentum << endl;
    cout << " - epsilon: " << epsilon << endl;
    cout << endl;
    cout << " - Training image X: " << training_image_fn << endl;
    cout << " - Training label Y: " << training_label_fn << endl;
    cout << " - No. of training samples: " << n_train << endl << endl;
}


void preprocess()
{
    // convert the image vector to image matrix (28 * 28)
    char number;
    for (int j = 1; j <= height; ++j)
    {
        for (int i = 1; i <= width; ++i)
        {
            image.read(&number, sizeof(char));
            if (number == 0)
            {
                digit[i][j] = 0;
            } else 
            {
                digit[i][j] = 1;
            }
        }
    }

    /*
    // print the digit image
    cout << "Image: " << endl;
    for (int j = 1; j <= height; ++j)
    {
        for (int i = 1; i <= width; ++i)
        {
            cout << digit[i][j];
        }
        cout << endl;
    }
    */


    // convert the digit to the out1
    for (int j = 1; j <= height; ++j)
    {
        for (int i = 1; i <= width; ++i)
        {
            int pos = i + (j - 1) * width;
            out1[pos] = digit[i][j];
        }
    }

    // read the label
    label.read(&number, sizeof(char));
    for (int i = 1; i <= n3; ++i)
    {
        expected[i] = 0.0;
    }
    expected[number+1] = 1.0;
    cout << "Label: " << (int)(number) << endl;

}


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


int learning_process()
{
    // initialize delta1
    for (int i = 1; i <= n1; ++i)
    {
        for (int j = 1; j <= n2; ++j)
        {
            delta1[i][j] = 0.0;
        }
    }

    // initialize delta2
    for (int i = 1; i <= n2; ++i)
    {
        for (int j = 1; j <= n3; ++j)
        {
            delta2[i][j] = 0.0;
        }
    }

    // learning process: epoch loop
    for (int i = 1; i <= epochs; ++i)
    {
        forward();
        backward();
        if(square_error() < epsilon)
        {
           return i;
        }
    }
    return epochs;
}


void save_model(string file_name) {
    ofstream file(file_name.c_str(), ios::out);
	
	// Input layer - Hidden layer
    for (int i = 1; i <= n1; ++i) {
        for (int j = 1; j <= n2; ++j) {
			file << w1[i][j] << " ";
		}
		file << endl;
    }
	
	// Hidden layer - Output layer
    for (int i = 1; i <= n2; ++i) {
        for (int j = 1; j <= n3; ++j) {
			file << w2[i][j] << " ";
		}
        file << endl;
    }
	
	file.close();
}


void train()
{
    // file loading
    report.open(report_fn.c_str(), ios::out);
    image.open(training_image_fn.c_str(), ios::in | ios::binary);  // binary image file
    label.open(training_label_fn.c_str(), ios::in | ios::binary);  // binary label file


    // read the image and label files
    char number;
    for (int i = 1; i <= 16; ++i)
    {
        image.read(&number, sizeof(char));
    }
    for (int i = 1; i <= 8; ++i)
    {
        label.read(&number, sizeof(char));
    }

    net_mlp();

    for (int sample = 1; sample <= n_train; ++sample)
    {
        cout << "Sample " << sample << endl;
        preprocess();
        int n_iter = learning_process();
        // log the square error
        cout << "No. of iterations: " << n_iter << endl;
        printf("Error: %0.61f\n\n", square_error());
        report << "Sample " << sample << ": iters = " << n_iter << ", Error = " << square_error() << endl;

        /*
        // save the current network (weights)
        if (sample % 100 == 0)
        {
            cout << "Saving the network to " << model_fn << "." << endl;
            save_model(model_fn);
        }
        */
    }

    save_model(model_fn);

    // file closed
    image.close();
    label.close();
    report.close();
}


int main(int argc, char* argv[])
{
    desc();  // model definition
    train();  // training process
}
