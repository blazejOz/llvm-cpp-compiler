#include "Lexer.hpp"
#include "Parser.hpp"
#include "IR_Generator.hpp"
#include "JITengine.hpp"

int main() {
    // 1. Lexing
    Lexer lexer(R"(

            fn tryWhile(int a): void
            {
                int i = a; 
                while(i > 0){
                    print(i);
                    i = i - 1;
                }
            }     

            fn main(): int
            {
                int x = 3;
                tryWhile(x);
                return 0;
            }

        )");

    auto tokens = lexer.tokenize();

    // 2. Parsing
    Parser parser(tokens);
    auto asts = parser.parse();

    for (const auto& ast : asts) {
        std::cout << "Parsed Statement: " << ast->toString() << std::endl;
    }

    // 3. IR Generation
    IRGenerator codegen;
    codegen.generate(asts);
    codegen.print();

    std::string irCodes = codegen.getIRString();

    JITengine engine;
    engine.runFromIRString(irCodes);
    

    return 0;
}