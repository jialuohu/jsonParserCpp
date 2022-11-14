#include <iostream>
#include "Scanner.hpp"
#include "Parser.hpp"
using std::endl, std::cout;

void testScanner(){
    using namespace jialuohu::json;
    
    auto source = R"(
    {
        "glossary" : {
            "test": true,
            "hello": null,
            "hello2": "miao\"miao"
        }
    }
    )";

    // auto source2 = "[1.0001,2.325,3,0.44,5,\"Hello\"]";

    Scanner scanner(source);
    // Scanner scanner(source2);

    Scanner::JsonTokenType type;
    while ((type = scanner.Scan()) != Scanner::JsonTokenType::END_OF_SOURCE) {
        std::cout << "Type: " << type;
        if (type == Scanner::JsonTokenType::VALUE_NUMBER) {
            std::cout << " Value: " << scanner.GetValueNumber();
        } else if (type == Scanner::JsonTokenType::VALUE_STRING) {
            std::cout << " Value: " << scanner.GetValueString();
        }
        std::cout << '\n';
    }
}

void testParser(){
    using namespace jialuohu::json;
    auto source = R"(
    {
        "glossary" : {
        "test": true,
        "hello": null,
        "hello2": "world\b\nwords!"
        }
    }
    )";
    auto source2 = "[1, 2, 3, 4, 5, \"Hello\"]";

    Scanner scanner(source);
    Scanner scanner2(source2);
    Parser parser(scanner);
    Parser parser2(scanner2);

    JsonElement* res = parser.Parse();
    JsonElement* res2 = parser2.Parse();

    std::cout << res->Dumps()  << '\n';
    std::cout << res2->Dumps()  << '\n';

    delete res;
}

int main(){
    // testScanner();
    testParser();

    

    return 0;
}