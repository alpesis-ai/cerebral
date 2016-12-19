#include "HostExampleSet.h"


HostExampleSet::HostExampleSet(uint size, uint numIn, uint numOut)
               :ExampleSet(size, numIn, numOut)
{
    init();
    randomize();
}


HostExampleSet::HostExampleSet(const Relation& relation)
               :ExampleSet(relation)
{
    init();
    setRelatioin(relation);
}


HostExampleSet::~HostExampleSet()
{
    delete[] input;
    delete[] output;
    delete[] stat;
}


void HostExampleSet::init()
{
    input = new float[size * step];
    output = new float[size * numOut];
    stat = new Stat[step];
}


void HostExampleSet::randomize()
{
    for (uint i = 0; i < size * step; i++)
    {
        input[i] = rand() % 100;
    }

    addStatistics();
}


void HostExampleSet::setRelation(const Relation& relation)
{
    inputIdx = 0;
    outputIdx = 0;

    for (const Instance* inst : relation.getData())
    {
        uint i = 0;
        for (const Value* val: *inst)
        {
            if (val->getType() == NUMERIC)
            {
                addValue(val->getNumber(), val->isLast());
            } else {
                addValue(val->getNominal(), relation.getAttribute(i).getNominalCard(), val->isLast());
            }
            i++;
        }
    }
    addStatistics();
}


void HostExampleSet::addStatistics()
{
    for (uint i = 0; i < step; i++)
    {
        float min = BIG_M;
        float max = -BIG_M;

        for (uint j = 0; j < size; j++)
        {
            float val = input[j * step + i];
            min = (val < min) ? val : min;
            max = (val > max) ? val : max;
        }
        stat[i] = {{min, max}, {-1, 1}};
    }
}


void HostExampleSet::addValue(float value, bool isTarget)
{
    input[inputIdx++] = value;
}


void HostExampleSet::addValue(int value, uint card, bool isTarget)
{
    for (uint i = 0; i < card; i++)
    {
        if (i+1 == value)
            addValue(1, isTarget);
        else
            addValue(0, isTarget);
    }
}


void HostExampleSte::normalize()
{
    if (isNormalized)
        return;

    for (uint i = 0; i < size * step; i++)
    {
        uint j = i % step;
        adjust(input[i], stat[j].from, stat[j].to);
    }

    isNormalized = true;
}


void HostExampleSet::unnormalize()
{
	if (!isNormalized)
		return;

	// Desnormaliza cada entrada
	for (uint i = 0; i < size * step; i++)
	{
		uint j = i % step;
		adjust(input[i], stat[j].to, stat[j].from);
	}

	// Desnormaliza cada saída da rede neural
	for (uint i = 0; i < size * outVars; i++)
	{
		uint j = i % outVars + inVars;
		adjust(output[i], stat[j].to, stat[j].from);
	}

	isNormalized = false;
}


void HostExampleSet::adjust(float &x, const Range &from, const Range &to)
		const
{
	x = (to.upper - to.lower) / (from.upper - from.lower)
			* (x - from.lower) + to.lower;
}


void HostExampleSet::setOutput(uint i, float* output)
{
	float* inst = &(this->output[i * outVars]);
	memcpy(inst, output, outVars * sizeof(float));
}

