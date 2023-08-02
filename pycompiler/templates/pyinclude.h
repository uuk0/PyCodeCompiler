//
// Created by baulu on 31.07.2023.
//

#pragma once
#ifndef PYINCLUDE
#define PYINCLUDE

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>


struct PyObjectContainer;
struct PyGeneratorContainer;
struct PyFunctionContext;


enum PyObjectType
{
    PY_TYPE_NONE,           // -
    PY_TYPE_BOOL,           // 0 = False, 1 = True
    PY_TYPE_INT,            // int64_t
    PY_TYPE_FLOAT,          // double precision
    PY_TYPE_PY_IMPL,        // a class implemented in python
    PY_TYPE_FUNC_POINTER,   // a c function pointer (boxed)
};
typedef enum PyObjectType PyObjectType;


struct PyClassContainer
{
    struct PyClassContainer** parents;

    char* class_name;

    char** attr_name_array;
    uint8_t attr_count;

    char** static_attribute_names;
    struct PyObjectContainer** static_attribute_values;
};
typedef struct PyClassContainer PyClassContainer;


struct PyObjectContainer
{
    PyObjectType type;
    void* raw_value;
    uint16_t refcount;
    uint16_t flags;
    PyClassContainer* py_type;
    struct PyObjectContainer** attr_array;
    struct PyObjectContainer* source;
};
typedef struct PyObjectContainer PyObjectContainer;


typedef PyObjectContainer* PY_FUNC_UNBOXED(PyObjectContainer* self, uint8_t param_count, PyObjectContainer** args);
typedef PyObjectContainer* PY_GEN_FUNC_UNBOXED(struct PyGeneratorContainer* generator, PyObjectContainer* self, uint8_t param_count, PyObjectContainer** args);


struct PyFunctionContext
{
    uint8_t local_count;
    char** local_names;
    PyObjectContainer** locals;
};


struct PyGeneratorContainer
{
    PY_FUNC_UNBOXED* next_entry;
    struct PyGeneratorContainer* remaining_yield_from;
    struct PyFunctionContext* context;
};



extern PyObjectContainer* PY_NONE;
extern PyObjectContainer* PY_FALSE;
extern PyObjectContainer* PY_TRUE;


PyObjectContainer* createEmptyContainer(PyObjectType type);

PyClassContainer* PY_createClassContainer(char* name);
void PY_ClassContainer_AllocateParentArray(PyClassContainer* cls, uint8_t count);

PyObjectContainer* PY_createClassInstance(PyClassContainer* cls);
PyObjectContainer* PY_createBoxForFunction(PY_FUNC_UNBOXED* func);

PyObjectContainer* PY_getObjectAttributeByName(PyObjectContainer* obj, char* name);
PyObjectContainer* PY_getObjectAttributeByNameOrStatic(PyObjectContainer* obj, char* name);
void PY_setObjectAttributeByName(PyObjectContainer* obj, char* name, PyObjectContainer* value);
void PY_setClassAttributeByName(PyClassContainer* cls, char* name, PyObjectContainer* value);
void PY_setClassAttributeByNameOrCreate(PyClassContainer* cls, char* name, PyObjectContainer* value);

PyObjectContainer* PY_invokeBoxedMethod(PyObjectContainer* obj, PyObjectContainer* self, uint8_t param_count, PyObjectContainer** args);

PyObjectContainer* PY_createInteger(int64_t value);
int64_t PY_unpackInteger(PyObjectContainer* obj);

void initialize();

#define INCREF(obj) obj->refcount++;
#define DECREF(obj) obj->refcount--; if (obj->refcount == 0) free(obj);

#endif

