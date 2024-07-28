cmake_minimum_required(VERSION 3.13)
project(KoiScript VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
    source/log/log.cpp
    include/scripting/log/log.hpp

    source/token.cpp
    include/scripting/token.hpp

    source/lexicon.cpp
    include/scripting/lexicon.hpp
    source/lexer.cpp
    include/scripting/lexer.hpp
#    source/parser.cpp
#    include/scripting/parser.hpp
#    source/assembler.cpp
#    include/scripting/assembler.hpp
#    source/koi_script.cpp
#    include/scripting/koi_script.hpp

#    source/abstract_syntax_tree/node.cpp
#    include/scripting/abstract_syntax_tree/node.hpp

    source/extensions/extensions.cpp
    include/scripting/extensions/extensions.hpp

    include/scripting/runtime/basic_type.hpp
    include/scripting/runtime/error.hpp

    source/runtime/environment.cpp
    include/scripting/runtime/environment.hpp

    source/runtime/variant/i_variant.cpp
    include/scripting/runtime/variant/i_variant.hpp
    source/runtime/variant/variable.cpp
    include/scripting/runtime/variant/variable.hpp
    source/runtime/variant/array.cpp
    include/scripting/runtime/variant/array.hpp
    source/runtime/variant/function.cpp
    include/scripting/runtime/variant/function.hpp

    include/scripting/runtime/meta/i_meta.hpp

    include/scripting/runtime/meta/i_env.hpp
    source/runtime/meta/i_env.cpp
    source/runtime/meta/ref.cpp
    include/scripting/runtime/meta/ref.hpp
    source/runtime/meta/var.cpp
    include/scripting/runtime/meta/var.hpp
    source/runtime/meta/assign.cpp
    include/scripting/runtime/meta/assign.hpp
#    source/runtime/meta/exe.cpp
#    include/scripting/runtime/meta/exe.hpp
#    source/runtime/meta/val.cpp
#    include/scripting/runtime/meta/val.hpp

    source/runtime/meta/main.cpp
    include/scripting/runtime/meta/main.hpp
    source/runtime/meta/print.cpp
    include/scripting/runtime/meta/print.hpp
    source/runtime/lib/built_in.cpp
    include/scripting/runtime/lib/built_in.hpp
    include/scripting/runtime/lib/i_library.hpp
    #    source/runtime/meta/fun_lit.cpp
#    include/scripting/runtime/meta/fun_lit.hpp
#    source/runtime/meta/i_lit.cpp
#    include/scripting/runtime/meta/i_lit.hpp
#    source/runtime/meta/var_lit.cpp
#    include/scripting/runtime/meta/var_lit.hpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    include
)


add_subdirectory(debug)

# fixme:: toggle with build option
add_subdirectory(test)
