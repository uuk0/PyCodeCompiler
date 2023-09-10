//
// Created by baulu on 05.09.2023.
//

#ifndef PYCCOMPILER_DICT_H
#define PYCCOMPILER_DICT_H

#include "pyinclude.h"

extern PyClassContainer* PY_TYPE_DICT;

PyObjectContainer* PY_STD_dict_CREATE(uint8_t argc, ...);
PyObjectContainer* PY_STD_dict_init(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_STD_dict_init_fast_arg_zero(PyObjectContainer* self);

PyObjectContainer* PY_STD_dict_get(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_STD_dict_get_fast_arg_2(PyObjectContainer* self, PyObjectContainer* key, PyObjectContainer* default_value);

PyObjectContainer* PY_STD_dict_setitem(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_STD_dict_setitem_fast(PyObjectContainer* self, PyObjectContainer* key, PyObjectContainer* value);

PyObjectContainer* PY_STD_dict_getitem(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_STD_dict_getitem_fast(PyObjectContainer* self, PyObjectContainer* key);

PyObjectContainer* PY_STD_dict_delitem(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_STD_dict_delitem_fast(PyObjectContainer* self, PyObjectContainer* key);

PyObjectContainer* PY_STD_dict_contains(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_STD_dict_contains_fast(PyObjectContainer* self, PyObjectContainer* key);

void PY_STD_initDictType(void);

#endif //PYCCOMPILER_DICT_H
