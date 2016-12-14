#include <string.h>
#include <fstream>

#include "models/train_mlp.h"
#include "models/test_mlp.h"
#include "models/train_elm.h"
#include "models/test_elm.h"


int main(int argc, char* argv[])
{

    if (argc != 3)
    {
        cout << "Usage: ./MNIST <train/test> <mlp/elm>" << endl;
    }

    // MLP: train
    else if ((strcmp(argv[1], "train") == 0) && (strcmp(argv[2], "mlp") == 0))
    {
        train_mlp();
    }
    // MLP: test
    else if ((strcmp(argv[1], "test") == 0) && (strcmp(argv[2], "mlp") == 0))
    {
        test_mlp();
    }

    // ELM: train
    else if ((strcmp(argv[1], "train") == 0) && (strcmp(argv[2], "elm") == 0))
    {
        train_elm();
    }
    // ELM: test
    else if ((strcmp(argv[1], "test") == 0) && (strcmp(argv[2], "elm") == 0))
    {
        test_elm();
    } 

    else 
    {
        cout << "Usage: ./MNIST <train/test> <mlp/elm>" << endl;
    }

    return 0;
}
