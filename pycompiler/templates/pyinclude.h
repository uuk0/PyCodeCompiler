//
// Created by baulu on 31.07.2023.
//

#pragma once
#ifndef PYINCLUDE
#define PYINCLUDE

#include "standard_library/config.h"
#include "standard_library/parameters.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>


struct PyObjectContainer;
struct PyGeneratorContainer;
struct PyFunctionContext;

extern struct PyObjectContainer* PY_builtin_int_compare_container;
extern struct PyObjectContainer* PY_builtin_int_hash_container;


enum PyObjectType
{
    PY_TYPE_NONE,           // -                                             See: PY_NONE
    PY_TYPE_BOOL,           // 0 = False, 1 = True                           See: PY_TRUE, PY_FALSE
    PY_TYPE_INT,            // int64_t   todo: improve as python int has no limits
    PY_TYPE_STRING,         // char*     todo: make real class, so we can allow \0 chars in it!
    PY_TYPE_FLOAT,          // double precision
    PY_TYPE_PY_IMPL,        // a class implemented in python, the py_type field MUST be set
    PY_TYPE_PY_TYPE,        // a type reference to a PyClassContainer, raw_type is a PyClassContainer*
    PY_TYPE_FUNC_POINTER,   // a c function pointer (boxed)
    PY_EXCEPTION,           // an exception thrown; use PY_CHECK_EXCEPTION and related to auto-fwd the exception
    PY_TYPE_SPECIAL,        // used in a few cases where the type is secured by other means
};
typedef enum PyObjectType PyObjectType;


#define PY_CLASS_HAS_CUSTOM_GETATTR 1
#define PY_CLASS_IS_STD_IMPLEMENTED 2
#define PY_CLASS_ALLOW_DYNAMIC_ATTRIBUTES 4

struct PyClassContainer
{
    struct PyClassContainer** parents;

    char* class_name;

    char** attr_name_array;
    uint8_t attr_count;

    char** static_attribute_names;
    struct PyObjectContainer** static_attribute_values;

    uint16_t flags;
};
typedef struct PyClassContainer PyClassContainer;

// Compatible struct to PyObjectContainer, which can be used instead
// for smaller objects
struct ShortPyObjectContainer
{
    PyObjectType type;
    void* raw_value;
    uint16_t refcount;
    uint16_t flags;
};

#define PY_OBJ_NO_FREE 1

struct PyObjectContainer
{
    PyObjectType type;
    void* raw_value;
    uint16_t refcount;
    uint16_t flags;
    PyClassContainer* py_type;
    struct PyObjectContainer** attr_array;
    struct PyObjectContainer* source;

#ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    // TODO: make HASHMAP*
    uint16_t dynamic_attr_count;
    char** dynamic_attr_keys;
    struct PyObjectContainer** dynamic_attr_values;
#endif
};
typedef struct PyObjectContainer PyObjectContainer;


typedef PyObjectContainer* PY_FUNC_UNBOXED(PyObjectContainer* self, uint8_t param_count, PyObjectContainer** args, CallStructureInfo* info);
typedef PyObjectContainer* PY_FUNC_GENERATOR_ITEM(PyObjectContainer* value, PyObjectContainer** locals);


struct PyFunctionContext
{
    uint8_t local_count;
    char** local_names;
    PyObjectContainer** locals;
};


extern PyObjectContainer* PY_NONE;
extern PyObjectContainer* PY_FALSE;
extern PyObjectContainer* PY_TRUE;

extern PyClassContainer* PY_TYPE_OBJECT;


PyObjectContainer* createEmptyContainer(PyObjectType type);

PyClassContainer* PY_createClassContainer(char* name);
void PY_ClassContainer_AllocateParentArray(PyClassContainer* cls, uint8_t count);
bool PY_isSubclassOf(PyClassContainer* cls, PyClassContainer* parent);
bool PY_isInstanceOf(PyObjectContainer* obj, PyClassContainer* cls);
void PY_ClassContainer_DeclareObjectAttribute(PyClassContainer* cls, char* name);
void PY_ClassContainer_EnsureObjectAttributesDeclaredFor(PyClassContainer* cls, PyClassContainer* parent);

PyObjectContainer* PY_createClassInstance(PyClassContainer* cls);
PyObjectContainer* PY_createBoxForFunction(PY_FUNC_UNBOXED* func);
PyObjectContainer* PY_createClassWrapper(PyClassContainer* cls);
PyClassContainer* PY_unwrapClassContainer(PyObjectContainer* obj);
PyObjectContainer* PY_createClass(char* name, PyObjectContainer* init(PyClassContainer**));

PyObjectContainer* PY_getObjectAttributeByName(PyObjectContainer* obj, char* name);
PyObjectContainer* PY_getObjectAttributeByNameOrStatic(PyObjectContainer* obj, char* name);
void PY_setObjectAttributeByName(PyObjectContainer* obj, char* name, PyObjectContainer* value);
PyObjectContainer* PY_getClassAttributeByName(PyClassContainer* cls, char* name);
void PY_setClassAttributeByName(PyClassContainer* cls, char* name, PyObjectContainer* value);
void PY_setClassAttributeByNameOrCreate(PyClassContainer* cls, char* name, PyObjectContainer* value);
char* PY_getObjectClassName(PyObjectContainer* obj);
char* PY_getObjectRepr(PyObjectContainer* obj);
PyObjectContainer* PY_getObjectRepr_wrapper(PyObjectContainer* obj);
PyObjectContainer* PY_getObjectStr_wrapper(PyObjectContainer* obj);

PyObjectContainer* PY_invokeBoxedMethod(PyObjectContainer* method, PyObjectContainer* self, uint8_t param_count, PyObjectContainer** args, CallStructureInfo* info);

PyObjectContainer* PY_GetSubscriptionValue(PyObjectContainer* obj, PyObjectContainer* index);
PyObjectContainer* PY_SetSubscriptionValue(PyObjectContainer* obj, PyObjectContainer* index, PyObjectContainer* value);

// Primitive Data Objects

PyObjectContainer* PY_createString(char* string);
char* PY_unpackString(PyObjectContainer* obj);

PyObjectContainer* PY_createInteger(int64_t value);
int64_t PY_unpackInteger(PyObjectContainer* obj);

PyObjectContainer* PY_createFloat(double value);
double PY_unpackFloat(PyObjectContainer* obj);

PyObjectContainer* PY_createBoolean(bool value);
bool PY_unpackBoolean(PyObjectContainer* obj);

bool PY_getTruthValueOf(PyObjectContainer* obj);

void initialize();

#define INCREF(obj) obj->refcount++;
// #define DECREF(obj) obj->refcount--; if (obj->refcount == 0) free(obj);

void DECREF(PyObjectContainer* obj);

/**
#define DECREF(obj) obj->refcount--; if (obj->refcount == 0) { \
PyObjectContainer* method = PY_getObjectAttributeByNameOrStatic(obj, "__del__"); \
if (method != NULL)                                            \
{                                                              \
    PY_invokeBoxedMethod(method, obj, 0, NULL, NULL);          \
}                                                              \
free(obj);                                                     \
};
 * **/

PyObjectContainer* PY_NOOP(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);

#endif

