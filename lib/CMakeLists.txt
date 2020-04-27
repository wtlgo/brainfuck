cmake_minimum_required(VERSION 3.13)
project(bf-lib VERSION 0.0.1)

add_library(bf-lib 
    src/bf.cpp

    src/AST.cpp
    src/tokenizer.cpp
    src/parser.cpp
    src/VM.cpp

    src/cell.cpp
    src/tape.cpp
)
target_compile_features(bf-lib PUBLIC cxx_std_14)
target_include_directories(bf-lib PRIVATE include/private include/public/wtlgo)
target_include_directories(bf-lib INTERFACE include/public)

file(GLOB PUBLIC_HEADERS
    "include/public/wtlgo/*.hpp"
)

set_target_properties(bf-lib PROPERTIES 
    OUTPUT_NAME bf
    PUBLIC_HEADER "${PUBLIC_HEADERS}"
)
