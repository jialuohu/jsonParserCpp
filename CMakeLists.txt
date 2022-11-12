CMAKE_MINIMUM_REQUIRED(VERSION 3.16)

SET(CMAKE_CXX_COMPILER g++)
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_BUILD_TYPE Debug)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic-errors -Werror -Wextra")

SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")       # allow vscode debugger to set breakpoints

PROJECT(jsonParserCpp)

include_directories(./include)
add_executable(jsonParserTest ./test/main.cpp ./src/Parser.cpp ./src/Scanner.cpp)
