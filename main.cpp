#include "lexer.h"
#include "parser.h"
#include <llvm/Support/raw_ostream.h>

int main() {
    const char *input = R"(
    (class A(public(init int a) (= a 1)))
    (fn main()
        (init double b)
        (= b 2.5)
        )



    )";
    Lexer lexer(input);
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