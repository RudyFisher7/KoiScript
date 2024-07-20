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
    source/lexicon.cpp
    include/scripting/lexicon.hpp
    source/parser.cpp
    include/scripting/parser.hpp
    source/std_lib.cpp
    include/scripting/std_lib.hpp
    source/lib_registrar.cpp
    include/scripting/lib_registrar.hpp
    source/scope.cpp
    include/scripting/closure.hpp
    include/scripting/type_defs.hpp
    include/scripting/token_buffer.cpp
    include/scripting/token_buffer.hpp
    source/log/log.cpp
    include/scripting/log/log.hpp
    source/extensions/extensions.cpp
    include/scripting/extensions/extensions.hpp
    source/ast_node.cpp
    include/scripting/ast_node.hpp
    source/type.cpp
    include/scripting/type.hpp
    source/assembler.cpp
    include/scripting/assembler.hpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    include
)


add_subdirectory(debug)

# fixme:: toggle with build option
add_subdirectory(test)
