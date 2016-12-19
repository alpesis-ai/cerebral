#ifndef HOSTEXAMPLESET_H
#define HOSTEXAMPLESET_H

#include "../common/ExampleSet.h" 

class HostExampleSet : public ExampleSet
{
    public:
        HostExampleSet(uint size, uint numIn, uint numOut);
        HostExampleSet(const Relation& relation);
        virtual ~HostExampleSet();
        virtual void normalize();
        virtual void unnormalize();
        virtual void setOutput(uint i, float* output);

    protected:
        void init();
        void randomize();
        void setRelation(const Relation& relation);
        void addStatistics();
        void addValue(float value, bool isTarget);
        void addValue(int value, uint card, bool isTarget);
        void adjust(float &x, const Range &from, const Range &to) const;
        uint inputIdx;
        uint outputIdx;
} 

#endif
