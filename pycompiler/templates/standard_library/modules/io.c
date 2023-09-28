//
// Created by baulu on 28.09.2023.
//

#include <stdio.h>
#include "io.h"
#include "standard_library/parameters.h"
#include "standard_library/exceptions.h"

PyObjectContainer* PY_STD_print(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info) {
    PyObjectContainer** unpacked_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);

    PyObjectContainer* raw_sep_text = PY_ARGS_getKeywordParameter(args, info, "sep");
    char* sep_text = " ";
    if (raw_sep_text) sep_text = PY_unpackString(raw_sep_text);

    PyObjectContainer * raw_end_text = PY_ARGS_getKeywordParameter(args, info, "end");
    char* end_text = "\n";
    if (raw_end_text) end_text = PY_unpackString(raw_end_text);

    FILE* file = stdout; // todo: allow file parameter!

    for (int i = 0; i < argc; i++) {
        fprintf(file, "%s", PY_unpackString(PY_CHECK_EXCEPTION(PY_getObjectStr_wrapper(unpacked_args[i]))));

        if (i < argc - 1) {
            fprintf(file, "%s", sep_text);
        }
    }

    fprintf(file, "%s", end_text);
    fflush(file);

    if (info) {
        free(unpacked_args);
    }
    return PY_NONE;
}
