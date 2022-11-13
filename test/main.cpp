#include <iostream>
#include "Scanner.hpp"


int main(){
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

    return 0;
}