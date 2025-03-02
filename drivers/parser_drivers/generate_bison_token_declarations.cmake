cmake_minimum_required(VERSION 3.13)


set(EnumFilePath "../common/include/drivers_common/token_type.h")

message(STATUS "\n\n-- USAGE***********************")
message(STATUS "First enum value must be assigned a value (e.g., 'MY_ENUM_VALUE = 256,').")
message(STATUS "Only the first enum may be assigned a value, the rest will be enumerated by this script.")
message(STATUS "The last enum value must end with 'SIZE'.")
message(STATUS "USAGE***********************\n\n")
message(STATUS "Loading: ${EnumFilePath}")

file(READ ${EnumFilePath} EnumFile)

string(REPLACE "\n" ";" FileLines ${EnumFile})

message(STATUS "Parsing enum for tokens...")

set(StartLine "")
set(i 0)
list(LENGTH FileLines LinesSize)
while (StartLine STREQUAL "" AND i LESS LinesSize)
    list(GET FileLines ${i} Line)
    if (Line MATCHES "{$")
        set(StartLine ${Line})
    endif ()
    MATH(EXPR i ${i}+1)
endwhile ()

list(GET FileLines ${i} StartLine)
string(REGEX MATCH "[0-9]+" TokenValue "${StartLine}")
message(STATUS "Starting at enum value: ${StartLine}")
if (TokenValue)
    message(STATUS "First value: ${TokenValue}")
endif ()

set(Tokens "")

set(EndLine "")
while (EndLine STREQUAL "" AND i LESS LinesSize)
    list(GET FileLines ${i} Line)

    string(STRIP "${Line}" StrippedLine)

    string(FIND "${StrippedLine}" " " SpaceIndex)
    string(FIND "${StrippedLine}" "," CommaIndex)

    if (NOT SpaceIndex EQUAL -1)
        string(SUBSTRING "${StrippedLine}" 0 ${SpaceIndex} EnumString)
    elseif (NOT CommaIndex EQUAL -1)
        string(SUBSTRING "${StrippedLine}" 0 ${CommaIndex} EnumString)
    else ()
        set(EnumString "${StrippedLine}")
    endif ()

    string(REPLACE "KOI_SCRIPT_TOKEN_TYPE" "YY" EnumString ${EnumString})

    list(APPEND Tokens "%token ${EnumString} ${TokenValue}\n")

    MATH(EXPR TokenValue ${TokenValue}+1)

    if (Line MATCHES "SIZE$")
        set(EndLine ${Line})
    endif ()
    MATH(EXPR i ${i}+1)
endwhile ()

message(STATUS "Generating file koiscript_tokens.gen.txt...")

file(WRITE koiscript_tokens.gen.txt ${Tokens})
message(STATUS "Done.")
