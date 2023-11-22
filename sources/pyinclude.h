//
// Created by baulu on 17.11.2023.
//

#ifndef SOURCES_PYINCLUDE_H
#define SOURCES_PYINCLUDE_H

#include <stdint.h>

struct PyObject {

};

struct ExecutionInfo {

};

typedef struct PyObject PyObject;

typedef void* (*PY_FUNCTION_SIGNATURE)(void* self, uint16_t argc, void** args, ExecutionInfo* info);

#define PY_CHECK_EXCEPTION(value) { void* v = value; if (v == NULL) return NULL; v; }

#endif //SOURCES_PYINCLUDE_H
