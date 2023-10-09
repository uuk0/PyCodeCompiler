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
#include <math.h>
#include <inttypes.h>


static bool initialized = false;

PyObjectContainer* PY_NONE;
PyObjectContainer* PY_FALSE;
PyObjectContainer* PY_TRUE;
PyObjectContainer* PY_NOT_IMPLEMENTED;

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

void PY_ClassContainer_DeclareObjectAttribute(PyClassContainer* cls, char* name) {
    for (int i = 0; i < cls->attr_count; i++) {
        if (strcmp(cls->attr_name_array[i], name) == 0) {
            return;
        }
    }

    cls->attr_count++;
    cls->attr_name_array = realloc(cls->attr_name_array, cls->attr_count * sizeof(char*));
    if (cls->attr_name_array == NULL)
    {
        perror("realloc PY_ClassContainer_DeclareObjectAttribute");
        exit(EXIT_FAILURE);
    }
    cls->attr_name_array[cls->attr_count-1] = name;
}

void PY_ClassContainer_EnsureObjectAttributesDeclaredFor(PyClassContainer* cls, PyClassContainer* parent) {
    for (int i = 0; i < parent->attr_count; i++) {
        PY_ClassContainer_DeclareObjectAttribute(cls, parent->attr_name_array[i]);
    }
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

PyObjectContainer* PY_createClass(char* name, PyObjectContainer* init(PyClassContainer**)) {
    PyClassContainer* cls = PY_createClassContainer(name);
    PY_CHECK_EXCEPTION(init(&cls));
    return PY_createClassWrapper(cls);
}

// todo: do a better check!
bool PY_hasObjectAttribute(PyObjectContainer* obj, char* name) {
    PyObjectContainer* value = PY_getObjectAttributeByNameOrStatic(obj, name);
    return value == NULL ? PY_FALSE : PY_TRUE;
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
    if (attr == NULL)
    {
        return NULL;
    }

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
    }
    if (obj->type == PY_TYPE_FLOAT)
    {
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
        if (strcmp(name, "__iter__") == 0)
        {
            return PY_STD_string_iter_CONTAINER;
        }
        if (strcmp(name, "startswith") == 0)
        {
            return PY_STD_string_startswith_CONTAINER;
        }
    }
    else if (obj->type == PY_TYPE_PY_TYPE)
    {
        PyObjectContainer* result;
        if (strcmp(name, "__getitem__") == 0)
        {
            result = PY_getClassAttributeByName(PY_unwrapClassContainer(obj), "__class_getitem__");
        }
        else
        {
            result = PY_getClassAttributeByName(PY_unwrapClassContainer(obj), name);
        }

        if (result)
        {
            return result;
        }
    }
    else if (obj->type == PY_EXCEPTION)
    {
        return obj;  // rethrow the exception
    }

    printf("Type: %s, Attr: %s\n", PY_getObjectClassName(obj), name);
    return NULL;
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

    if (cls->parents != NULL)
    {
        i = 0;
        while (cls->parents[i] != NULL)
        {
            PyObjectContainer* value = PY_getObjectAttributeByNameOrStatic_StaticTransformer(obj, PY_getClassAttributeByName(cls->parents[i], name));
            if (value != NULL)
            {
                return value;
            }
            i++;
        }
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

char* PY_getObjectClassName(PyObjectContainer* obj) {
    assert(obj != 0);

    switch (obj->type) {
        case PY_TYPE_PY_IMPL:
            return obj->py_type->class_name;
        case PY_TYPE_NONE:
            return "NoneType";
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

    printf("data type id: %i; refcount: %i\n", obj->type, obj->refcount);
    assert(0 && "should not be reachable; invalid 'type' (maybe you passed uninitialized memory?)");
}

char* PY_getObjectRepr(PyObjectContainer* obj)
{
    if (obj == NULL) return "C_NULL";

    if (obj->type == PY_TYPE_PY_IMPL)
    {
        PyObjectContainer* method = PY_getObjectAttributeByNameOrStatic(obj, "__repr__");
        if (method == NULL)
        {
            char* class_name = PY_getObjectClassName(obj);
            size_t size = strlen(class_name) + strlen("<-object at 0x0000020CB8576980>");
            char* buffer = malloc(size+1);
            if (buffer == NULL)
            {
                perror("malloc repr wrapper");
                exit(EXIT_FAILURE);
            }
            snprintf(buffer, size+1, "<%s-object at %#018" PRIu64 ">", class_name, (uintptr_t)obj);
            return buffer;
        }
        char* result = PY_unpackString(PY_CHECK_EXCEPTION_AND_EXIT(PY_invokeBoxedMethod(method, obj, 0, NULL, NULL)));
        assert(*result != '\0');
        return result;
    }

    switch (obj->type) {
        case PY_TYPE_NONE:
            return "None";
        case PY_TYPE_BOOL:
            if (obj == PY_TRUE)
            {
                return "True";
            }
            return "False";
        case PY_TYPE_INT:
        {
            size_t size = (int) ((ceil(log10((double)UINT64_MAX)) + 1 + 1) * sizeof(char));
            char *buffer = malloc(size);
            snprintf(buffer, size, "%" PRId64, *(int64_t*)obj->raw_value);
            return buffer;
        }
        case PY_TYPE_STRING:
        {
            // todo: escape " chars in text!
            char *buffer = malloc(strlen(obj->raw_value) + 2);
            buffer[0] = '\"';
            buffer[1] = '\0';
            strcat(buffer, obj->raw_value);
            strcat(buffer, "\"");
            return buffer;
        }
        case PY_TYPE_FLOAT:
        {
            // todo: whats the real size?
            size_t size = 64;
            char *buffer = malloc(size);
            snprintf(buffer, size, "%f", *(double*)obj->raw_value);
            return buffer;
        }
        case PY_TYPE_PY_TYPE:
        {
            PyClassContainer* cls = PY_unwrapClassContainer(obj);
            char* class_name = cls->class_name;
            size_t size = strlen(class_name) + strlen("<-type-object at 0x0000020CB8576980>");
            char* buffer = malloc(size+1);
            if (buffer == NULL)
            {
                perror("malloc repr wrapper");
                exit(EXIT_FAILURE);
            }
            snprintf(buffer, size, "<%s-type-object at %#018" PRIu64 ">", class_name, (uintptr_t)obj);
            return buffer;
        }
        case PY_TYPE_FUNC_POINTER:
        {
            size_t size = strlen("<function pointer at 0x0000020CB8576980>");
            char *buffer = malloc(size + 1);
            if (buffer == NULL) {
                perror("malloc repr wrapper");
                exit(EXIT_FAILURE);
            }
            snprintf(buffer, size, "<function pointer at %#018" PRIu64 ">", (uintptr_t) obj);
            return buffer;
            return "<function pointer to>";
        }
        case PY_EXCEPTION:
        {
            if (obj->raw_value != NULL)
            {
                // This is an (PYTHON) Exception object -> that repr is our one!
                return PY_getObjectRepr(obj->raw_value);
            }

            size_t size = strlen("<exception at 0x0000020CB8576980>");
            char* buffer = malloc(size+1);
            if (buffer == NULL)
            {
                perror("malloc repr wrapper");
                exit(EXIT_FAILURE);
            }
            snprintf(buffer, size, "<exception at %#018" PRIu64 ">", (uintptr_t)obj);
            return buffer;
        }
    }
    assert(0);
}

PyObjectContainer* PY_getObjectRepr_wrapper(PyObjectContainer* obj)
{
    return PY_createString(PY_getObjectRepr(obj));
}

PyObjectContainer* PY_getObjectStr_wrapper(PyObjectContainer* obj)
{
    PyObjectContainer* method = PY_getObjectAttributeByNameOrStatic(obj, "__str__");

    if (method == NULL)
    {
        return PY_createString(PY_getObjectRepr(obj));
    }
    return PY_invokeBoxedMethod(method, obj, 0, NULL, NULL);
}

PyObjectContainer* PY_STD_id(PyObjectContainer* obj) {
    return PY_createInteger(*(int64_t*)&obj);
}

PyObjectContainer* PY_invokeBoxedMethod(PyObjectContainer* method, PyObjectContainer* self, uint8_t param_count, PyObjectContainer** args, CallStructureInfo* info)
{
    if (method == NULL)
    {
        fprintf(stderr, "FAULT: method is NULL\n");
        fprintf(stderr, "self is %s, args: %i\n", PY_getObjectRepr(self), param_count);
        fflush(stdout);
        fflush(stderr);
        PyObjectContainer** x = NULL;
        self = (PyObjectContainer*)*x;
    }
    PY_THROW_EXCEPTION_IF_WITH_MESSAGE(method == NULL, NULL, "method MUST be != NULL");

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

    if (method->type == PY_TYPE_PY_TYPE) {
        PyClassContainer* cls = PY_unwrapClassContainer(method);
        PyObjectContainer* obj = PY_createClassInstance(cls);
        PyObjectContainer* init = PY_getObjectAttributeByNameOrStatic(obj, "__init__");
        PY_invokeBoxedMethod(init, obj, param_count, args, info);
        return obj;
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
    container->raw_value = strdup(string);
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
    assert(obj != NULL);
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
    assert(obj != NULL);
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
    assert(obj != NULL);
    assert(obj->type == PY_TYPE_BOOL);

    if (obj == PY_TRUE)
    {
        return true;
    }
    return false;
}


bool PY_getTruthValueOf(PyObjectContainer* obj) {
    head:;

    if (obj == NULL) {
        fprintf(stderr, "WARN: tried to get truth value of C_NULL\n");
        return false;
    }

    switch (obj->type)
    {
        case PY_TYPE_BOOL:
            return (bool)obj->raw_value;
        case PY_TYPE_NONE:
            return false;
        case PY_TYPE_INT:
            return PY_unpackInteger(obj) != 0;
        case PY_TYPE_FLOAT:
            return PY_unpackFloat(obj) != 0;
        case PY_TYPE_FUNC_POINTER:
            return true;
        case PY_EXCEPTION:
            assert(0 && "tried to check exception for truth value; aborting");
        case PY_TYPE_PY_IMPL: {
            PyObjectContainer* bool_method = PY_getObjectAttributeByNameOrStatic(obj, "__bool__");

            if (bool_method != NULL)
            {
                obj = PY_invokeBoxedMethod(bool_method, NULL, 0, NULL, NULL);
                goto head;  // check the result again
            }

            return true;
        }
        case PY_TYPE_STRING:
            return strlen(obj->raw_value) > 0;
        case PY_TYPE_PY_TYPE:
            return PY_TRUE;
        case PY_TYPE_SPECIAL:
            assert(0 && "BOOL() on SPECIAL is not allowed");
    }

    return false;
}

PyObjectContainer* PY_getTruthValueOf_BOXED(PyObjectContainer* obj) {
    return PY_createBoolean(PY_getTruthValueOf(obj));
}

PyObjectContainer* PY_toInt(PyObjectContainer* obj) {
    switch (obj->type) {
        case PY_TYPE_INT:
        case PY_EXCEPTION:
            return obj;
        case PY_TYPE_FLOAT:
            return PY_createInteger((int64_t)PY_unpackFloat(obj));
        case PY_TYPE_FUNC_POINTER:
        case PY_TYPE_STRING:
        case PY_TYPE_SPECIAL:
        case PY_TYPE_NONE:
        case PY_TYPE_PY_TYPE:
            PY_THROW_EXCEPTION(NULL);
        case PY_TYPE_PY_IMPL: {
            PyObjectContainer* method = PY_getObjectAttributeByNameOrStatic(obj, "__index__");
            PY_THROW_EXCEPTION_IF(method == NULL, NULL);
            return PY_invokeBoxedMethod(method, obj, 0, NULL, NULL);
        }
        case PY_TYPE_BOOL:
            return obj == PY_FALSE ? PY_createInteger(0) : PY_createInteger(1);
    }
}

PyObjectContainer* PY_STD_hasattr(PyObjectContainer* obj, PyObjectContainer* attr) {
    assert(attr->type == PY_TYPE_STRING);
    return PY_createBoolean(PY_hasObjectAttribute(obj, PY_unpackString(attr)));
}

PyObjectContainer* PY_STD_getattr(PyObjectContainer* obj, PyObjectContainer* attr) {
    assert(attr->type == PY_TYPE_STRING);
    PyObjectContainer* value = PY_getObjectAttributeByNameOrStatic(obj, PY_unpackString(attr));
    PY_THROW_EXCEPTION_IF(value == NULL, NULL);
    return value;
}

PyObjectContainer* PY_STD_getattr_with_default(PyObjectContainer* obj, PyObjectContainer* attr, PyObjectContainer* default_value) {
    assert(attr->type == PY_TYPE_STRING);
    PyObjectContainer* value = PY_getObjectAttributeByNameOrStatic(obj, PY_unpackString(attr));
    return value ? value : default_value;
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

PyObjectContainer* PY_NOOP_CONTAINER;
PyObjectContainer* PY_NOOP(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info) {
    return PY_NONE;
}

void initialize()
{
    if (initialized) return;

    PY_NONE = createEmptyContainer(PY_TYPE_NONE);
    PY_NONE->flags |= PY_OBJ_NO_FREE;
    PY_FALSE = createEmptyContainer(PY_TYPE_BOOL);
    PY_FALSE->raw_value = (void*)0;
    PY_FALSE->flags |= PY_OBJ_NO_FREE;
    PY_TRUE = createEmptyContainer(PY_TYPE_BOOL);
    PY_TRUE->raw_value = (void*)1;
    PY_TRUE->flags |= PY_OBJ_NO_FREE;

    PY_TYPE_OBJECT = PY_createClassContainer("object");
    PY_setClassAttributeByNameOrCreate(PY_TYPE_OBJECT, "__init__", PY_createBoxForFunction(PY_NOOP));

    PY_NOT_IMPLEMENTED = PY_createClassInstance(PY_TYPE_OBJECT);
    PY_NOT_IMPLEMENTED->flags |= PY_OBJ_NO_FREE;

    PY_NOOP_CONTAINER = PY_createBoxForFunction(PY_NOOP);

    initialized = true;
}

void DECREF(PyObjectContainer* obj) {
    if (obj->flags & PY_OBJ_NO_FREE) return;

    obj->refcount--;
    if (obj->refcount > 0) return;

    switch(obj->type) {
        case PY_TYPE_PY_IMPL : {
            PyObjectContainer* method = PY_getObjectAttributeByNameOrStatic(obj, "__del__");
            if (method != NULL) {
                PY_invokeBoxedMethod(method, obj, 0, NULL, NULL);
                DECREF(method);
            }
            break;
        }
        case PY_TYPE_INT:
        case PY_TYPE_FLOAT:
        case PY_TYPE_STRING:
            free(obj->raw_value);
            break;
        default:
            break;
    }
    free(obj);
}

