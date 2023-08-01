//
// Created by baulu on 31.07.2023.
//

#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include "pyinclude.h"


static bool initialized = false;

PyObjectContainer* PY_NONE;
PyObjectContainer* PY_FALSE;
PyObjectContainer* PY_TRUE;

PyObjectContainer* createEmptyContainer(PyObjectType type)
{
    PyObjectContainer* container = malloc(sizeof(PyObjectContainer));

    if (container == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    container->type = type;
    container->raw_value = NULL;
    container->py_type = NULL;
    container->attr_array = NULL;
    return container;
}

PyClassContainer* PY_createClassContainer(char* name)
{
    PyClassContainer* container = malloc(sizeof(PyClassContainer));

    if (container == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    container->parents = NULL;
    container->class_name = name;
    container->attr_name_array = NULL;
    container->static_attribute_names = NULL;
    container->static_attribute_values = NULL;

    return container;
}

void PY_ClassContainer_AllocateParentArray(PyClassContainer* cls, uint8_t count)
{
    assert(cls->parents == NULL);

    cls->parents = calloc(count + 1, sizeof(PyClassContainer*));

    if (cls->parents == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
}

PyObjectContainer* PY_createInteger(int64_t value)
{
    uint64_t* value_holder = malloc(sizeof(uint64_t));

    if (value_holder == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    *value_holder = value;
    PyObjectContainer* container = createEmptyContainer(PY_TYPE_INT);
    container->raw_value = value_holder;
    return container;
}

int64_t PY_unpackInteger(PyObjectContainer* obj)
{
    assert(obj->type == PY_TYPE_INT);

    return *((int64_t*)obj->raw_value);
}

void initialize()
{
    if (initialized) return;

    PY_NONE = createEmptyContainer(PY_TYPE_NONE);
    PY_FALSE = createEmptyContainer(PY_TYPE_BOOL);
    PY_FALSE->raw_value = (void*)0;
    PY_TRUE = createEmptyContainer(PY_TYPE_BOOL);
    PY_TRUE->raw_value = (void*)1;

    initialized = true;
}

