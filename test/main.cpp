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
    auto source = R"####(
{"id":"I&CSCI53","department":"I&C SCI","number":"53","school":"Donald Bren School of Information and Computer Sciences","title":"Principles in System Design","course_level":"Lower Division (1-99)","department_alias":["ICS"],"units":[6,6],"description":"Introduces basic principles of system software: operating systems, compilers, and networking. Exposure to the following topics through theoretical and practical programming experiences: linking and loading, process and memory management, concurrency and synchronization, network communication, programming for performance, etc.","department_name":"Information and Computer Science","professor_history":["dutt","iharris","givargis","jwongma","klefstad","alfaro"],"prerequisite_tree":"{\"AND\":[\"I&C SCI 46\",\"I&C SCI 51\"]}","prerequisite_list":["I&C SCI 46","I&C SCI 51"],"prerequisite_text":" I&C SCI 46 and I&C SCI 51. I&C SCI 46 with a grade of C or better. I&C SCI 51 with a grade of C or better","prerequisite_for":["COMPSCI 122C","COMPSCI 131","COMPSCI 222"],"repeatability":"","grading_option":"","concurrent":"","same_as":"","restriction":"School of Info & Computer Sci students have first consideration for enrollment. Computer Science Engineering Majors have first consideration for enrollment.","overlap":"","corequisite":"","ge_list":[],"ge_text":"","terms":["2019 Winter","2019 Spring","2019 Fall","2020 Winter","2020 Spring","2020 Fall","2021 Winter","2021 Spring","2021 Fall","2022 Winter","2022 Spring","2022 Fall"]}
    )####";

    
    auto source2 = "[1, 2, 3, 4, 5, \"Hello\"]";

    Scanner scanner(source);
    Scanner scanner2(source2);
    Parser parser(scanner);
    Parser parser2(scanner2);

    JsonElement* res = parser.Parse();
    JsonElement* res2 = parser2.Parse();

    // JsonObject* obj = res->AsObject();
    // obj->insert({"tes", new JsonElement(20.0f)});

    std::cout << res->Dumps()  << '\n';
    std::cout << res2->Dumps()  << '\n';


    delete res;
    delete res2;
}

int main(){
    // testScanner();
    testParser();

    

    return 0;
}