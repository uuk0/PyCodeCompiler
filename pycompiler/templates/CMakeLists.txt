cmake_minimum_required(VERSION 3.26)

project(PyCCompiler)

include_directories(.)

add_library(templates
        pyinclude.c
        pyinclude.h
        standard_library/init.c
        standard_library/init.h
        standard_library/list.c
        standard_library/list.h
        standard_library/int.c
        standard_library/int.h
        standard_library/tuple.c
        standard_library/tuple.h
        standard_library/operators.c
        standard_library/operators.h
        standard_library/importhelper.c
        standard_library/importhelper.h
        standard_library/importhelper.c
        standard_library/helpers/hashmap.c
        standard_library/helpers/hashmap.h
        standard_library/dict.c
        standard_library/dict.h
        standard_library/string.c
        standard_library/string.h
        standard_library/exceptions.h
        standard_library/exceptions.c
        standard_library/modules/typing.c
        standard_library/modules/typing.h
        standard_library/modules/unittest.c
        standard_library/modules/unittest.h
        standard_library/generator.c
        standard_library/generator.h
        standard_library/config.h
)

add_executable(test
        test.c
        pyinclude.c
)
