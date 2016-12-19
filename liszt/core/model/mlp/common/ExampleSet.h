#ifndef EXAMPLESET_H
#define EXAMPLESET_H

class ExampleSet
{
    public:
        ExampleSet(uint size, uint numIn, uint numOut);
        ExampleSet(const Relation& relation);
        virtual ~ExampleSet();
        virtual void normalize() = 0;
        virtual void unnormalize() = 0;
        uint getNumIn() const;
        uint getNumOut() const;
        uint getSize() const;
        const float* getInput() const;
        const float* getInput(uint i) const;
        const float* getTarget(uint i) const;
        virtual void setOutput(uint i, float* output) = 0;
        const Stat* getStat() const;
        float getLearning() const;
        void setLeanring(float learning);
        float getTolerance() const;
        void setTolerance(float tolerance);
        uint getMaxEpochs() const;
        void setMaxEpochs(uint maxEpochs);
        float getError() const;
        void setError(float error);
        uint getEpochs() const;
        void setEpochs(uint epochs);
        float getTime() const;
        void setTime(float time);

    protected:
        void set(uint size, uint numIn, uint numOut);
        float learning;
        uint maxEpochs;
        float tolerance;
        uint numIn;
        uint numOut;
        uint size;
        uint step;
        float* input;
        float* output;
        Stat* stat;
        float error;
        float time;
        uint epochs;
        bool isNormalized;

};

#endif
