#ifndef SCANNER_H
#define SCANNER_H


class Scanner : public yyFlexLexer
{
    public:
        Scanner(Driver &driver);
        int yylex(Parser::semantic_type* yylval, Parser::location_type* yyloc);
        void markLine();
        int getLineno() const;
        string getToken() const;
    
    private:
        void throwError(ErrorType error) const;
        Driver &driver;
        int markedLine;
};

#endif
