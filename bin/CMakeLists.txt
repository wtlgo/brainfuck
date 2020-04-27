cmake_minimum_required(VERSION 3.13)
project(bf-lib VERSION 1.0.0)

add_executable(bf-bin 
    src/main.cpp
    src/config.cpp
    src/utility.cpp
)
target_compile_features(bf-bin PUBLIC cxx_std_11)
target_include_directories(bf-bin PRIVATE include)
target_link_libraries(bf-bin PUBLIC bf-lib)
set_target_properties(bf-bin PROPERTIES OUTPUT_NAME bf)
