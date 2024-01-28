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

    void parseMethod();

    void parseFunction();

    void parseCall();

    void parsePubPri();

    void parsePubPriHelper(Token currentToken);

    void parseConstructor();
};

#endif // PARSER_H
