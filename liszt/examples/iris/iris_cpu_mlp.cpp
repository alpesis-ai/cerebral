#include <vector>
#include <iostream>
#include <stdexcept>

#include "../../core/model/mlp/cpu/HostExampleSet.h"

using namespace std;


// ---------------------------------------------------------------------

string program;

void train_fast(int argc, char* argv[]);
void train_normal(int argc, char* argv[]);

// ---------------------------------------------------------------------

int main(int argc, char* argv[])
{

    try 
    {
        program = argv[0];
        string usage = "Usage: " + program + " <fast/normal>";

        if (argc < 2)
            throw runtime_error(usage);

        string mode = argv[1];

        if (mode == "fast")
            train_fast(argc, argv);
        else if (mode == "normal")
            train_normal(argc, argv);
        else
            throw runtime_error(usage);
    } catch (exception &error) {
        cerr << error.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


void train_fast(int argc, char* argv[])
{
    string usage = "Usage: " + program + " fast "
                   "<numInput> [numHidden] <numOutput> <numInstances> <maxEpochs>";

    if (argc < 6)
        throw runtime_error(usage);

    uint size = atoi(argv[argc-2]);
    uint maxEpochs = atoi(argv[argc-1]);

    vector<int> units;
    for (int i = 2; i < argc-2; i++)
    {
        units.push_back(atoi(argv[i]));
    }

    HostExampleSet set(size, units.front(), units.back());

}


void train_normal(int argc, char* argv[])
{}
