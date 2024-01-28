#include "lexer.h"
#include <llvm/Support/ErrorHandling.h>

Token::Token(TokenKind kind, llvm::StringRef value) : kind(kind), value(value) {}

Token::Token() : kind(tok_eof), value("") {} // Default constructor

Lexer::Lexer(const char *input) : pos(input), start(input) {}

Token Lexer::getNextToken() {
    while (isspace(*pos)) {
        if (*pos == '\n') {
            pos++;
            return {tok_newline, "\n"};
        }
        pos++;
    }

    start = pos;
    if (*pos == '\0') {
        return {tok_eof, ""};  // End of file
    }

    if (isalpha(*pos)) {
        while (isalnum(*pos) || *pos == '_')
            pos++;
        return identifier();
    } else if (isdigit(*pos)) {
        while (isdigit(*pos))
            pos++;
        return integer();
    } else if (*pos == '"') {
        pos++;
        while (*pos != '"' && *pos != '\0')
            pos++;
        if (*pos == '"') {
            pos++;
            return {tok_string, llvm::StringRef(start, pos - start)};
        } else {
            llvm::report_fatal_error("Unterminated string");
        }
    } else {
        switch (*pos) {
            case '(':
                pos++;
                return {tok_open_paren, "("};
            case ')':
                pos++;
                return {tok_close_paren, ")"};
            case '=':
                pos++;
                return {tok_equal, "="};
            case '-':
                pos++;
                if (*pos == '>')
                    pos++;
                return {tok_arrow, "->"};
            case ';':
                pos++;
                return {tok_semicolon, ";"};
            case '.':
                pos++;
                return {tok_dot, "."};
            case '*':
                pos++;
                return {tok_star, "*"};
            case '&':
                pos++;
                return {tok_amp, "&"};
            default:
                return symbol();
        }
    }
}

Token Lexer::identifier() {
    return {tok_identifier, llvm::StringRef(start, pos - start)};
}

Token Lexer::integer() {
    return {tok_integer, llvm::StringRef(start, pos - start)};
}

Token Lexer::symbol() {
    return {tok_symbol, llvm::StringRef(start, 1)};
}