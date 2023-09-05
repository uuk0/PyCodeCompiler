//
// Created by baulu on 05.09.2023.
//

#ifndef PYCCOMPILER_DICT_H
#define PYCCOMPILER_DICT_H

#include "pyinclude.h"

extern PyClassContainer* PY_TYPE_DICT;

PyObjectContainer* PY_STD_dict_init(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);

PyObjectContainer* PY_STD_dict_setitem(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_STD_dict_setitem_fast(PyObjectContainer* self, PyObjectContainer* key, PyObjectContainer* value);

void PY_STD_initDictType(void);

#endif //PYCCOMPILER_DICT_H
