cmake_minimum_required(VERSION 3.13)
project(KoiScriptLexicon LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -pedantic")

message(STATUS "CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")

link_directories("C:/Program Files (x86)/GnuWin32/lib")
add_library(fl STATIC IMPORTED)
set_target_properties(fl PROPERTIES
        IMPORTED_LOCATION "C:/Program Files (x86)/GnuWin32/lib/libfl.a"
        INTERFACE_INCLUDE_DIRECTORIES "C:/Program Files (x86)/GnuWin32/lib"
)

include_directories("C:/Program Files (x86)/GnuWin32/include")

#add_library(${PROJECT_NAME} STATIC
#        lex.yy.c
#)
#
#target_include_directories(${PROJECT_NAME} PUBLIC
#        .
#)

add_executable(LexDebug
        lex.yy.c
#        main.c
)

target_link_libraries(LexDebug PRIVATE
        fl
)

#target_compile_definitions(${PROJECT_NAME} PRIVATE
#    ENABLE_KOI_SCRIPTING_LOG=1
#)
#
#target_compile_options(${PROJECT_NAME} PRIVATE
#    -pedantic
#)
