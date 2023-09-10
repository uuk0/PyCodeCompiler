//
// Created by baulu on 05.09.2023.
//

#include <assert.h>
#include <stdarg.h>
#include <memory.h>
#include "dict.h"
#include "helpers/hashmap.h"
#include "operators.h"
#include "exceptions.h"
#include "config.h"
#include "tuple.h"

#ifdef PY_ENABLE_GENERATORS
#include "generator.h"
#endif

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
    PY_STD_dict_init_fast_arg_zero(dict);

    va_list ap;
    va_start(ap, argc * 2);
    for(int i = 0; i < argc; i++){
        PyObjectContainer* key = va_arg(ap, PyObjectContainer*);
        PyObjectContainer* value = va_arg(ap, PyObjectContainer*);
        PY_STD_dict_setitem_fast(dict, key, value);
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

PyObjectContainer* PY_STD_dict_len(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 0);
    return PY_STD_dict_len_fast(self);
}

PyObjectContainer* PY_STD_dict_len_fast(PyObjectContainer* self)
{
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_DICT);
    assert(self->raw_value != NULL);
    HashMapContainer* container = self->raw_value;
    return PY_createInteger((int64_t)container->used_size);
}

PyObjectContainer* PY_STD_dict_setdefault(PyObjectContainer* self,  uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 2);
    return PY_STD_dict_setdefault_fast(self, args[0], args[1]);
}

PyObjectContainer* PY_STD_dict_setdefault_fast(PyObjectContainer* self, PyObjectContainer* key, PyObjectContainer* default_value)
{
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_DICT);
    assert(self->raw_value != NULL);

    PyObjectContainer* value = HASHMAP_lookup(self->raw_value, key);

    if (value == NULL)
    {
        HASHMAP_insert(self->raw_value, key, default_value);
        return default_value;
    }

    return value;
}

PyObjectContainer* PY_STD_dict_clear(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 0);
    return PY_STD_dict_clear_fast(self);
}

PyObjectContainer* PY_STD_dict_clear_fast(PyObjectContainer* self)
{
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_DICT);
    assert(self->raw_value != NULL);

    HASHMAP_clear(self->raw_value);

    return PY_NONE;
}

PyObjectContainer* PY_STD_dict_copy(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 0);
    return PY_STD_dict_copy_fast(self);
}

PyObjectContainer* PY_STD_dict_copy_fast(PyObjectContainer* self)
{
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_DICT);
    assert(self->raw_value != NULL);

    HashMapContainer* container = self->raw_value;

    PyObjectContainer* copy = PY_createClassInstance(PY_TYPE_DICT);
    HashMapContainer* copy_container = HASHMAP_create_with_size(container->hash_method, container->compare_keys, container->alloc_size);
    copy->raw_value = copy_container;

    memcpy(copy_container->key_memory, container->key_memory, container->alloc_size * sizeof(void*));
    memcpy(copy_container->value_memory, container->value_memory, container->alloc_size * sizeof(void*));

    return copy;
}

#ifdef PY_ENABLE_GENERATORS
PyObjectContainer* PY_STD_dict_keys_iterator(PyGeneratorContainer* generator)
{
    PyObjectContainer* self = generator->locals[0];
    HashMapContainer* dict = self->raw_value;

    while (1)
    {
        if (generator->section_id >= dict->used_size)
        {
            return NULL;
        }

        PyObjectContainer* key = dict->key_memory[generator->section_id++];
        if (key == NULL || key == (PyObjectContainer*)&HASHMAP_MARKER_UNSET)
        {
            continue;
        }

        return key;
    }
}

PyObjectContainer* PY_STD_dict_keys(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 0);
    return PY_STD_dict_keys_fast(self);
}

PyObjectContainer* PY_STD_dict_keys_fast(PyObjectContainer* self)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_DICT);

    PyObjectContainer* generator = PY_STD_GENERATOR_create(1);
    PyGeneratorContainer* container = generator->raw_value;
    container->section_id = 0;
    container->locals[0] = self;
    container->next_section = PY_STD_dict_keys_iterator;
    return generator;
}

PyObjectContainer* PY_STD_dict_values_iterator(PyGeneratorContainer* generator)
{
    PyObjectContainer* self = generator->locals[0];
    HashMapContainer* dict = self->raw_value;

    while (1)
    {
        if (generator->section_id >= dict->used_size)
        {
            return NULL;
        }

        PyObjectContainer* key = dict->key_memory[generator->section_id++];
        if (key == NULL || key == (PyObjectContainer*)&HASHMAP_MARKER_UNSET)
        {
            continue;
        }

        PyObjectContainer* value = dict->value_memory[generator->section_id-1];
        return value;
    }
}

PyObjectContainer* PY_STD_dict_values(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 0);
    return PY_STD_dict_values_fast(self);
}

PyObjectContainer* PY_STD_dict_values_fast(PyObjectContainer* self)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_DICT);

    PyObjectContainer* generator = PY_STD_GENERATOR_create(1);
    PyGeneratorContainer* container = generator->raw_value;
    container->section_id = 0;
    container->locals[0] = self;
    container->next_section = PY_STD_dict_values_iterator;
    return generator;
}

PyObjectContainer* PY_STD_dict_items_iterator(PyGeneratorContainer* generator)
{
    PyObjectContainer* self = generator->locals[0];
    HashMapContainer* dict = self->raw_value;

    while (1)
    {
        if (generator->section_id >= dict->used_size)
        {
            return NULL;
        }

        PyObjectContainer* key = dict->key_memory[generator->section_id++];
        if (key == NULL || key == (PyObjectContainer*)&HASHMAP_MARKER_UNSET)
        {
            continue;
        }

        PyObjectContainer* value = dict->value_memory[generator->section_id-1];
        return PY_STD_tuple_CREATE(2, key, value);
    }
}

PyObjectContainer* PY_STD_dict_items(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 0);
    return PY_STD_dict_items_fast(self);
}

PyObjectContainer* PY_STD_dict_items_fast(PyObjectContainer* self)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_DICT);

    PyObjectContainer* generator = PY_STD_GENERATOR_create(1);
    PyGeneratorContainer* container = generator->raw_value;
    container->section_id = 0;
    container->locals[0] = self;
    container->next_section = PY_STD_dict_items_iterator;
    return generator;
}

#endif

void PY_STD_initDictType(void)
{
    PY_TYPE_DICT = PY_createClassContainer("dict");
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "get", PY_createBoxForFunction(PY_STD_dict_get));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "__init__", PY_createBoxForFunction(PY_STD_dict_init));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "__setitem__", PY_createBoxForFunction(PY_STD_dict_setitem));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "__getitem__", PY_createBoxForFunction(PY_STD_dict_getitem));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "__delitem__", PY_createBoxForFunction(PY_STD_dict_delitem));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "__contains__", PY_createBoxForFunction(PY_STD_dict_contains));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "__len__", PY_createBoxForFunction(PY_STD_dict_len));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "setdefault", PY_createBoxForFunction(PY_STD_dict_setdefault));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "clear", PY_createBoxForFunction(PY_STD_dict_clear));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "copy", PY_createBoxForFunction(PY_STD_dict_copy));

#ifdef PY_ENABLE_GENERATORS
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "__iter__", PY_createBoxForFunction(PY_STD_dict_keys));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "keys", PY_createBoxForFunction(PY_STD_dict_keys));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "values", PY_createBoxForFunction(PY_STD_dict_values));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "items", PY_createBoxForFunction(PY_STD_dict_items));
#endif
}

