#include <string.h>
#include <fstream>

#include "train.h"
#include "test.h"


int main(int argc, char* argv[])
{

    if (argc != 2 or strcmp(argv[1], "train") or (strcmp(argv[1], "test")))
    {
        cout << "Usage: ./MNIST <train/test>" << endl;
    }

    if (strcmp(argv[1], "train") == 0)
    {
        train();
    }
    
    if (strcmp(argv[1], "test") == 0)
    {
        test();
    } 

    return 0;
}
