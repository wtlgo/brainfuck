cmake_minimum_required(VERSION 3.13)
project(brainfuck VERSION 1.0.2)

add_definitions(-DBF_VERSION="${PROJECT_VERSION}")

add_subdirectory(lib)
add_subdirectory(bin)

install(
    TARGETS bf-bin bf-lib
    LIBRARY DESTINATION lib/wtlgo COMPONENT Runtime
    ARCHIVE DESTINATION lib/wtlgo COMPONENT Development
    RUNTIME DESTINATION bin COMPONENT Runtime
    PUBLIC_HEADER DESTINATION include/wtlgo COMPONENT Development
)
