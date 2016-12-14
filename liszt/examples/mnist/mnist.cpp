#include <string.h>
#include <fstream>

#include "train_mlp.h"
#include "test_mlp.h"


int main(int argc, char* argv[])
{

    if (argc != 3 or strcmp(argv[1], "train") or (strcmp(argv[1], "test")))
    {
        cout << "Usage: ./MNIST <train/test> <mlp/elm>" << endl;
    }

    if ((strcmp(argv[1], "train") == 0) && (strcmp(argv[2], "mlp") == 0))
    {
        train_mlp();
    }
    
    if ((strcmp(argv[1], "test") == 0) && (strcmp(argv[2], "mlp") == 0))
    {
        test_mlp();
    } 

    return 0;
}
