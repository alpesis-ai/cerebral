#ifndef MODEL_SAVER_H
#define MODEL_SAVER_H

#include <iostream>

using namespace std;


void model_save(string file_name)
{
    ofstream file(file_name.c_str(), ios::out);

    // input -> hidden
    for (int i = 1; i <= n1; ++i)
    {
        for (int j = 1; j <= n2; ++j)
        {
            file << w1[i][j] << " ";
        }
        file << endl;
    }

    // hidden -> output
    for (int i = 1; i <= n2; ++i)
    {
        for (int j = 1; j <= n3; ++j)
        {
            file << w2[i][j] << " ";
        }
        file << endl;
    }
    file.close();
}


void model_load(string file_name)
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


#endif
