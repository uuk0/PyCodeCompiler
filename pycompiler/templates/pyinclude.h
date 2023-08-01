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


enum PyObjectType
{
    PY_TYPE_NONE,  // -
    PY_TYPE_BOOL,  // 0 = False, 1 = True
    PY_TYPE_INT,   // int64_t
    PY_TYPE_FLOAT, // double precision
    PY_IMPL,       // a class implemented in python
};
typedef enum PyObjectType PyObjectType;


struct PyClassContainer
{
    struct PyClassContainer** parents;

    char* class_name;

    char** attr_name_array;

    char** static_attribute_names;
    struct PyObjectContainer** static_attribute_values;
};
typedef struct PyClassContainer PyClassContainer;


struct PyObjectContainer
{
    PyObjectType type;
    void* raw_value;
    PyClassContainer* py_type;
    struct PyObjectContainer* attr_array;
};
typedef struct PyObjectContainer PyObjectContainer;



extern PyObjectContainer* PY_NONE;
extern PyObjectContainer* PY_FALSE;
extern PyObjectContainer* PY_TRUE;


PyObjectContainer* createEmptyContainer(PyObjectType type);

PyClassContainer* PY_createClassContainer(char* name);
void PY_ClassContainer_AllocateParentArray(PyClassContainer* cls, uint8_t count);

PyObjectContainer* PY_createInteger(int64_t value);
int64_t PY_unpackInteger(PyObjectContainer* obj);

void initialize();
#endif

