cmake_minimum_required(VERSION 3.26)
project(sources C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(standard_library)

add_executable(sources
        standard_library/int.c
        standard_library/int.h
        pyinclude.c
        pyinclude.h
        standard_library/functions.h
        standard_library/functions.c)
