cmake_minimum_required(VERSION 3.13)
project(KoiScriptDebug)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
    debug.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    KoiScript
)
