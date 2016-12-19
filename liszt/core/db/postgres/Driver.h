#ifndef DRIVER_H
#define DRIVER_H

class Relation;
class Scanner;
class Parser;


class Driver
{
    public:
        Driver(const string &filename);
        virtual ~Driver();

        const Relation& parse();
        Scanner* scanner;
        Relation* dataset;
        string filename;
        ifstream istream;
        Parser* parser;

};

#endif
