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


add_executable(${PROJECT_NAME}
    lexer_simple_tests.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    KoiScript
    Catch2::Catch2
)
