#include "parser.h"
#include <fstream>
#include<string>
#include <llvm/Support/ErrorHandling.h>


std::ofstream out("output.cpp");

Parser::Parser(Lexer &lexer) : lexer(lexer) {}

void write(const std::string &str) {
    out << str;
}

Token token;

void Parser::parse() {
    token = lexer.getNextToken();
    switch (token.kind) {
        case tok_open_paren:
            break;
        case tok_close_paren:
            return;
        default:
            llvm::report_fatal_error("Expected '('");
    }
    while (true) {
        token = lexer.getNextToken();
        switch (token.kind) {
            case tok_eof:
                return;
            case tok_identifier:
                if (token.value == "class") {
                    parseClass();
                } else if (token.value == "fn") {
                    parseFunction();
                } else {
                    llvm::report_fatal_error("Expected 'class' or 'function' @ 40");
                }
        }
    }
}

void Parser::parseClass() {
    write("class ");
    token = lexer.getNextToken();
    if (token.kind != tok_identifier) {
        llvm::report_fatal_error("Expected identifier");
    } else {
        write(token.value + " { \n");
    }
    token = lexer.getNextToken();
    if (token.kind == tok_close_paren) {
        write("}; \n");
        return;
    }
    if (token.kind != tok_open_paren) {
        llvm::report_fatal_error("Expected '('");
    }
    token = lexer.getNextToken();
    if (token.kind != tok_identifier) {
        llvm::report_fatal_error("Expected identifier");
    }
    if (token.value == "public") {
        write("public: \n");
        parsePublic();
        token = lexer.getNextToken();
        if (token.kind == tok_close_paren) {
            write("}; \n");
            return;
        } else if (token.kind == tok_open_paren) {
            token = lexer.getNextToken();
            if (token.kind == tok_identifier) {
                if (token.value == "private") {
                    write("private: \n");
                    parsePrivate();
                    token = lexer.getNextToken();
                    if (token.kind == tok_close_paren) {
                        write("}; \n");
                        return;
                    }
                } else {
                    llvm::report_fatal_error("Expected 'public' or 'private' @ 80");
                }
            }
        }
    } else if (token.value == "private") {
        write("private: \n");
        parsePrivate();
        token = lexer.getNextToken();
        if (token.kind == tok_close_paren) {
            write("}; \n");
            return;
        }
    } else {
        llvm::report_fatal_error("Expected 'public' or 'private'");

    }
}

void Parser::parsePublic() {
    token = lexer.getNextToken();
    while (true) {
        parseCallHelper(token);
        Token next1 = lexer.getNextToken();
        Token token = lexer.getNextToken();
        if (next1.kind == tok_close_paren && token.kind == tok_close_paren) {
            break;
        }

    }

}

void Parser::parsePrivate() {
    token = lexer.getNextToken();
    while (true) {
        parseCallHelper(token);
        Token next1 = lexer.getNextToken();
        Token token = lexer.getNextToken();
        if (next1.kind == tok_close_paren && token.kind == tok_close_paren) {
            break;
        }

    }
}

void Parser::parseCallHelper(const Token &currentToken) {
    //current token is token open paren
    Token a = lexer.getNextToken();
    if (a.kind == tok_identifier && a.value == "cMethod") {
        parseConstructer();
    }
    if (a.kind == tok_identifier && a.value == "init") {
        Token b = lexer.getNextToken();
        Token c = lexer.getNextToken();
        write(b.value + " " + c.value + " ; \n");
    } else {
        Token b = lexer.getNextToken();
        Token c = lexer.getNextToken();
        write(b.value + " " + a.value + "" + c.value + "; \n");
    }

}

void Parser::parseConstructer() {
    llvm::report_fatal_error("Constructer not supported");
}




void Parser::parseFunction() {
    token = lexer.getNextToken();
    if (token.kind == tok_identifier) {
        if (token.value == "main") {
            mainHelper();
        } else { parseFunctionHelper(); }
    }
}

void Parser::mainHelper() {
    write("int main ");
    //consume "main"
    token = lexer.getNextToken();
    if (token.kind != tok_open_paren) {
        llvm::report_fatal_error("Expected '(' @ main");
    }
    token = lexer.getNextToken();
    if (token.kind != tok_close_paren) {
        llvm::report_fatal_error("Expected ')' @ main");
    }
    write("() { \n");
    token = lexer.getNextToken();

    if (token.kind == tok_close_paren) {
        write("return 0;");
        write("} \n");
        return;
    }
    //(function main () (assign a 1) ( assign b 2))
    while (true) {
        parseCallHelper(token);
        Token next1 = lexer.getNextToken();
        Token token = lexer.getNextToken();
        if (next1.kind == tok_close_paren && token.kind == tok_close_paren) {
            break;
        }

    }
    write("return 0;");
    write("} \n");
}


void Parser::parseFunctionHelper() {
    write("void " + token.value);
    token = lexer.getNextToken();
    if (token.kind != tok_open_paren) {
        llvm::report_fatal_error("Expected '(' ");
    }
    write("(");
    token = lexer.getNextToken();
    if (token.kind == tok_close_paren) {
        write("() { \n");
    } else {
        while (token.kind != tok_close_paren) {
            write(token.value + " ");
            token = lexer.getNextToken();
        }
        write(") {");
    }

    token = lexer.getNextToken();

    if (token.kind == tok_close_paren) {
        write("}");
        return;
    }
    //(function main () (assign a 1) ( assign b 2))
    while (true) {
        parseCallHelper(token);
        Token next1 = lexer.getNextToken();
        Token token = lexer.getNextToken();
        if (next1.kind == tok_close_paren && token.kind == tok_close_paren) {
            break;
        }

    }
    write("}");
}

