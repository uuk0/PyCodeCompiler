//
// Created by baulu on 31.07.2023.
//

#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include "pyinclude.h"
#include <string.h>


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
    container->attr_count = 0;
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

PyObjectContainer* PY_createClassInstance(PyClassContainer* cls)
{
    PyObjectContainer* obj = createEmptyContainer(PY_TYPE_PY_IMPL);
    obj->py_type = cls;
    obj->attr_array = calloc(cls->attr_count, sizeof(PyObjectContainer*));

    if (obj->attr_array == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    return obj;
}

PyObjectContainer* PY_createBoxForFunction(PY_FUNC_UNBOXED* func)
{
    PyObjectContainer* obj = createEmptyContainer(PY_TYPE_FUNC_POINTER);
    obj->raw_value = func;
    return obj;
}

PyObjectContainer* PY_getObjectAttributeByName(PyObjectContainer* obj, char* name)
{
    // todo: can we implement it for other types also?
    assert(obj->type == PY_TYPE_PY_IMPL);

    PyClassContainer* cls = obj->py_type;
    assert(cls != NULL);

    for (int i = 0; i < cls->attr_count; i++)
    {
        if (strcmp(cls->attr_name_array[i], name) == 0)
        {
            return obj->attr_array[i];
        }
    }

    return NULL;
}

PyObjectContainer* PY_getObjectAttributeByNameOrStatic(PyObjectContainer* obj, char* name)
{
    // todo: can we implement it for other types also?
    assert(obj->type == PY_TYPE_PY_IMPL);

    PyClassContainer* cls = obj->py_type;
    assert(cls != NULL);

    for (int i = 0; i < cls->attr_count; i++)
    {
        if (strcmp(cls->attr_name_array[i], name) == 0)
        {
            return obj->attr_array[i];
        }
    }

    if (cls->static_attribute_names == NULL) return NULL;

    int i = 0;
    while (cls->static_attribute_names[i] != NULL)
    {
        if (strcmp(cls->static_attribute_names[i], name) == 0)
        {
            return cls->static_attribute_values[i];
        }
        i++;
    }

    return NULL;
}

void PY_setObjectAttributeByName(PyObjectContainer* obj, char* name, PyObjectContainer* value)
{
    // todo: can we implement it for other types also?
    assert(obj->type == PY_TYPE_PY_IMPL);

    PyClassContainer* cls = obj->py_type;
    assert(cls != NULL);

    for (int i = 0; i < cls->attr_count; i++)
    {
        if (strcmp(cls->attr_name_array[i], name) == 0)
        {
            obj->attr_array[i] = value;
            return;
        }
    }

    assert(false);
}

void PY_setClassAttributeByName(PyClassContainer* cls, char* name, PyObjectContainer* value)
{
    int i = 0;
    while (cls->static_attribute_names[i] != NULL)
    {
        if (strcmp(cls->static_attribute_names[i], name) == 0)
        {
            cls->static_attribute_values[i] = value;
            return;
        }
        i++;
    }

    assert(false);
}

void PY_setClassAttributeByNameOrCreate(PyClassContainer* cls, char* name, PyObjectContainer* value)
{
    int i = 0;
    while (cls->static_attribute_names[i] != NULL)
    {
        if (strcmp(cls->static_attribute_names[i], name) == 0)
        {
            cls->static_attribute_values[i] = value;
            return;
        }
        i++;
    }

    cls->static_attribute_names = realloc(cls->static_attribute_names, (i + 2) * sizeof(char*));
    if (cls->static_attribute_names == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    cls->static_attribute_values = realloc(cls->static_attribute_names, (i + 2) * sizeof(PyObjectContainer*));
    if (cls->static_attribute_values == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    cls->static_attribute_names[i] = name;
    cls->static_attribute_values[i] = value;
}

PyObjectContainer* PY_invokeBoxedMethod(PyObjectContainer* obj, PyObjectContainer* self, uint8_t param_count, PyObjectContainer** args)
{
    assert(obj->type == PY_TYPE_FUNC_POINTER);

    PY_FUNC_UNBOXED* function = (PY_FUNC_UNBOXED*)obj->raw_value;

    return function(self, param_count, args);
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

