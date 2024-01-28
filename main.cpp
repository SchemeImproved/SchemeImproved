#include "lexer.h"
#include <llvm/Support/raw_ostream.h>

int main() {
    const char *input = R"(
    (class Cow
        (private
            (string name)
            (int age))
    )";

    Lexer lexer(input);
    Token token;
    do {
        token = lexer.getNextToken();
        llvm::outs() << "Token: " << token.value << "\n";
    } while (token.kind != tok_eof);

    return 0;
}