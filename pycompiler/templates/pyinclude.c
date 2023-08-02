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
    container->flags = 0;
    container->py_type = NULL;
    container->attr_array = NULL;
    container->source = NULL;
    container->refcount = 1;
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

    if (cls->attr_count != 0)
    {
        obj->attr_array = calloc(cls->attr_count, sizeof(PyObjectContainer *));

        if (obj->attr_array == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        obj->attr_array = NULL;
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

#define PY_TYPE_FUNC_HAS_SELF 1

static PyObjectContainer* PY_getObjectAttributeByNameOrStatic_StaticTransformer(PyObjectContainer* obj, PyObjectContainer* attr)
{
    // todo: handle more edge cases
    if (attr->type == PY_TYPE_FUNC_POINTER)
    {
        PyObjectContainer* new_attr = createEmptyContainer(PY_TYPE_FUNC_POINTER);
        new_attr->raw_value = attr->raw_value;
        new_attr->flags = attr->flags | PY_TYPE_FUNC_HAS_SELF;
        new_attr->source = obj;
        return new_attr;
    }

    return attr;
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
            return PY_getObjectAttributeByNameOrStatic_StaticTransformer(obj, cls->static_attribute_values[i]);
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

    assert(0 == "Attribute not found; Are you missing a declaration somewhere?");
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

    assert(0 == "Failed to set attribute; attribute does not exist (did you not use PY_setClassAttributeByNameOrCreate?)");
}

void PY_setClassAttributeByNameOrCreate(PyClassContainer* cls, char* name, PyObjectContainer* value)
{
    int i = 0;
    if (cls->static_attribute_names != NULL) {
        while (cls->static_attribute_names[i] != NULL) {
            if (strcmp(cls->static_attribute_names[i], name) == 0) {
                cls->static_attribute_values[i] = value;
                return;
            }
            i++;
        }
    }

    cls->static_attribute_names = realloc(cls->static_attribute_names, (i + 2) * sizeof(char*));
    if (cls->static_attribute_names == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    cls->static_attribute_values = realloc(cls->static_attribute_values, (i + 2) * sizeof(PyObjectContainer*));
    if (cls->static_attribute_values == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    cls->static_attribute_names[i] = strdup(name);  // create a copy for us
    cls->static_attribute_values[i] = value;
    cls->static_attribute_names[i+1] = NULL;
    cls->static_attribute_values[i+1] = NULL;
}

PyObjectContainer* PY_invokeBoxedMethod(PyObjectContainer* obj, PyObjectContainer* self, uint8_t param_count, PyObjectContainer** args)
{
    assert(obj != NULL);
    assert(obj->type == PY_TYPE_FUNC_POINTER);

    PY_FUNC_UNBOXED* function = (PY_FUNC_UNBOXED*)obj->raw_value;

    if (self == NULL && (obj->flags & PY_TYPE_FUNC_HAS_SELF))
    {
        self = obj->source;
    }

    return function(self, param_count, args);
}

PyObjectContainer* PY_GetSubscriptionValue(PyObjectContainer* obj, PyObjectContainer* index)
{
    assert(obj->type == PY_TYPE_PY_IMPL);

    PyObjectContainer* method = PY_getObjectAttributeByNameOrStatic(obj, "__getitem__");
    assert(method != NULL);

    return PY_invokeBoxedMethod(method, NULL, 1, &index);
}

void PY_SetSubscriptionValue(PyObjectContainer* obj, PyObjectContainer* index, PyObjectContainer* value)
{
    assert(obj->type == PY_TYPE_PY_IMPL);

    PyObjectContainer* method = PY_getObjectAttributeByNameOrStatic(obj, "__setitem__");
    assert(method != NULL);

    PyObjectContainer* mem[2];
    mem[0] = index;
    mem[1] = value;

    PY_invokeBoxedMethod(method, NULL, 2, mem);
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

static bool PY_getTruthValueOfPyObj(PyObjectContainer* obj)
{
    PyObjectContainer* bool_method = PY_getObjectAttributeByNameOrStatic(obj, "__bool__");

    if (bool_method != NULL)
    {
        PyObjectContainer* result = PY_invokeBoxedMethod(bool_method, NULL, 0, NULL);
        return PY_getTruthValueOf(result);
    }

    return true;
}

bool PY_getTruthValueOf(PyObjectContainer* obj)
{
    switch (obj->type)
    {
        case PY_TYPE_BOOL:
            return (bool)obj->raw_value;
        case PY_TYPE_NONE:
            return false;
        case PY_TYPE_INT:
            return PY_unpackInteger(obj) != 0;
        case PY_TYPE_FLOAT:
            // TODO
            return false;
        case PY_TYPE_FUNC_POINTER:
            return true;
        case PY_TYPE_PY_IMPL:
            return PY_getTruthValueOfPyObj(obj);
    }
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

