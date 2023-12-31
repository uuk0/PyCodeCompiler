//
// Created by baulu on 03.08.2023.
//

#ifndef TEMPLATES_TUPLE_H
#define TEMPLATES_TUPLE_H

#include "pyinclude.h"

extern PyClassContainer* PY_TYPE_TUPLE;


void PY_STD_initTupleType(void);
PyObjectContainer* PY_STD_tuple_init(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_STD_tuple_CONSTRUCT(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_STD_tuple_CREATE(uint8_t argc, ...);
PyObjectContainer* PY_STD_tuple_index(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_STD_tuple_getAtIndex(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_STD_tuple_toBool(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);

PyObjectContainer* PY_STD_tuple_iter(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_STD_tuple_iter_fast(PyObjectContainer* self);

PyObjectContainer* PY_STD_tuple_repr(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_STD_tuple_repr_fast(PyObjectContainer* self);

PyObjectContainer* PY_STD_tuple_len(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_STD_tuple_len_fast(PyObjectContainer* self);

#endif //TEMPLATES_TUPLE_H
