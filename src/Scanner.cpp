#include "Scanner.hpp"

namespace jialuohu{
    namespace json{
        
        Scanner::Scanner(const std::string& source)
        : source_(source), current_(0) {}

        bool Scanner::IsAtEnd(){
            return current_ >= source_.size();
        }

        char Scanner::Advance(){
            return source_[current_++];
        }

        void Scanner::ScanTrue(){
            if (source_.compare(current_, 3, "rue") == 0){
                current_ += 3;
            } else{
                Error("Scan `true` error");
            }
        }

        void Scanner::ScanFalse(){
            if (source_.compare(current_,4,"alse") == 0){
                current_ += 4;
            } else{
                Error("Scan `false` error");
            }
        }

        void Scanner::ScanNull(){
            if (source_.compare(current_,3,"ull") == 0){
                current_ += 3;
            } else{
                Error("Scan `null` error");
            }
        }

        char Scanner::Peek(){
            return source_[current_];
        }

        void Scanner::ScanString(){
            char pos = current_;
            while(Peek() != '\"' && !IsAtEnd()){
                Advance();
                if ( Peek() == '\\'){
                    Advance();
                    switch (Peek()){
                        case 'b':
                        case 'f':
                        case 'n':
                        case 'r':
                        case 't':
                        case '\"':
                        case '\\':
                            Advance();
                            break;
                        case 'u':
                            for (int i = 0; i <= 4; i++) Advance();
                            break;
                        default:
                            break;
                    }
                }
            }
            
            if (IsAtEnd()){
                Error("invalid string: missing closing quote");
            }

            value_string_ = source_.substr(pos, current_ - pos);
            Advance();
        }
        

        void Scanner::ScanNumber(){
            current_ --;
            bool isNeg = false;
            float res = 0;
            if (Peek() == '-'){
                isNeg = true;
                Advance();
            }

            while(isdigit(Peek()) && !IsAtEnd()){
                res = 10 * res + (Peek() - '0');
                Advance();
            }

            // fraction part
            if (Peek() == '.'){
                std::string frac_res{"0."};
                Advance();
                while(isdigit(Peek()) && !IsAtEnd()){
                    frac_res += std::string{Peek()};
                    Advance();
                }
                res += std::stof(frac_res);
            }

            value_number_ = (isNeg? -1 * res : res);
        }


        Scanner::JsonTokenType Scanner::Scan(){
            if (IsAtEnd()){
                return JsonTokenType::END_OF_SOURCE;
            }

            char c = Advance();
            switch (c)
            {
            case '{':
                return JsonTokenType::BEGIN_OBJECT;
            case '}':
                return JsonTokenType::END_OBJECT;
            case '[':
                return JsonTokenType::BEGIN_ARRAY;
            case ']':
                return JsonTokenType::END_ARRAY;
            case ':':
                return JsonTokenType::NAME_SEPARATOR;
            case ',':
                return JsonTokenType::VALUE_SEPARATOR;
            case 't':
                ScanTrue();
                return JsonTokenType::LITERAL_TRUE;
            case 'f':
                ScanFalse();
                return JsonTokenType::LITERAL_FALSE;
            case 'n':
                ScanNull();
                return JsonTokenType::LITERAL_NULL;

            case ' ':
            case '\t':
            case '\n':
            case '\r':
                return Scan();
            
            case '\"':
                ScanString();
                return JsonTokenType::VALUE_STRING;
            case '-':
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                ScanNumber();
                return JsonTokenType::VALUE_NUMBER;

            default:
                Error("Unsupported Token: " + c);
            }

            return JsonTokenType();
        }

        std::string Scanner::GetValueString(){
            return value_string_;
        }

        float Scanner::GetValueNumber(){
            return value_number_;
        }

    }
}