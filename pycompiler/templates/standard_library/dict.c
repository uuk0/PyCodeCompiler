//
// Created by baulu on 05.09.2023.
//

#include <assert.h>
#include <stdarg.h>
#include <memory.h>
#include <string.h>
#include "dict.h"
#include "helpers/hashmap.h"
#include "operators.h"
#include "exceptions.h"
#include "config.h"
#include "tuple.h"
#include "list.h"

#ifdef PY_ENABLE_GENERATORS
#include "generator.h"
#endif

PyClassContainer* PY_TYPE_DICT;

int64_t HASH_py_object(void* raw_obj)
{
    PyObjectContainer* obj = raw_obj;
    assert(obj != NULL && "tried to hash NULL, which is impossible");
    PyObjectContainer* hash_method = PY_getObjectAttributeByNameOrStatic(obj, "__hash__");
    if (hash_method != NULL)
    {
        int64_t result = PY_unpackInteger(PY_invokeBoxedMethod(hash_method, obj, 0, NULL, NULL));
        DECREF(hash_method);
        return result;
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
    va_start(ap, argc);
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

PyObjectContainer* PY_STD_dict_fromkeys(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info) {
    if (argc == 1)
    {
        return PY_STD_dict_fromkeys_fast_arg_2(self, args[0], PY_NONE);
    }
    else if (argc == 2)
    {
        return PY_STD_dict_fromkeys_fast_arg_2(self, args[0], args[1]);
    }

    PY_THROW_EXCEPTION_WITH_MESSAGE(NULL, "expected 1 or 2 arguments");
}

PyObjectContainer* PY_STD_dict_fromkeys_fast_arg_1(PyObjectContainer* self, PyObjectContainer* key) {
    return PY_STD_dict_fromkeys_fast_arg_2(self, key, PY_NONE);
}

PyObjectContainer* PY_STD_dict_fromkeys_fast_arg_2(PyObjectContainer* self, PyObjectContainer* keys, PyObjectContainer* default_value) {
    assert(keys != NULL);
    assert(default_value != NULL);

    PyObjectContainer* key_list = PY_createClassInstance(PY_TYPE_LIST);
    PY_STD_list_init_fast_arg_1(key_list, keys);
    PY_STD_list_container* list = key_list->raw_value;

    PyObjectContainer* dict = PY_STD_dict_CREATE(0);

    for (int i = 0; i < list->curr_size; i++) {
        HASHMAP_insert(dict->raw_value, list->array[i], default_value);
    }

    return dict;
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

    PyObjectContainer* obj = HASHMAP_lookup(self->raw_value, key);
    if (obj == NULL)
    {
        return default_value;
    }
    return obj;
}

PyObjectContainer* PY_STD_dict_pop(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info) {
    if (argc == 1)
    {
        return PY_STD_dict_pop_fast_arg_1(self, args[0]);
    }
    else if (argc == 2)
    {
        return PY_STD_dict_pop_fast_arg_2(self, args[0], args[1]);
    }

    PY_THROW_EXCEPTION_WITH_MESSAGE(NULL, "expected 1 or 2 arguments");
}

PyObjectContainer* PY_STD_dict_pop_fast_arg_1(PyObjectContainer* self, PyObjectContainer* key) {
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_DICT);
    assert(self->raw_value != NULL);
    assert(key != NULL);

    // todo: can be find the index beforehand and reuse it for del-ing?
    PyObjectContainer* obj = HASHMAP_lookup(self->raw_value, key);
    if (obj == NULL) {
        PY_THROW_EXCEPTION(NULL);  // todo: KeyError
    }
    HASHMAP_remove(self->raw_value, key);
    return obj;
}

PyObjectContainer* PY_STD_dict_pop_fast_arg_2(PyObjectContainer* self, PyObjectContainer* key, PyObjectContainer* default_value) {
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_DICT);
    assert(self->raw_value != NULL);
    assert(key != NULL);
    assert(default_value != NULL);

    // todo: can be find the index beforehand and reuse it for del-ing?
    PyObjectContainer* obj = HASHMAP_lookup(self->raw_value, key);
    if (obj == NULL) {
        return default_value;
    }
    HASHMAP_remove(self->raw_value, key);
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

PyObjectContainer* PY_STD_dict_eq(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 1);
    return PY_STD_dict_eq_fast(self, args[0]);
}

PyObjectContainer* PY_STD_dict_eq_fast(PyObjectContainer* self, PyObjectContainer* other)
{
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_DICT);
    assert(self->raw_value != NULL);

    if (other->type != PY_TYPE_PY_IMPL || other->py_type != PY_TYPE_DICT)
    {
        return PY_FALSE;
    }

    PY_THROW_EXCEPTION_IF(other->raw_value == NULL, NULL);

    HashMapContainer* self_cont = self->raw_value;
    HashMapContainer* other_cont = other->raw_value;

    if (self_cont->used_size != other_cont->used_size)
    {
        return PY_FALSE;
    }

    for (int i = 0; i < self_cont->alloc_size; i++)
    {
        PyObjectContainer* key = self_cont->key_memory[i];

        if (key == NULL || key == (PyObjectContainer*)&HASHMAP_MARKER_UNSET)
        {
            continue;
        }

        PyObjectContainer* other_value = HASHMAP_lookup(other_cont, key);
        if (other_value == NULL)
        {
            return PY_FALSE;
        }
        PyObjectContainer* self_value = self_cont->value_memory[i];
        PyObjectContainer* eq_method = PY_getObjectAttributeByNameOrStatic(self_value, "__eq__");

        if (eq_method == NULL) {
            if (self_value != other_value) {
                return PY_FALSE;
            }
        }
        else if (PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(eq_method, self_value, 1, &other_value, NULL)) == PY_FALSE)
        {
            return PY_FALSE;
        }
    }
    return PY_TRUE;
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
    copy_container->used_size = container->used_size;

    return copy;
}

PyObjectContainer* PY_STD_dict_concat(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 1);
    return PY_STD_dict_concat_fast(self, args[0]);
}

PyObjectContainer* PY_STD_dict_concat_fast(PyObjectContainer* self, PyObjectContainer* other)
{
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_DICT);
    assert(self->raw_value != NULL);

    if (other->type != PY_TYPE_PY_IMPL || other->py_type != PY_TYPE_DICT) {
        return PY_NOT_IMPLEMENTED;
    }
    assert(other->raw_value != NULL);

    PyObjectContainer* new_map = PY_STD_dict_CREATE(0);

    HashMapContainer* this_container = self->raw_value;
    for (uint64_t i = 0; i < this_container->alloc_size; i++)
    {
        PyObjectContainer* key = this_container->key_memory[i];

        if (key == NULL || key == (PyObjectContainer*)&HASHMAP_MARKER_UNSET)
        {
            continue;
        }

        PY_STD_dict_setitem_fast(new_map, key, this_container->value_memory[i]);
    }

    HashMapContainer* other_container = other->raw_value;
    for (uint64_t i = 0; i < other_container->alloc_size; i++)
    {
        PyObjectContainer* key = other_container->key_memory[i];

        if (key == NULL || key == (PyObjectContainer*)&HASHMAP_MARKER_UNSET)
        {
            continue;
        }

        PY_STD_dict_setitem_fast(new_map, key, other_container->value_memory[i]);
    }

    return new_map;
}

PyObjectContainer* PY_STD_dict_concat_inplace(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 1);
    return PY_STD_dict_concat_inplace_fast(self, args[0]);
}

PyObjectContainer* PY_STD_dict_concat_inplace_fast(PyObjectContainer* self, PyObjectContainer* other)
{
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_DICT);
    assert(self->raw_value != NULL);

    if (other->type != PY_TYPE_PY_IMPL || other->py_type != PY_TYPE_DICT) {
        return PY_NOT_IMPLEMENTED;
    }
    assert(other->raw_value != NULL);

    HashMapContainer* other_container = other->raw_value;

    for (uint64_t i = 0; i < other_container->alloc_size; i++)
    {
        PyObjectContainer* key = other_container->key_memory[i];

        if (key == NULL || key == (PyObjectContainer*)&HASHMAP_MARKER_UNSET)
        {
            continue;
        }

        PY_STD_dict_setitem_fast(self, key, other_container->value_memory[i]);
    }

    return self;
}

PyObjectContainer* PY_STD_dict_repr(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info) {
    assert(argc == 0);
    return PY_STD_dict_repr_fast(self);
}

PyObjectContainer* PY_STD_dict_repr_fast(PyObjectContainer* self) {
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_DICT);
    assert(self->raw_value != NULL);
    HashMapContainer* this_container = self->raw_value;

    int64_t dict_size = PY_unpackInteger(PY_STD_dict_len_fast(self));

    char* buffer = strdup("{}");
    size_t buffer_size = 2;

    bool first = true;
    if (dict_size > 0) {
        for (uint64_t i = 0; i < this_container->alloc_size; i++)
        {
            PyObjectContainer* key = this_container->key_memory[i];

            if (key == NULL || key == (PyObjectContainer*)&HASHMAP_MARKER_UNSET)
            {
                continue;
            }

            char* key_repr = PY_getObjectRepr(this_container->key_memory[i]);
            char* value_repr = PY_getObjectRepr(this_container->value_memory[i]);
            size_t inner_size = strlen(key_repr) + strlen(": ") + strlen(value_repr);
            if (!first) {
                inner_size += strlen(", ");
            }

            buffer = realloc(buffer, buffer_size + inner_size + 1);
            buffer[buffer_size-1] = '\0'; // remove the '}'
            buffer_size += inner_size;

            if (!first) {
                strcat(buffer, ", ");
            }

            strcat(buffer, key_repr);
            strcat(buffer, ": ");
            strcat(buffer, value_repr);
            strcat(buffer, "}");

            first = false;
        }
    }

    return PY_createString(buffer);
}

PyObjectContainer* PY_STD_dict_bool(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info) {
    assert(argc == 0);
    return PY_STD_dict_bool_fast(self);
}

PyObjectContainer* PY_STD_dict_bool_fast(PyObjectContainer* self) {
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_DICT);
    assert(self->raw_value != NULL);
    HashMapContainer* this_container = self->raw_value;
    return PY_createBoolean(this_container->used_size != 0);
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

        // is is a valid key?
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
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "fromkeys", PY_createBoxForFunction(PY_STD_dict_fromkeys));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "get", PY_createBoxForFunction(PY_STD_dict_get));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "pop", PY_createBoxForFunction(PY_STD_dict_pop));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "__init__", PY_createBoxForFunction(PY_STD_dict_init));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "__setitem__", PY_createBoxForFunction(PY_STD_dict_setitem));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "__getitem__", PY_createBoxForFunction(PY_STD_dict_getitem));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "__delitem__", PY_createBoxForFunction(PY_STD_dict_delitem));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "__contains__", PY_createBoxForFunction(PY_STD_dict_contains));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "__len__", PY_createBoxForFunction(PY_STD_dict_len));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "__eq__", PY_createBoxForFunction(PY_STD_dict_eq));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "setdefault", PY_createBoxForFunction(PY_STD_dict_setdefault));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "clear", PY_createBoxForFunction(PY_STD_dict_clear));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "copy", PY_createBoxForFunction(PY_STD_dict_copy));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "__or__", PY_createBoxForFunction(PY_STD_dict_concat));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "__ior__", PY_createBoxForFunction(PY_STD_dict_concat_inplace));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "update", PY_createBoxForFunction(PY_STD_dict_concat_inplace));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "__repr__", PY_createBoxForFunction(PY_STD_dict_repr));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "__str__", PY_createBoxForFunction(PY_STD_dict_repr));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "__bool__", PY_createBoxForFunction(PY_STD_dict_bool));

#ifdef PY_ENABLE_GENERATORS
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "__iter__", PY_createBoxForFunction(PY_STD_dict_keys));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "keys", PY_createBoxForFunction(PY_STD_dict_keys));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "values", PY_createBoxForFunction(PY_STD_dict_values));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_DICT, "items", PY_createBoxForFunction(PY_STD_dict_items));
#endif
}

