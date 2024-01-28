#include "lexer.h"
#include <llvm/Support/raw_ostream.h>

int main() {
    const char *input = R"(
    (class Cow
        (private
            (string name)
            (int age))
          (public
            (method (Cow (string name) (int age))
                (= this.name name)
                (= this.age age))
            (method (toString)
                (print "Name: " name ", Age: " age))))
    (function main (void)
        (Cow* cow1) ;this is a pointer not an obj
        (Cow* cow2)

        (= Cow1 (new Cow cow1 1)) ;this instantiate a cow obj on the heap
        (= Cow2 (new Cow cow2 4))
        (delete cow1)
        (delete cow2)
        (= Cow1 nullptr)
        (= Cow2 nullptr))
    )";

    Lexer lexer(input);
    Token token;
    do {
        token = lexer.getNextToken();
        llvm::outs() << "Token: " << token.value << "\n";
    } while (token.kind != tok_eof);

    return 0;
}