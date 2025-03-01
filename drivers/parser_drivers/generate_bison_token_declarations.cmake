set(EnumFilePath "../common/include/drivers_common/token_type.h")

file(READ ${EnumFilePath} EnumFile)

string(REPLACE "\n" ";" FileLines ${EnumFile})

foreach(Line IN LISTS FileLines)
    if (Line MATCHES "MIN,$")
        message(STATUS ${Line})
    endif()
endforeach()