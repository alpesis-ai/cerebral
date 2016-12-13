#include <iostream>

#include "settings.h"
#include "graph.h"
#include "mlp.h"

using namespace std;

void desc_test()
{
    cout << "************************************************************" << endl;
    cout << "MNIST Test Process                                          " << endl;
    cout << "************************************************************" << endl;
    cout << endl;
    cout << " - No. of input neurons: " << n1 << endl;
    cout << " - No. of hidden neurons: " << n2 << endl;
    cout << " - No. of output neurons: " << n3 << endl;
    cout << endl;
    cout << " - Testing image data: " << testing_image_fn << endl;
    cout << " - Testing label data: " << testing_label_fn << endl;
    cout << " - No. of testing samples: " << n_test << endl;
}


void load_model(string file_name)
{
    ifstream file(file_name.c_str(), ios::in);

    // layer 1: input -> hidden
    for (int i = 1; i <= n1; ++i)
    {
        for (int j = 1; j <= n2; ++j)
        {
            file >> w1[i][j];
        }
    }

    // layer 2: hidden -> output
    for (int i = 1; i <= n2; ++i)
    {
        for (int j = 1; j <= n3; ++j)
        {
            file >> w2[i][j];
        }
    }

    file.close();
}


void test_process()
{
    report.open(report_fn_test.c_str(), ios::out);
    image.open(testing_image_fn.c_str(), ios::in | ios::binary);  // binary image file
    label.open(testing_label_fn.c_str(), ios::in | ios::binary);  // binary label file

    // read file headers
    char number;
    for (int i = 1; i <= 16; ++i)
    {
        image.read(&number, sizeof(char));
    }
    for (int i = 1; i <= 8; ++i)
    {
        label.read(&number, sizeof(char));
    }

    // initialize the net
    net_mlp_forward();
    load_model(model_fn);  // load model (weights matrices) of a trained neural network

    int n_correct = 0;
    for (int sample = 1; sample <= n_test; ++sample)
    {
        cout << "Sample " << sample << endl;

        // get (image, label)
        int label = preprocess();
        // classification 
        forward();

        // prediction
        int predict = 1;
        for (int i = 2; i <= n3; ++i)
        {
            if (out3[i] > out3[predict])
            {
                cout << "out3[i]: " << out3[i] << " | out3[predict]: " << out3[predict] << endl;
                cout << "[i]: " << i << " | predict: " << predict << endl;
                predict = i; 
            }
        }
        --predict;

        // write down the classification result and the squared error
        double error = square_error();
        printf("Error: %0.61f\n", error);

        if (label == predict)
        {
            ++n_correct;
            cout << "Classification: Yes. Label = " << label << " | Predict = " << predict << endl << endl;
            report << "Sample " << sample << ": Yes. Label = " << label << " | Predict = " << predict << " | Error = " << error << endl;
        } else 
        {   
            cout << "Classification: No. Label = " << label << " | Predict = " << predict << endl << endl;
            report << "Image: " << endl;
            report << "Sample " << sample << ": No. Label = " << label << " | Predict = " << predict << " | Error = " << error << endl;
        }

    }

    // summary
    double accuracy = (double)(n_correct) / n_test * 100.0;
    cout << "Number of correct samples: " << n_correct << " / " << n_test << endl;
    printf("Accuracy: %0.2lf\n", accuracy);

    report << "Number of correct samples: " << n_correct << " / " << n_test << endl;
    report << "Accuracy: " << accuracy << endl;

    image.close();
    label.close();
    report.close();
    

}


int test()
{
    desc_test();
    test_process();
    return 0;
}
