//
// Created by baulu on 05.09.2023.
//

#include <assert.h>
#include <stdarg.h>
#include "dict.h"
#include "helpers/hashmap.h"
#include "operators.h"
#include "exceptions.h"

PyClassContainer* PY_TYPE_DICT;

int64_t HASH_py_object(void* raw_obj)
{
    PyObjectContainer* obj = raw_obj;
    PyObjectContainer* hash_method = PY_getObjectAttributeByNameOrStatic(obj, "__hash__");

    if (hash_method != NULL)
    {
        return PY_unpackInteger(PY_invokeBoxedMethod(hash_method, obj, 0, NULL, NULL));
    }

    // Cast the object pointer to an int, so it can be used as a hash
    // Uses a cast to an int64_t* to circumvent the narrowcast
    return *((int64_t*)&obj);
}

bool HASH_compare_py_object(void* lhs, void* rhs)
{
    return PY_unpackBoolean(PY_STD_operator_equals(lhs, rhs));
}

PyObjectContainer* PY_STD_dict_CREATE(uint8_t argc, ...)
{
    PyObjectContainer* dict = PY_createClassInstance(PY_TYPE_DICT);

    va_list ap;
    va_start(ap, argc * 2);
    for(int i = 0; i < argc; i++){
        PY_STD_dict_setitem_fast(dict, va_arg(ap, PyObjectContainer*), va_arg(ap, PyObjectContainer*));
    }
    va_end(ap);

    return dict;
}

PyObjectContainer* PY_STD_dict_init(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    self->raw_value = HASHMAP_create(HASH_py_object, HASH_compare_py_object);
    return PY_NONE;
}

PyObjectContainer* PY_STD_dict_init_fast_arg_zero(PyObjectContainer* self)
{
    self->raw_value = HASHMAP_create(HASH_py_object, HASH_compare_py_object);
    return PY_NONE;
}

PyObjectContainer* PY_STD_dict_get(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    if (argc == 1)
    {
        return PY_STD_dict_getitem_fast(self, args[0]);
    }
    else if (argc == 2)
    {
        return PY_STD_dict_get_fast_arg_2(self, args[0], args[1]);
    }

    PY_THROW_EXCEPTION_WITH_MESSAGE(NULL, "expected 1 or 2 arguments");
}

PyObjectContainer* PY_STD_dict_get_fast_arg_2(PyObjectContainer* self, PyObjectContainer* key, PyObjectContainer* default_value)
{
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_DICT);
    assert(self->raw_value != NULL);
    assert(key != NULL);
    assert(default_value != NULL);
    PY_CHECK_EXCEPTION(key);
    PY_CHECK_EXCEPTION(default_value);

    PyObjectContainer* obj = HASHMAP_lookup(self->raw_value, key);
    if (obj == NULL)
    {
        return default_value;
    }
    return obj;
}

PyObjectContainer* PY_STD_dict_setitem(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 2);
    return PY_STD_dict_setitem_fast(self, args[0], args[1]);
}

PyObjectContainer* PY_STD_dict_setitem_fast(PyObjectContainer* self, PyObjectContainer* key, PyObjectContainer* value)
{
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_DICT);
    assert(self->raw_value != NULL);
    assert(key != NULL);

    HASHMAP_insert(self->raw_value, key, value);

    return PY_NONE;
}

PyObjectContainer* PY_STD_dict_getitem(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 1);
    return PY_STD_dict_getitem_fast(self, args[0]);
}

PyObjectContainer* PY_STD_dict_getitem_fast(PyObjectContainer* self, PyObjectContainer* key)
{
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_DICT);
    assert(self->raw_value != NULL);
    assert(key != NULL);

    PyObjectContainer* obj = HASHMAP_lookup(self->raw_value, key);
    if (obj == NULL)
    {
        PY_THROW_EXCEPTION_WITH_MESSAGE(NULL, "key not found");
    }
    return obj;
}

PyObjectContainer* PY_STD_dict_delitem(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 1);
    return PY_STD_dict_delitem_fast(self, args[0]);
}

PyObjectContainer* PY_STD_dict_delitem_fast(PyObjectContainer* self, PyObjectContainer* key)
{
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_DICT);
    assert(self->raw_value != NULL);

    if (HASHMAP_remove(self->raw_value, key) == NULL)
    {
        PY_THROW_EXCEPTION_WITH_MESSAGE(NULL, "key not in dict");
    }

    return PY_NONE;
}

PyObjectContainer* PY_STD_dict_contains(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 1);
    return PY_STD_dict_contains_fast(self, args[0]);
}

PyObjectContainer* PY_STD_dict_contains_fast(PyObjectContainer* self, PyObjectContainer* key)
{
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_DICT);
    assert(self->raw_value != NULL);

    return HASHMAP_has_key(self->raw_value, key) ? PY_TRUE : PY_FALSE;
}

void PY_STD_initDictType(void)
{
    PY_TYPE_DICT = PY_createClassContainer("dict");
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "get", PY_createBoxForFunction(PY_STD_dict_get));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "__init__", PY_createBoxForFunction(PY_STD_dict_init));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "__setitem__", PY_createBoxForFunction(PY_STD_dict_setitem));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "__getitem__", PY_createBoxForFunction(PY_STD_dict_getitem));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "__delitem__", PY_createBoxForFunction(PY_STD_dict_delitem));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "__contains__", PY_createBoxForFunction(PY_STD_dict_contains));
}

