#ifndef ERROR_HPP
#define ERROR_HPP

#include <stdexcept>

namespace jialuohu {
    namespace json {
        inline void Error(const char* message){ 
            throw std::logic_error(message); 
        }
    }  // namespace json
}  // namespace jialuohu

#endif