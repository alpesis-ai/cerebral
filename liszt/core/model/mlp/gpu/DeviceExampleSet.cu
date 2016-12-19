#include "DeviceExampleSet.h"


    __device__ void adjust(float &x, const Range &from, const Range &to);

    DeviceExampleSet::DeviceExampleSet(uint size, uint numIn, uint numOut)
                     :ExampleSet(size, numIn, numOut)
    {
        HostExampleSet set(size, numIn, numOut);
        copyToDevice(set);
    }


    DeviceExampleSet::copyToDevice(const HostExampleSet &set)
    {
        stepBlocks = (size * step) / TPB + 1;
        outBlocks = (size * numOut) / TPB + 1;

        cudaMalloc(&input, size * step * sizeof(float));
        cudaMalloc(&output, size * numOut * sizeof(float));
        cudaMalloc(&stat, step * sizeof(Stat));

        cudaMemcpy(input, set.getInput(), size * step * sizeof(float), cudaMemcpyHostToDevice);
        cudaMemcpy(stat, set.getStat(), step* sizeof(Stat), cudaMemcpyHostToDevice);
    }
