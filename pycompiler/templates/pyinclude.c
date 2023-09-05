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

PyObjectContainer* PY_builtin_int_compare_container;

PyClassContainer* PY_TYPE_OBJECT;

PyObjectContainer* createEmptyContainer(PyObjectType type)
{
    PyObjectContainer* container = malloc(sizeof(PyObjectContainer));

    if (container == NULL)
    {
        perror("malloc createEmptyContainer");
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
        perror("malloc PY_createClassContainer");
        exit(EXIT_FAILURE);
    }

    container->parents = NULL;
    container->class_name = name;
    container->attr_count = 0;
    container->attr_name_array = NULL;
    container->static_attribute_names = NULL;
    container->static_attribute_values = NULL;
    container->flags = 0;

    return container;
}

void PY_ClassContainer_AllocateParentArray(PyClassContainer* cls, uint8_t count)
{
    assert(cls->parents == NULL);

    cls->parents = calloc(count + 1, sizeof(PyClassContainer*));

    if (cls->parents == NULL)
    {
        perror("malloc PY_ClassContainer_AllocateParentArray");
        exit(EXIT_FAILURE);
    }
}

bool PY_isSubclassOf(PyClassContainer* cls, PyClassContainer* parent)
{
    if (cls->parents == NULL)
    {
        return false;
    }

    int i = 0;
    while (cls->parents[i] != NULL)
    {
        if (cls->parents[i] == parent)
        {
            return true;
        }

        if (PY_isSubclassOf(cls->parents[i], parent))
        {
            return true;
        }
    }
    return false;
}

bool PY_isInstanceOf(PyObjectContainer* obj, PyClassContainer* cls)
{
    assert(obj->type == PY_TYPE_PY_IMPL);

    return PY_isSubclassOf(obj->py_type, cls);
}

PyObjectContainer* PY_createClassInstance(PyClassContainer* cls)
{
    assert(cls != NULL);
    PyObjectContainer* obj = createEmptyContainer(PY_TYPE_PY_IMPL);
    obj->py_type = cls;

    if (cls->attr_count != 0)
    {
        obj->attr_array = calloc(cls->attr_count, sizeof(PyObjectContainer *));

        if (obj->attr_array == NULL) {
            perror("malloc PY_createClassInstance");
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

static PyObjectContainer* PY_getObjectAttributeByNameOrStatic_primitive(PyObjectContainer* obj, char* name)
{
    if (obj->type == PY_TYPE_INT)
    {
        if (strcmp(name, "__eq__") == 0)
        {
            return PY_builtin_int_compare_container;
        }
    }

    assert(false == "no special attribute found!");
}

PyObjectContainer* PY_getObjectAttributeByNameOrStatic(PyObjectContainer* obj, char* name)
{
    if (obj->type != PY_TYPE_PY_IMPL)
    {
        return PY_getObjectAttributeByNameOrStatic_StaticTransformer(obj, PY_getObjectAttributeByNameOrStatic_primitive(obj, name));
    }

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
        perror("malloc PY_setClassAttributeByNameOrCreate A");
        exit(EXIT_FAILURE);
    }

    cls->static_attribute_values = realloc(cls->static_attribute_values, (i + 2) * sizeof(PyObjectContainer*));
    if (cls->static_attribute_values == NULL)
    {
        perror("malloc PY_setClassAttributeByNameOrCreate B");
        exit(EXIT_FAILURE);
    }

    cls->static_attribute_names[i] = strdup(name);  // create a copy for us
    cls->static_attribute_values[i] = value;
    cls->static_attribute_names[i+1] = NULL;
    cls->static_attribute_values[i+1] = NULL;
}

PyObjectContainer* PY_invokeBoxedMethod(PyObjectContainer* method, PyObjectContainer* self, uint8_t param_count, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(method != NULL);

    bool decref_after = false;

    if (method->type == PY_TYPE_PY_IMPL) {
        method = PY_getObjectAttributeByNameOrStatic(method, "__call__");

        while (method->type == PY_TYPE_PY_IMPL) {
            PyObjectContainer* new_obj = PY_getObjectAttributeByNameOrStatic(method, "__call__");
            DECREF(method);
            method = new_obj;
            assert(method != NULL);
        }

        decref_after = true;
    }

    assert(method->type == PY_TYPE_FUNC_POINTER);

    PY_FUNC_UNBOXED* function = (PY_FUNC_UNBOXED*)method->raw_value;

    if (self == NULL && (method->flags & PY_TYPE_FUNC_HAS_SELF))
    {
        self = method->source;
    }

    PyObjectContainer* result = function(self, param_count, args, info);

    if (decref_after)
    {
        DECREF(method);
    }

    return result;
}

PyObjectContainer* PY_GetSubscriptionValue(PyObjectContainer* obj, PyObjectContainer* index)
{
    assert(obj->type == PY_TYPE_PY_IMPL);

    PyObjectContainer* method = PY_getObjectAttributeByNameOrStatic(obj, "__getitem__");
    assert(method != NULL);

    return PY_invokeBoxedMethod(method, NULL, 1, &index, NULL);
}

void PY_SetSubscriptionValue(PyObjectContainer* obj, PyObjectContainer* index, PyObjectContainer* value)
{
    assert(obj->type == PY_TYPE_PY_IMPL);

    PyObjectContainer* method = PY_getObjectAttributeByNameOrStatic(obj, "__setitem__");
    assert(method != NULL);

    PyObjectContainer* mem[2];
    mem[0] = index;
    mem[1] = value;

    PY_invokeBoxedMethod(method, NULL, 2, mem, NULL);
}

PyObjectContainer* PY_createString(char* string)
{
    PyObjectContainer* container = createEmptyContainer(PY_TYPE_STRING);
    container->raw_value = string;
    return container;
}

char* PY_unpackString(PyObjectContainer* obj)
{
    assert(obj->type == PY_TYPE_STRING);
    return obj->raw_value;
}

PyObjectContainer* PY_createInteger(int64_t value)
{
    uint64_t* value_holder = malloc(sizeof(uint64_t));

    if (value_holder == NULL)
    {
        perror("malloc PY_createInteger");
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

PyObjectContainer* PY_createFloat(double value)
{
    double* value_holder = malloc(sizeof(double));

    if (value_holder == NULL)
    {
        perror("malloc PY_createFloat");
        exit(EXIT_FAILURE);
    }

    *value_holder = value;
    PyObjectContainer* container = createEmptyContainer(PY_TYPE_FLOAT);
    container->raw_value = value_holder;
    return container;
}

double PY_unpackFloat(PyObjectContainer* obj)
{
    assert(obj->type == PY_TYPE_FLOAT);

    return *((double*)obj->raw_value);
}

PyObjectContainer* PY_createBoolean(bool value)
{
    if (value)
    {
        return PY_TRUE;
    }
    return PY_FALSE;
}

bool PY_unpackBoolean(PyObjectContainer* obj)
{
    assert(obj->type == PY_TYPE_BOOL);
    if (obj == PY_TRUE)
    {
        return true;
    }
    return false;
}


static bool PY_getTruthValueOfPyObj(PyObjectContainer* obj)
{
    PyObjectContainer* bool_method = PY_getObjectAttributeByNameOrStatic(obj, "__bool__");

    if (bool_method != NULL)
    {
        PyObjectContainer* result = PY_invokeBoxedMethod(bool_method, NULL, 0, NULL, NULL);
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

    return false;
}

int8_t PY_getArgumentFlags(CallStructureInfo* info, uint8_t index)
{
    assert(info != NULL);
    if (index < info->offset)
    {
        return -1;
    }

    index -= info->offset;

    uint8_t page_index = index >> 4;
    uint64_t page = info->bitmask[page_index];
    uint8_t offset = index & 15;
    uint8_t section = (page >> (2 * offset)) & 3;
    return (int8_t)section;
}

PyObjectContainer* PY_ARGUMENT_getKeywordArgumentOrNull(uint8_t argc, PyObjectContainer** args, CallStructureInfo* info, char* name)
{
    if (info == NULL)
    {
        return NULL;
    }

    for (int i = info->offset; i < argc; i++)
    {
        int8_t flag = PY_getArgumentFlags(info, i);

        if (flag == CALL_STRUCTURE_KEYWORD)
        {
            char* key = (char*)info->data[i - info->offset];

            if (strcmp(key, name) == 0)
            {
                return args[i];
            }
        }
    }

    return NULL;
}

PyObjectContainer* PY_ARGUMENT_getKeywordArgumentOrDefault(uint8_t argc, PyObjectContainer** args, CallStructureInfo* info, char* name, PyObjectContainer* default_value)
{
    if (info == NULL)
    {
        return default_value;
    }

    for (int i = info->offset; i < argc; i++)
    {
        int8_t flag = PY_getArgumentFlags(info, i);

        if (flag == CALL_STRUCTURE_KEYWORD)
        {
            char* key = (char*)info->data[i - info->offset];

            if (strcmp(key, name) == 0)
            {
                return args[i];
            }
        }
    }

    return default_value;
}

void initialize()
{
    if (initialized) return;

    PY_NONE = createEmptyContainer(PY_TYPE_NONE);
    PY_FALSE = createEmptyContainer(PY_TYPE_BOOL);
    PY_FALSE->raw_value = (void*)0;
    PY_TRUE = createEmptyContainer(PY_TYPE_BOOL);
    PY_TRUE->raw_value = (void*)1;

    PY_TYPE_OBJECT = PY_createClassContainer("object");

    initialized = true;
}

