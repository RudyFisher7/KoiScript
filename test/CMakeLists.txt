cmake_minimum_required(VERSION 3.13)
project(KoiScriptTest)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

Include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)


set(LEVER_DECLARATION_TEST LexerDeclarationTest)

add_executable(${LEVER_DECLARATION_TEST}
    lexer_declaration_test.cpp
)

target_link_libraries(${LEVER_DECLARATION_TEST} PRIVATE
    KoiScript
    Catch2::Catch2
)


set(LEVER_META_TEST LexerMetaTest)

add_executable(${LEVER_META_TEST}
    lexer_meta_test.cpp
)

target_link_libraries(${LEVER_META_TEST} PRIVATE
    KoiScript
    Catch2::Catch2
)


set(RUNTIME_VARIABLE_TEST RuntimeVariableTest)

add_executable(${RUNTIME_VARIABLE_TEST}
    runtime_variable_test.cpp
)

target_link_libraries(${RUNTIME_VARIABLE_TEST} PRIVATE
    KoiScript
    Catch2::Catch2
)


set(RUNTIME_ARRAY_TEST RuntimeArrayTest)

add_executable(${RUNTIME_ARRAY_TEST}
    runtime_array_test.cpp
)

target_link_libraries(${RUNTIME_ARRAY_TEST} PRIVATE
    KoiScript
    Catch2::Catch2
)


set(RUNTIME_FUNCTION_TEST RuntimeFunctionTest)

add_executable(${RUNTIME_FUNCTION_TEST}
    runtime_function_test.cpp
)

target_link_libraries(${RUNTIME_FUNCTION_TEST} PRIVATE
    KoiScript
    Catch2::Catch2
)
