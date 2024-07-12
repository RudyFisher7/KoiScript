cmake_minimum_required(VERSION 3.13)
project(KoiScript)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
    source/lexer.cpp
    include/scripting/lexer.hpp
    source/variant.cpp
    include/scripting/variant.hpp
    source/token.cpp
    include/scripting/token.hpp
    source/grammar.cpp
    include/scripting/grammar.hpp
    source/parser.cpp
    include/scripting/parser.hpp
    source/std_lib.cpp
    include/scripting/std_lib.hpp
    include/scripting/lib_registrar.cpp
    include/scripting/lib_registrar.hpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    include
)


add_subdirectory(debug)
