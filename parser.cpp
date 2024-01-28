#include "parser.h"
#include <fstream>
#include <llvm/Support/ErrorHandling.h>

std::ofstream out("output.cpp");

Parser::Parser(Lexer &lexer) : lexer(lexer) {}

void write(std::string str) {
    out << str;
}

void Parser::parse() {
    while (true) {
        Token token = lexer.getNextToken();
        if (token.kind == tok_eof) {
            break;
        } else if (token.kind == tok_newline) {
            continue;
        } else if (token.kind == tok_open_paren) {
            token = lexer.getNextToken();
            if (token.kind == tok_identifier && token.value == "class") {
                parseClass();
            } else if (token.kind == tok_identifier && token.value == "function") {
                parseFunction();
            } else {
                printf("Unexpected token %s\n", token.value.c_str());
                llvm::report_fatal_error("Unexpected token @ 24");
            }
        } else {
            printf("Unexpected token %s\n", token.value.c_str());
            llvm::report_fatal_error("Unexpected token@ 27");
        }
    }
    out.close();
}

void Parser::parseClass() {
    write("class ");
    Token token = lexer.getNextToken();
    if (token.kind != tok_identifier) {
        llvm::report_fatal_error("Expected identifier");
    } else {
        write(token.value);
        write("{ \n");
    }
    token = lexer.getNextToken();
    if (token.kind != tok_open_paren) {
        llvm::report_fatal_error("Expected '('");
    }
    token = lexer.getNextToken();
    if (token.kind == tok_close_paren) {
        write(" }");
    } else if (token.kind != tok_identifier && (token.value != "public" || token.value != "private")) {
        llvm::report_fatal_error("Expected 'public' or 'private'");
    } else if (token.value == "public") {
        write("public: \n");
        parsePubPri();
        token = lexer.getNextToken();
        if (token.kind == tok_open_paren) {
            token = lexer.getNextToken();
            if (token.value == "private") {
                write("private: \n");
                parsePubPri();
                token = lexer.getNextToken();
                if (token.kind == tok_close_paren) {
                    write(" }; \n");
                } else {
                    llvm::report_fatal_error("Expected ')'");
                }

            } else {
                llvm::report_fatal_error("Expected 'private'");
            }
        } else if (token.kind == tok_close_paren) {
            write(" }; \n");
        } else {
            llvm::report_fatal_error("Expected '(' or ')'");
        }
    } else if (token.value == "private") {
        write("private: \n");
        parsePubPri();
        token = lexer.getNextToken();
        if (token.kind == tok_open_paren) {
            token = lexer.getNextToken();
            if (token.value == "public") {
                write("public: \n");
                parsePubPri();
                token = lexer.getNextToken();
                if (token.kind == tok_close_paren) {
                    write(" }; \n");
                } else {
                    llvm::report_fatal_error("Expected ')'");
                }
            } else {
                llvm::report_fatal_error("Expected 'public'");
            }
        } else if (token.kind == tok_close_paren) {
            write(" }; \n");
        } else {
            llvm::report_fatal_error("Expected '(' or ')'");
        }
    } else {
        llvm::report_fatal_error("Unexpected token");
    }
}

void Parser::parsePubPri() {
    while (true) {
        Token token = lexer.getNextToken();
        if (token.kind == tok_close_paren) {
            write(" \n");
            token = lexer.getNextToken();
            if (token.kind == tok_close_paren) {
                write("\n");
                break;
            } else parsePubPriHelper(token);
        } else if (token.kind == tok_open_paren) {
            token = lexer.getNextToken();
            parsePubPriHelper(token);
        } else {
            llvm::report_fatal_error("Unexpected token");
        }
    }

}

void Parser::parsePubPriHelper(Token currentToken) {
    if (currentToken.kind == tok_identifier && currentToken.value != "method" && currentToken.value != "cMethod") {
        write(currentToken.value);
        write(" ");
        currentToken = lexer.getNextToken();
        if (currentToken.kind == tok_identifier) {
            write(currentToken.value);
            write("; \n");
        } else {
            llvm::report_fatal_error("Expected identifier");
        }
    } else if (currentToken.value == "method") {
        parseMethod();
    } else if (currentToken.value == "cMethod") {
        parseConstructor();
    }
}


void Parser::parseMethod() {
    write("auto ");

}

void Parser::parseConstructor() {
    Token token = lexer.getNextToken();
    if (token.type != tok_identifier) {
        llvm::report_fatal_error("Expected identifier");
    } else {
        write(token.value);
        write(" (");

    }

    void Parser::parseFunction() {
        // Implement function parsing logic
        // ...
    }


    void Parser::parseCall() {
        // Implement function/method call parsing logic
        // ...
    }
