#include "lexer.h"
#include <llvm/Support/raw_ostream.h>
#include <fstream>
#include <iostream>

int main() {
    std::ifstream inputFile("example.si");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file\n";
        return 1;
    }

    std::string input((std::istreambuf_iterator<char>(inputFile)),
                      (std::istreambuf_iterator<char>()));
    inputFile.close();

    Lexer lexer(input.c_str());
    Token token;
    do {
        token = lexer.getNextToken();
        llvm::outs() << "Token: " << token.value << "\n";
    } while (token.kind != tok_eof);

    return 0;
}
