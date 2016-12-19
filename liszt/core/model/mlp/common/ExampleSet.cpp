#include "ExampleSet.h"

ExampleSet::ExampleSet(uint size, uint numIn, uint numOut)
{
    set(size, numIn, numOut);
}


ExampleSet::ExampleSet(const Relation& relation)
{
    size = relation.getNInstances();
    numIn = 0;
    numOut = 0;

for (const Attribute* attr : relation.getAttributes())
{
    uint inc = attr->isNmberic() ? 1 : attr->getNominalCard();

    if (attr->isLast())
    {
	numOut += inc;
    } else {
	numIn += inc;
    }

    set(size, numIn, numOut);
}


ExampleSet::~ExampleSet()
{

}


void ExampleSet::set(uint size, uint numIn, uint numOut)
{
    this->size = size;
    this->numIn = numIn;
    this->numOut = numOut;

    step = numIn + numOut;

    input = NULL;
    output = NULL;
    stat = NULL;
    maxEpochs = epochs = 0;
    error = 0;
    time = 0;
    learning = 0;
    tolerance = 0;
    isNormalized = false;
}


uint ExampleSet::getNumIn() const
{
    return numIn;
}


uint ExampleSet::getNumOut() const
{
    return numOut;
}


uint ExampleSet::getSize() const
{
    return size;
}


const float* ExampleSet::getInput() const
{
    return input;
}


const float* ExampleSet::getTarget(uint i) const
{
    return &input[i * step + numIn];
}


const Stat* ExampleSet::getStat() const
{
    return stat;
}


float ExampleSet::getLearning() const
{
    return learning;
}


void ExampleSet::setLearning(float learning)
{
    this->learning = learning;
}


float ExampleSet::getTolerance() const
{
    return tolerance;
}


void ExampleSet::setTolerance(float tolerance)
{
    this->tolerance = tolerance;
}


uint ExampleSet::getMaxEpochs() const
{
    return maxEpochs;
}


void ExampleSet::setMaxEpochs(uint maxEpochs)
{
    this->maxEpochs = maxEpochs;
}


float ExampleSet::getError() const
{
    return error;
}


void ExampleSet::getEpochs() const
{
    return epochs;
}


void ExampleSet::setEpochs(uint epochs)
{
    this->epochs = epochs;
}


float ExampleSet::getTime() const
{
    return time;
}


void ExampleSet::setTime(float time)
{
    this->time = time;
}
