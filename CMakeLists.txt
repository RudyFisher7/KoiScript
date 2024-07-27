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
#    source/parser.cpp
#    include/scripting/parser.hpp
    source/assembler.cpp
    include/scripting/assembler.hpp
    source/koi_script.cpp
    include/scripting/koi_script.hpp

    source/abstract_syntax_tree/node.cpp
    include/scripting/abstract_syntax_tree/node.hpp

    source/extensions/extensions.cpp
    include/scripting/extensions/extensions.hpp

    include/scripting/runtime/error.hpp

    source/runtime/environment.cpp
    include/scripting/runtime/environment.hpp

    source/runtime/data/array.cpp
    include/scripting/runtime/data/array.hpp
    source/runtime/data/function.cpp
    include/scripting/runtime/data/function.hpp
    source/runtime/data/variable.cpp
    include/scripting/runtime/data/variable.hpp
    source/runtime/data/variant.cpp
    include/scripting/runtime/data/variant.hpp
    source/runtime/meta/i_meta.cpp
    include/scripting/runtime/meta/i_meta.hpp
    source/runtime/meta/exe.cpp
    include/scripting/runtime/meta/exe.hpp
    source/runtime/meta/main.cpp
    include/scripting/runtime/meta/main.hpp
    source/runtime/meta/print.cpp
    include/scripting/runtime/meta/print.hpp
    source/runtime/meta/var.cpp
    include/scripting/runtime/meta/var.hpp
    include/scripting/runtime/meta/i_decl.hpp
    source/runtime/meta/assign.cpp
    include/scripting/runtime/meta/assign.hpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    include
)


add_subdirectory(debug)

# fixme:: toggle with build option
add_subdirectory(test)
