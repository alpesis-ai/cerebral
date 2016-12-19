#ifndef DEVICEEXAMPLESET_H
#define DEVICEEXAMPLESET_H

    class DeviceExampleSet : public ExampleSet
    {
        public:
            DeviceExampleSet(uint size, uint numIn, uint numOut);
            DeviceExampleSet(const Relation& relation);
            virtual ~DeviceExampleSet();
            virtual void normalize();
            virtual void unnormalize();
            virtual void setOutput(uint i, float* output);

        protected:
            void copyToDevice(const HostExampleSet &set);
            uint stepBlocks;
            uint outBlocks;
    }


#endif
