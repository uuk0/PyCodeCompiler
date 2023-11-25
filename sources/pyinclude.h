//
// Created by baulu on 17.11.2023.
//

#ifndef SOURCES_PYINCLUDE_H
#define SOURCES_PYINCLUDE_H

#include <stdint.h>

#define PY_OBJ_FLAG_HAS_ATTR_PAIR_CLASS_MANAGED_LIST 0
#define PY_OBJ_FLAG_HAS_ATTR_PAIR_LIST 1
#define PY_OBJ_FLAG_HAS_ATTR_HASHMAP 2
#define PY_OBJ_IS_EXTERNAL_POINTER 3

#define PY_IS_STABLE_OBJECT 4
#define PY_IS_STACK_ALLOCATED 5

struct PyClass {

};
typedef struct PyClass PyClass;

struct PyObject {
    PyClass* py_class;
    uint16_t flags;
    void* attribute_table;
    uint16_t ref_counter;
};
typedef struct PyObject PyObject;

struct ExecutionInfo {

};
typedef struct ExecutionInfo ExecutionInfo;

typedef void* (*PY_FUNCTION_SIGNATURE)(void* self, uint16_t argc, void** args, ExecutionInfo* info);

PyObject* PY_STD_create_malloced_object(PyClass* cls);
PyObject* PY_STD_create_stacked_object(PyClass* cls, PyObject* obj);

#define PY_CHECK_EXCEPTION(value) { void* v = value; if (v == NULL) return NULL; v; }

#endif //SOURCES_PYINCLUDE_H
