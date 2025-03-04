cmake_minimum_required(VERSION 3.13)
project(KoiScriptParserDriver LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -pedantic")

message(STATUS "CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")


# Include yacc stuff
include_directories("C:/GnuWin32/include")


# Create the yacc stuff in the binary tree so it gets cleaned up and jazz
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/flex)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/yacc)

execute_process(
        COMMAND flex.exe ${PROJECT_SOURCE_DIR}/../lexer_drivers/koiscript.l
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/flex
)

execute_process(
        COMMAND bison -dy ${PROJECT_SOURCE_DIR}/koiscript.y
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/yacc
)


add_custom_target(FlexCommandForBison
        COMMAND flex.exe ${PROJECT_SOURCE_DIR}/../lexer_drivers/koiscript.l
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/flex
        BYPRODUCTS ${PROJECT_BINARY_DIR}/flex/lex.yy.c
)


add_custom_target(BisonCommand
        COMMAND bison -dy ${PROJECT_SOURCE_DIR}/koiscript.y
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/yacc
        BYPRODUCTS ${PROJECT_BINARY_DIR}/yacc/y.tab.h ${PROJECT_BINARY_DIR}/yacc/y.tab.c
)


# Build the internal lexer c library
# todo:: allow for different driver implementations in the build system. so far just flex.
add_library(${PROJECT_NAME} STATIC
        ${PROJECT_BINARY_DIR}/flex/lex.yy.c
        ${PROJECT_BINARY_DIR}/yacc/y.tab.h
        ${PROJECT_BINARY_DIR}/yacc/y.tab.c
        include/parser_drivers/parser_driver.h
        source/yacc_parser_driver.c
)

add_dependencies(${PROJECT_NAME} FlexCommandForBison BisonCommand)

target_include_directories(${PROJECT_NAME} PUBLIC
        include
        ${PROJECT_BINARY_DIR}/yacc
        ${PROJECT_BINARY_DIR}/flex
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        KoiScriptDriversCommon
)

#add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
#        COMMAND bison -dy ${PROJECT_SOURCE_DIR}/koiscript.y
#        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/yacc
#        BYPRODUCTS ${PROJECT_BINARY_DIR}/yacc/y.tab.h ${PROJECT_BINARY_DIR}/yacc/y.tab.c
#)


# Build the internal lexer library's debug executable
add_executable(ParserDriverDebug
        debug/main.c
)

target_link_libraries(ParserDriverDebug PRIVATE
        ${PROJECT_NAME}
)
