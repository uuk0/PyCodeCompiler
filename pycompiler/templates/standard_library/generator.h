//
// Created by baulu on 08.09.2023.
//

#ifndef PYCCOMPILER_GENERATOR_H
#define PYCCOMPILER_GENERATOR_H

#include "pyinclude.h"

struct PyGeneratorContainer;
typedef PyObjectContainer* PY_GENERATOR_FRAGMENT(struct PyGeneratorContainer* generator);
struct PyGeneratorContainer
{
    PyObjectContainer** locals;
    PyObjectContainer* yield_from_source;
    PY_GENERATOR_FRAGMENT* next_section;
    uint16_t section_id;
};
typedef struct PyGeneratorContainer PyGeneratorContainer;

extern PyClassContainer* PY_TYPE_GENERATOR;

PyObjectContainer* PY_STD_GENERATOR_create(uint16_t local_count);
PyObjectContainer* PY_STD_GENERATOR_next(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_STD_GENERATOR_next_fast_arg_0(PyObjectContainer* self);
PyObjectContainer* PY_STD_GENERATOR_next_fast_arg_1(PyObjectContainer* self, PyObjectContainer* default_value);

PyObjectContainer* PY_STD_GENERATOR_CREATE_FILLED(PY_GENERATOR_FRAGMENT target, uint16_t local_count, ...);

PyObjectContainer* PY_STD_GENERATOR_iter(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);

PyObjectContainer* PY_STD_NEXT_FORWARD_arg_0(PyObjectContainer* self);
PyObjectContainer* PY_STD_NEXT_FORWARD_arg_1(PyObjectContainer* self, PyObjectContainer* default_value);

PyObjectContainer* PY_STD_range(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_STD_range_arg_1(PyObjectContainer* end);
PyObjectContainer* PY_STD_range_arg_2(PyObjectContainer* start, PyObjectContainer* end);
PyObjectContainer* PY_STD_range_arg_3(PyObjectContainer* start, PyObjectContainer* end, PyObjectContainer* step);

void PY_STD_initGeneratorType(void);

#endif //PYCCOMPILER_GENERATOR_H
