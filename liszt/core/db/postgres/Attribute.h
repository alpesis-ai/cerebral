#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

typedef list<string> Nominal;

enum AttributeType
{
    NUMERIC, NOMINAL, STRING, DATE, EMPTY
};



class Attribute
{
    public:
        Attribute(const string &name, AttributeType type);
        Attribute(const string &name, AttributeType type, const string &format);
        Attribute(const string &name, AttributeType type, const Nominal &nominal);
        virtual ~Attribute();
        
        bool isNominal() const;
        bool isNumeric() const;
        string getName() const;
        AttributeType getType() const;
        bool isLast() const;
        void setLast(bool last);
        const Nominal& getNominalList() const;
        uint getNominalCard() const;

    private:
        string name;
        AttributeType type;
        bool last;
        
        union
        {
            string* str;
            Nominal* nominal;
        };
};

typedef vector<Attribute*> Attributes;

#endif
