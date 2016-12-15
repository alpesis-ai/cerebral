#include "process.h"


int main(int argc, char* argv[])
{
    if ((argc != 2) or (strcmp(argv[1], "cpu") != 0) or (strcmp(argv[1], "gpu") != 0))
    {
        cout << "Usage: ./REG <cpu/gpu>" << endl;
    }

    if ((argc == 2) && (strcmp(argv[1], "cpu") == 0))
    {
        elm_cpu();
    }
    
    if ((argc == 2) && (strcmp(argv[1], "gpu") == 0))
    {
        elm_gpu();
    } 

    return 0;
}
