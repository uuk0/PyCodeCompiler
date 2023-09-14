//
// Created by baulu on 31.07.2023.
//

#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include "pyinclude.h"
#include "standard_library/string.h"
#include "standard_library/exceptions.h"
#include <string.h>
#include <stdio.h>


static bool initialized = false;

PyObjectContainer* PY_NONE;
PyObjectContainer* PY_FALSE;
PyObjectContainer* PY_TRUE;

PyObjectContainer* PY_builtin_int_compare_container;
PyObjectContainer* PY_builtin_int_hash_container;

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
    container->dynamic_attr_count = 0;

#ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    container->dynamic_attr_keys = NULL;
    container->dynamic_attr_values = NULL;
#endif
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

void PY_ClassContainer_DeclareObjectAttribute(PyClassContainer* cls, char* name)
{
    cls->attr_count++;
    cls->attr_name_array = realloc(cls->attr_name_array, cls->attr_count * sizeof(char*));
    if (cls->attr_name_array == NULL)
    {
        perror("realloc PY_ClassContainer_DeclareObjectAttribute");
        exit(EXIT_FAILURE);
    }
    cls->attr_name_array[cls->attr_count-1] = name;
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

PyObjectContainer* PY_createClassWrapper(PyClassContainer* cls)
{
    PyObjectContainer* obj = createEmptyContainer(PY_TYPE_PY_TYPE);
    obj->raw_value = cls;
    return obj;
}

PyClassContainer* PY_unwrapClassContainer(PyObjectContainer* obj)
{
    assert(obj->type == PY_TYPE_PY_TYPE);
    return obj->raw_value;
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

#ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    for (int i = 0; i < obj->dynamic_attr_count; i++)
    {
        if (strcmp(obj->dynamic_attr_keys[i], name) == 0)
        {
            return obj->dynamic_attr_values[i];
        }
    }
#endif

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
        else if (strcmp(name, "__hash__") == 0)
        {
            return PY_builtin_int_hash_container;
        }
        printf("%s\n", name);
        PY_THROW_EXCEPTION_WITH_MESSAGE(NULL, "cannot get attribute on type <int>");
    }
    if (obj->type == PY_TYPE_FLOAT)
    {
        printf("%s\n", name);
        PY_THROW_EXCEPTION_WITH_MESSAGE(NULL, "cannot get attribute on type <float>");
    }
    else if (obj->type == PY_TYPE_STRING)
    {
        if (strcmp(name, "__hash__") == 0)
        {
            return PY_STD_string_hash_CONTAINER;
        }
        if (strcmp(name, "__eq__") == 0)
        {
            return PY_STD_string_eq_CONTAINER;
        }
        printf("%s\n", name);
        PY_THROW_EXCEPTION_WITH_MESSAGE(NULL, "cannot get attribute on type <string>");
    }
    else if (obj->type == PY_EXCEPTION)
    {
        return obj;  // rethrow the exception
    }

    printf("%s\n", name);
    PY_THROW_EXCEPTION(NULL);
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

#ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    for (int i = 0; i < obj->dynamic_attr_count; i++)
    {
        if (strcmp(obj->dynamic_attr_keys[i], name) == 0)
        {
            return obj->dynamic_attr_values[i];
        }
    }
#endif

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

#ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE

#ifndef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTES_FOR_ALL
    if (cls->flags & PY_CLASS_ALLOW_DYNAMIC_ATTRIBUTES)
#else
    if (1)
#endif
    {
        obj->dynamic_attr_count++;
        obj->dynamic_attr_keys = realloc(obj->dynamic_attr_keys, obj->dynamic_attr_count * sizeof(char*));
        if (obj->dynamic_attr_keys == NULL)
        {
            perror("PY_setObjectAttributeByName dynamic keys");
            exit(EXIT_FAILURE);
        }
        obj->dynamic_attr_values = realloc(obj->dynamic_attr_values, obj->dynamic_attr_count * sizeof(PyObjectContainer*));
        if (obj->dynamic_attr_values == NULL)
        {
            perror("PY_setObjectAttributeByName dynamic values");
            exit(EXIT_FAILURE);
        }
        obj->dynamic_attr_keys[obj->dynamic_attr_count-1] = name;
        obj->dynamic_attr_values[obj->dynamic_attr_count-1] = value;
        return;
    }
#endif

    assert(0 && "Attribute not found; Are you missing a declaration somewhere?");
}

PyObjectContainer* PY_getClassAttributeByName(PyClassContainer* cls, char* name)
{
    if (cls->static_attribute_names == NULL)
    {
        return NULL;
    }

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

    assert(0 && "Failed to set attribute; attribute does not exist (did you not use PY_setClassAttributeByNameOrCreate?)");
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
        perror("malloc PY_setClassAttributeByNameOrCreate names");
        exit(EXIT_FAILURE);
    }

    cls->static_attribute_values = realloc(cls->static_attribute_values, (i + 2) * sizeof(PyObjectContainer*));
    if (cls->static_attribute_values == NULL)
    {
        perror("malloc PY_setClassAttributeByNameOrCreate values");
        exit(EXIT_FAILURE);
    }

    cls->static_attribute_names[i] = strdup(name);  // create a copy for us
    cls->static_attribute_values[i] = value;
    cls->static_attribute_names[i+1] = NULL;
    cls->static_attribute_values[i+1] = NULL;
}

char* PY_getObjectClassName(PyObjectContainer* obj)
{

    switch (obj->type)
    {
        case PY_TYPE_PY_IMPL:
            return obj->py_type->class_name;
        case PY_TYPE_NONE:
            return "None";
        case PY_TYPE_BOOL:
            return "bool";
        case PY_TYPE_INT:
            return "int";
        case PY_TYPE_STRING:
            return "string";
        case PY_TYPE_FLOAT:
            return "float";
        case PY_TYPE_PY_TYPE:
            return "type";
        case PY_TYPE_FUNC_POINTER:
            return "<function pointer>";
        case PY_EXCEPTION:
            return "<exception>";
    }
    assert(0);
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
            if (method == NULL)
            {
                PY_THROW_EXCEPTION(NULL);
            }
        }

        decref_after = true;
    }

    if (method->type != PY_TYPE_FUNC_POINTER)
    {
        PY_THROW_EXCEPTION(NULL);
    }

    PY_FUNC_UNBOXED* function = (PY_FUNC_UNBOXED*)method->raw_value;

    if (self == NULL && (method->flags & PY_TYPE_FUNC_HAS_SELF))
    {
        self = method->source;
    }

    PyObjectContainer* result = function(self, param_count, args, info);
    PY_CHECK_EXCEPTION(result);

    if (decref_after)
    {
        DECREF(method);
    }

    return result;
}

PyObjectContainer* PY_GetSubscriptionValue(PyObjectContainer* obj, PyObjectContainer* index)
{
    // When using [] on a function, it is used for generics,
    // so we can skip this
    if (obj->type == PY_TYPE_FUNC_POINTER)
    {
        return obj;
    }

    assert(obj->type == PY_TYPE_PY_IMPL);

    PyObjectContainer* method = PY_getObjectAttributeByNameOrStatic(obj, "__getitem__");
    if (method == NULL)
    {
        PY_THROW_EXCEPTION(NULL);
    }

    return PY_invokeBoxedMethod(method, NULL, 1, &index, NULL);
}

PyObjectContainer* PY_SetSubscriptionValue(PyObjectContainer* obj, PyObjectContainer* index, PyObjectContainer* value)
{
    if (obj->type != PY_TYPE_PY_IMPL)
    {
        PY_THROW_EXCEPTION(NULL);
    }

    PyObjectContainer* method = PY_getObjectAttributeByNameOrStatic(obj, "__setitem__");
    if (method == NULL)
    {
        PY_THROW_EXCEPTION(NULL);
    }

    PyObjectContainer* mem[2];
    mem[0] = index;
    mem[1] = value;

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(method, NULL, 2, mem, NULL));
    return PY_NONE;
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
        case PY_EXCEPTION:
            assert(0 && "tried to check exception for truth value; aborting");
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

