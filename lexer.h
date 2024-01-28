#ifndef LEXER_H
#define LEXER_H

#include <llvm/ADT/StringRef.h>

enum TokenKind {
    tok_eof = -1,
    tok_identifier = -2,
    tok_integer = -3,
    tok_string = -4,
    tok_symbol = -5,
    tok_open_paren = -6,
    tok_close_paren = -7,
    tok_newline = -8,
    tok_equal = -9,
    tok_arrow = -10,
    tok_comment = -11,
    tok_dot = -12,
    tok_comma = -13,
    tok_add = -15,
    tok_sub = -16,
    tok_div = -17,
    tok_mut = -18,
    tok_assign = -19,
};

struct Token {
    TokenKind kind;
    std::basic_string<char> value;

    Token(TokenKind kind, llvm::StringRef value);

    Token();
};

class Lexer {
    const char *pos;
    const char *start;

public:
    explicit Lexer(const char *input);

    Token getNextToken();

private:
    Token identifier();

    Token integer();

    Token symbol();
};

#endif // LEXER_H
