cmake_minimum_required(VERSION 3.13)
project(KoiScriptLexerDriver LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -pedantic")

message(STATUS "CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")


# Include flex stuff
link_directories("C:/GnuWin32/lib")
add_library(fl STATIC IMPORTED)
set_target_properties(fl PROPERTIES
        IMPORTED_LOCATION "C:/GnuWin32/lib/libfl.a"
        INTERFACE_INCLUDE_DIRECTORIES "C:/GnuWin32/lib"
)

include_directories("C:/GnuWin32/include")


# Create the flex stuff in the binary tree so it gets cleaned up and jazz
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/flex)

execute_process(
        COMMAND flex.exe ${PROJECT_SOURCE_DIR}/koiscript.l
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/flex
)


add_custom_target(FlexCommand
        COMMAND flex.exe ${PROJECT_SOURCE_DIR}/koiscript.l
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/flex
        BYPRODUCTS ${PROJECT_BINARY_DIR}/flex/lex.yy.c
)


# Build the internal lexer c library
# todo:: allow for different driver implementations in the build system. so far just flex.
add_library(${PROJECT_NAME} STATIC
        ${PROJECT_BINARY_DIR}/flex/lex.yy.c
        include/lexer_drivers/lexer_driver.h
        source/flex_lexer_driver.c
)

add_dependencies(${PROJECT_NAME} FlexCommand)

target_link_libraries(${PROJECT_NAME} PRIVATE
        KoiScriptDriversCommon
        fl
)

target_include_directories(${PROJECT_NAME} PUBLIC
        include
        PRIVATE ${PROJECT_BINARY_DIR}/flex
)


# Build the internal lexer library's debug executable
add_executable(LexerDriverDebug
        debug/main.c
)

target_link_libraries(LexerDriverDebug PRIVATE
        ${PROJECT_NAME}
)
