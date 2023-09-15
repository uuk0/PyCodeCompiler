//
// Created by baulu on 15.09.2023.
//

#ifndef PYCCOMPILER_ITERTOOLS_H
#define PYCCOMPILER_ITERTOOLS_H

#include "pyinclude.h"

extern PyObjectContainer* PY_MODULE_INSTANCE_itertools;

PyObjectContainer* PY_MODULE_itertools_chain(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);

PyObjectContainer* PY_MODULE_itertools_init(void);

#endif //PYCCOMPILER_ITERTOOLS_H
