//
// Created by baulu on 03.08.2023.
//

#ifndef TEMPLATES_INT_H
#define TEMPLATES_INT_H

#include "pyinclude.h"

PyObjectContainer* PY_builtin_int_compare(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
void PY_STD_initIntType(void);

#endif //TEMPLATES_INT_H
