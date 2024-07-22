cmake_minimum_required(VERSION 3.13)
project(KoiScript VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
    source/log/log.cpp
    include/scripting/log/log.hpp

    source/type.cpp
    include/scripting/type.hpp
    source/token.cpp
    include/scripting/token.hpp

    source/lexicon.cpp
    include/scripting/lexicon.hpp
    source/lexer.cpp
    include/scripting/lexer.hpp
    source/parser.cpp
    include/scripting/parser.hpp
    source/assembler.cpp
    include/scripting/assembler.hpp

    source/abstract_syntax_tree/node.cpp
    include/scripting/abstract_syntax_tree/node.hpp
    source/abstract_syntax_tree/meta.cpp
    include/scripting/abstract_syntax_tree/meta.hpp
    source/abstract_syntax_tree/literal.cpp
    include/scripting/abstract_syntax_tree/literal.hpp

    source/extensions/extensions.cpp
    include/scripting/extensions/extensions.hpp

    include/scripting/runtime/type_defs.hpp
    include/scripting/runtime/error.hpp

    source/runtime/environment.cpp
    include/scripting/runtime/environment.hpp
    source/runtime/global_environment.cpp
    include/scripting/runtime/global_environment.hpp

    source/runtime/array.cpp
    include/scripting/runtime/array.hpp
    source/runtime/function.cpp
    include/scripting/runtime/function.hpp
    source/runtime/variable.cpp
    include/scripting/runtime/variable.hpp
    source/runtime/variant.cpp
    include/scripting/runtime/variant.hpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    include
)


add_subdirectory(debug)

# fixme:: toggle with build option
add_subdirectory(test)
