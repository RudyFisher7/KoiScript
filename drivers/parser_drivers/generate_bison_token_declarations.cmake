cmake_minimum_required(VERSION 3.13)


set(EnumFilePath "../common/include/drivers_common/token_type.h")

file(READ ${EnumFilePath} EnumFile)

string(REPLACE "\n" ";" FileLines ${EnumFile})

set(StartLine "")
set(i 0)
list(LENGTH FileLines LinesSize)
while(StartLine STREQUAL "" AND i LESS LinesSize)
    list(GET FileLines ${i} Line)
    if (Line MATCHES "{$")
        set(StartLine ${Line})
    endif()
    MATH(EXPR i ${i}+1)
endwhile()

message(STATUS ${StartLine})

set(Tokens "")

set(EndLine "")
while(EndLine STREQUAL "" AND i LESS LinesSize)
    list(GET FileLines ${i} Line)
    if (Line MATCHES "SIZE$")
        set(EndLine ${Line})
    endif()
    MATH(EXPR i ${i}+1)
endwhile()

message(STATUS ${EndLine})
