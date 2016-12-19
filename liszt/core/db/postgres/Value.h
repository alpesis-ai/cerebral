#ifndef VALUE_H
#define VALUE_H

#include "Attribute.h"

class Value
{
    public:
        Value(AttributeType type);
        Value(AttributeType type, float number);
        Value(AttributeType type, string &str);
        virtual ~Value();

        bool isNumeric() const;
        bool isNominal() const;
        bool isEmpty() const;
        int getIndex() const;
        void setIndex(int index);
        AttributeType getType() const;
        bool isLast() const;
        void setLast(bool last);
        float getNumber() const;
        int getNominal() const;

    private:
        int index;
        AttributeType type;
        bool last;
        
        union
        {
            float number;
            struct
            {
                string *str;
                int nominal;
            };
        };
        
};

typedef vector<Value*> Instance;
typedef list<Value> DataList;
typedef vector<Instance*> Data;

#endif
