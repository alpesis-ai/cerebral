#ifndef RELATION_H
#define RELATION_H

#include <map>

#include "Value.h"
#include "Driver.h"


class Relation
{
    public:
        Relation(Driver &driver);
        ~Relation();

        void addAttributes(Attribute* attr);
        void addInstance(const DataList* dlist, bool isSparse);

        uint getNAttributes() const;
        uint getNInstances() const;
        string getName() const;
        
        void setName(const string *name);
        const Attributes& getAttributes() const;
        const Attributes& getAttributes(uint i) const;
        const Data& getData() const;
        const Instance& getInstance(uint i) const;

    private:
        int checkNominal(uint attrIindex, const string &name);
        void throwError(ErrorType error) const;
        string name;
        Attributes attributes;
        Data data;
        Driver &driver;
        map<string, bool> attrMap;
};        

#endif
