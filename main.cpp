#include "lexer.h"
#include <llvm/Support/raw_ostream.h>
#include <fstream>
#include <iostream>

int main() {
    // Open the .si file
    std::ifstream inputFile("example.si");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file\n";
        return 1;
    }

    // Create a Lexer with the ifstream
    Lexer lexer(inputFile);

    // Close the file
    inputFile.close();

    Token token;
    do {
        token = lexer.getNextToken();
        llvm::outs() << "Token: " << token.value << "\n";
    } while (token.kind != tok_eof);

    return 0;
}
