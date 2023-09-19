//
// Created by baulu on 05.09.2023.
//

#ifndef PYCCOMPILER_STRING_H
#define PYCCOMPILER_STRING_H

#include <assert.h>
#include "pyinclude.h"

extern PyObjectContainer* PY_STD_string_hash_CONTAINER;
PyObjectContainer* PY_STD_string_hash(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
extern PyObjectContainer* PY_STD_string_eq_CONTAINER;
PyObjectContainer* PY_STD_string_eq(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_STD_string_eq_fast(PyObjectContainer* lhs, PyObjectContainer* rhs);
extern PyObjectContainer* PY_STD_string_iter_CONTAINER;
PyObjectContainer* PY_STD_string_iter(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_STD_string_iter_fast(PyObjectContainer* self);

PyObjectContainer* PY_STD_string_startswith(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_STD_string_startswith_fast(PyObjectContainer* self, PyObjectContainer* other);
bool PY_STD_string_startswith_impl(char* self, char* other);

PyObjectContainer* PY_STD_string_add(PyObjectContainer* lhs, PyObjectContainer* rhs);

void PY_STD_initStringType(void);

#endif //PYCCOMPILER_STRING_H
