#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

class Parser {
public:
    explicit Parser(Lexer &lexer);

    void parse();

private:
    Lexer &lexer;

    void parseClass();


    void parseFunction();

    void parseCallHelper(const Token &currentToken);

    void mainHelper();

    void parseFunctionHelper();

    void parsePublic();

    void parsePrivate();

    void parseConstructer();
};

#endif // PARSER_H
