#ifndef PARSER_HPP
#define PARSER_HPP

#include "JsonElement.hpp"
#include "Scanner.hpp"

namespace jialuohu{
    namespace json{
        class Parser{
        public:
            Parser(Scanner scanner);
            JsonElement* Parse();

        private:
            JsonObject* ParseObject();
            JsonArray* ParseArray();
            
        private:
            Scanner scanner_;
        };
    }


}


#endif