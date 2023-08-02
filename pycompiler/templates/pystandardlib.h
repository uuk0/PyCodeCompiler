//
// Created by baulu on 02.08.2023.
//

#ifndef TEMPLATES_PYSTANDARDLIB_H
#define TEMPLATES_PYSTANDARDLIB_H

#include "pyinclude.h"

PyObjectContainer* PY_issubclass(PyObjectContainer* self, int argc, PyObjectContainer** args);
PyObjectContainer* PY_isinstance(PyObjectContainer* self, int argc, PyObjectContainer** args);

extern PyClassContainer* PY_TYPE_LIST;
PyObjectContainer* PY_STD_list_init(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args);
PyObjectContainer* PY_STD_list_append(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args);
PyObjectContainer* PY_STD_list_insert(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args);
PyObjectContainer* PY_STD_list_index(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args);
PyObjectContainer* PY_STD_list_remove(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args);
PyObjectContainer* PY_STD_list_setAtIndex(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args);
PyObjectContainer* PY_STD_list_getAtIndex(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args);
PyObjectContainer* PY_STD_list_removeAtIndex(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args);
PyObjectContainer* PY_STD_list_toBool(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args);

void PY_STD_INIT();

#endif //TEMPLATES_PYSTANDARDLIB_H
