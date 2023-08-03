//
// Created by baulu on 03.08.2023.
//

#ifndef TEMPLATES_LIST_H
#define TEMPLATES_LIST_H

#include "pyinclude.h"

extern PyClassContainer* PY_TYPE_LIST;
PyObjectContainer* PY_STD_list_init(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args);
PyObjectContainer* PY_STD_list_append(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args);
PyObjectContainer* PY_STD_list_insert(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args);
PyObjectContainer* PY_STD_list_index(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args);
PyObjectContainer* PY_STD_list_remove(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args);
PyObjectContainer* PY_STD_list_setAtIndex(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args);
PyObjectContainer* PY_STD_list_getAtIndex(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args);
PyObjectContainer* PY_STD_list_removeAtIndex(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args);
PyObjectContainer* PY_STD_list_clear(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args);
PyObjectContainer* PY_STD_list_toBool(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args);

void PY_STD_initListType(void);

#endif //TEMPLATES_LIST_H
