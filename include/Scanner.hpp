#ifndef SCANNER_HPP
#define SCANNER_HPP
#include <iostream>
#include <string>
#include "Error.hpp"

namespace jialuohu{
    namespace json{

        class Scanner{
        public:
            enum class JsonTokenType {
                BEGIN_OBJECT,       // {
                END_OBJECT,         // }

                VALUE_SEPARATOR,    // ,
                NAME_SEPARATOR,     // :

                VALUE_STRING,       // "string"
                VALUE_NUMBER,       // 1,2,2e10

                LITERAL_TRUE,       // true
                LITERAL_FALSE,      // false
                LITERAL_NULL,       // null

                BEGIN_ARRAY,        // [
                END_ARRAY,          // ]

                END_OF_SOURCE,      // EOF

            };


            friend std::ostream& operator<<(std::ostream& os, const JsonTokenType& type) {
                switch (type) {
                case JsonTokenType::BEGIN_ARRAY:
                    os << "[";
                    break;
                case JsonTokenType::END_ARRAY:
                    os << "]";
                    break;
                case JsonTokenType::BEGIN_OBJECT:
                    os << "{";
                    break;
                case JsonTokenType::END_OBJECT:
                    os << "}";
                    break;
                case JsonTokenType::NAME_SEPARATOR:
                    os << ":";
                    break;
                case JsonTokenType::VALUE_SEPARATOR:
                    os << ",";
                    break;
                case JsonTokenType::VALUE_NUMBER:
                    os << "number";
                    break;
                case JsonTokenType::VALUE_STRING:
                    os << "string";
                    break;
                case JsonTokenType::LITERAL_TRUE:
                    os << "true";
                    break;
                case JsonTokenType::LITERAL_FALSE:
                    os << "false";
                    break;
                case JsonTokenType::LITERAL_NULL:
                    os << "null";
                    break;
                case JsonTokenType::END_OF_SOURCE:
                    os << "EOF";
                    break;
                default:
                    break;
                }
                return os;
            }

            Scanner(const std::string& source);
            JsonTokenType Scan();
            std::string GetValueString();
            float GetValueNumber();

        private:
            bool IsAtEnd();
            char Advance();
            void ScanTrue();
            void ScanFalse();
            void ScanNull();
            char Peek();
            void ScanString();
            void ScanNumber();

        private:
            std::string source_;    // json source
            size_t current_;       // current pos

            std::string value_string_;
            float value_number_;
        };




    }   // namespace json
}   // namespace jialuohu




#endif