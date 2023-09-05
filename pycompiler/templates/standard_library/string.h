//
// Created by baulu on 05.09.2023.
//

#ifndef PYCCOMPILER_STRING_H
#define PYCCOMPILER_STRING_H

#include <assert.h>
#include "pyinclude.h"

extern PyObjectContainer* PY_STD_string_hash_CONTAINER;
PyObjectContainer* PY_STD_string_hash(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);

void PY_STD_initStringType(void);

#endif //PYCCOMPILER_STRING_H
