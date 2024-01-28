#include "lexer.h"
#include "parser.h"
#include <llvm/Support/raw_ostream.h>

int main() {
    const char *input = R"(
    (class Cow
        (private
            (int age))
        (public
            (cMethod Cow (int age, double time)
                (= this->age age)
                (= this->time time)
            )

    )";
    Lexer lexer(input);
//    Token token;
//    do {
//        token = lexer.getNextToken();
//        llvm::outs() << "Token: " << token.value << "\n";
//        llvm::outs()<< "Kind: " << token.kind << "\n";
//    } while (token.kind != tok_eof);
//
//    return 0;
//}
    Parser parser(lexer);

    try {
        parser.parse();
        llvm::outs() << "Parsing completed successfully.\n";
    } catch (const std::exception &e) {
        llvm::errs() << "Error during parsing: " << e.what() << "\n";
        return 1;
    }

    return 0;
}