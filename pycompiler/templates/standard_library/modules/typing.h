//
// Created by baulu on 08.09.2023.
//

#ifndef PYCCOMPILER_TYPING_H
#define PYCCOMPILER_TYPING_H

#include "pyinclude.h"

extern PyObjectContainer* PY_MODULE_INSTANCE_typing;
extern PyClassContainer* PY_MODULE_typing_Generic;
extern PyClassContainer* PY_MODULE_typing_TypeVar;

PyObjectContainer* PY_MODULE_typing_Generic_class_getitem(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);

PyObjectContainer* PY_MODULE_typing_TypeVar_init(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_MODULE_typing_TypeVar_init_arg_1(PyObjectContainer* self, PyObjectContainer* name);

PyObjectContainer* PY_MODULE_typing_init(void);

#endif //PYCCOMPILER_TYPING_H
