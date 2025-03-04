cmake_minimum_required(VERSION 3.13)
project(KoiScriptDriversCommon LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -pedantic")

message(STATUS "CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")


# Build the internal lexer c library
# todo:: allow for different driver implementations in the build system. so far just flex.
add_library(${PROJECT_NAME} STATIC
        include/drivers_common/token_type.h
        source/token.c
        include/drivers_common/token.h
        include/drivers_common/token_tree.h
        source/token_tree.c
)

target_include_directories(${PROJECT_NAME} PUBLIC
        include
)


# Build the internal lexer library's debug executable
add_executable(DriversCommonDebug
        debug/main.c
)

target_link_libraries(DriversCommonDebug PRIVATE
        ${PROJECT_NAME}
)
