cmake_minimum_required(VERSION 3.13)

set(ENV{FL_LIBRARY_PATH} "C:/GnuWin32/lib/libfl.a")
set(ENV{GNU_WIN_32_LIB_PATH} "C:/GnuWin32/lib")
set(ENV{GNU_WIN_32_INCLUDE_PATH} "C:/GnuWin32/include")

message(STATUS $ENV{FL_LIBRARY_PATH})
