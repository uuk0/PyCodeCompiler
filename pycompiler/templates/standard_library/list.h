//
// Created by baulu on 03.08.2023.
//

#ifndef TEMPLATES_LIST_H
#define TEMPLATES_LIST_H

#include "pyinclude.h"

struct PY_STD_list_container
{
    uint16_t curr_size;
    uint16_t rem_size;
    PyObjectContainer** array;
};
typedef struct PY_STD_list_container PY_STD_list_container;

extern PyClassContainer* PY_TYPE_LIST;
PyObjectContainer* PY_STD_list_init(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_STD_list_init_fast_arg_0(PyObjectContainer* self);
PyObjectContainer* PY_STD_list_init_fast_arg_1(PyObjectContainer* self, PyObjectContainer* source);
PyObjectContainer* PY_STD_list_CONSTRUCT(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_STD_list_CREATE(uint8_t argc, ...);

PyObjectContainer* PY_STD_list_append(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_STD_list_append_fast(PyObjectContainer* self, PyObjectContainer* param);

PyObjectContainer* PY_STD_list_insert(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_STD_list_insert_fast(PyObjectContainer* self, PyObjectContainer* index, PyObjectContainer* value);
PyObjectContainer* PY_STD_list_insert_fast_with_int(PyObjectContainer* self, int64_t index, PyObjectContainer* value);

PyObjectContainer* PY_STD_list_index(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_STD_list_index_fast(PyObjectContainer* self, PyObjectContainer* value);
int64_t PY_STD_list_index_fast_list(PyObjectContainer* self, PyObjectContainer* value);

PyObjectContainer* PY_STD_list_remove(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);

PyObjectContainer* PY_STD_list_setAtIndex(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_STD_list_setAtIndex_fast(PyObjectContainer* self, PyObjectContainer* index, PyObjectContainer* value);
PyObjectContainer* PY_STD_list_setAtIndex_fast_with_int(PyObjectContainer* self, int64_t index, PyObjectContainer* value);

PyObjectContainer* PY_STD_list_getAtIndex(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_STD_list_getAtIndex_fast(PyObjectContainer* self, PyObjectContainer* index);
PyObjectContainer* PY_STD_list_getAtIndex_fast_with_int(PyObjectContainer* self, int64_t index);

PyObjectContainer* PY_STD_list_removeAtIndex(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);

PyObjectContainer* PY_STD_list_clear(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_STD_list_clear_fast(PyObjectContainer* self);

PyObjectContainer* PY_STD_list_eq(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);

PyObjectContainer* PY_STD_list_len(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_STD_list_len_fast(PyObjectContainer* self);

PyObjectContainer* PY_STD_list_toBool(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_STD_list_toBool_fast(PyObjectContainer* self);

PyObjectContainer* PY_STD_list_iter(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_STD_list_iter_fast(PyObjectContainer* self);

PyObjectContainer* PY_STD_list_sort(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);

void PY_STD_initListType(void);

#endif //TEMPLATES_LIST_H
