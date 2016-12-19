#include <vector>
#include <iostream>
#include <stdexcept>

#include "../../core/model/mlp/gpu/DeviceExampleSet.h"

using namespace std;

// ---------------------------------------------------------------------

string program;

void train_fast(int argc, char* argv[]);
void train_normal(int argc, char* argv[]);

// ---------------------------------------------------------------------

int main(int argc, char* argv[])
{
    // argv[0]
    program = argv[0];
    string usage = "Usage: " + program + " <fast/normal>";
    // argc
    if (argc < 2)
        throw runtime_error(usage);

    // argv[1]
    string mode = argv[1];
    if (mode == "fast")
    {
        train_fast(argc, argv);

    } else if (mode == "normal") {
        train_normal(argc, argv);

    } else {
        throw runtime_error(usage);
    }

    return EXIT_SUCCESS;
}


void train_fast(int argc, char* argv[])
{
    string usage = "Usage: " + program + " fast "
                   "<numInput> [numHidden] <numOutput> <numInstances> <maxEpochs>";

    if (argc < 6)
    {
        throw runtime_error(usage);
    }

    uint size = atoi(argv[argc-2]);
    uint maxEpochs = atoi(argv[argc-1]);

    // units: [<numInput>, [numHidden], <numOutput>]
    vector<int> units;
    for (int i = 2; i < argc-2; i++)
    {
        units.push_back(atoi(argv[i]));
    }

    // initialize neural network: [size, numInput, numOutput]
    DeviceExampleSet set(size, units.front(), units.back());   
 
}


void train_normal(int argc, char* argv[])
{}
