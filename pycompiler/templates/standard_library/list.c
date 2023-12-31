#include <stdlib.h>
#include <assert.h>
#include <memory.h>
#include <stdarg.h>
#include <string.h>
#include "list.h"
#include "operators.h"
#include "exceptions.h"
#include "config.h"

#ifdef PY_ENABLE_GENERATORS
#include "generator.h"
#endif

PyClassContainer* PY_TYPE_LIST;

#define PY_STD_LIST_START_SIZE 4

PyObjectContainer* PY_STD_list_init(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    if (argc == 0)
    {
        return PY_STD_list_init_fast_arg_0(self);
    }
    else
    {
        assert(argc == 1);
        return PY_STD_list_init_fast_arg_1(self, args[0]);
    }
}

PyObjectContainer* PY_STD_list_init_fast_arg_0(PyObjectContainer* self)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    assert(self->raw_value == NULL);

    PY_STD_list_container* list = malloc(sizeof(PY_STD_list_container));

    if (list == NULL)
    {
        perror("malloc PY_STD_list_init container");
        exit(EXIT_FAILURE);
    }

    self->raw_value = list;
    list->curr_size = 0;
    list->rem_size = PY_STD_LIST_START_SIZE;
    list->array = malloc(PY_STD_LIST_START_SIZE * sizeof(PyObjectContainer*));

    if (list->array == NULL)
    {
        perror("malloc PY_STD_list_init array");
        exit(EXIT_FAILURE);
    }

    return PY_NONE;
}

PyObjectContainer* PY_STD_list_init_fast_arg_1(PyObjectContainer* self, PyObjectContainer* source)
{
    // Case where we can be a lot faster
    if (source->type == PY_TYPE_PY_IMPL && source->py_type == PY_TYPE_LIST)
    {
        PY_STD_list_container* source_container = source->raw_value;
        PY_STD_list_init_fast_reserve(self, source_container->curr_size + source_container->rem_size);
        PY_STD_list_container* self_container = self->raw_value;
        memcpy(self_container->array, source_container->array, source_container->curr_size * sizeof(PyObjectContainer*));
        self_container->curr_size = source_container->curr_size;
        self_container->rem_size = source_container->rem_size;
        return PY_NONE;
    }

    PyObjectContainer* len_method = PY_getObjectAttributeByNameOrStatic(source, "__len__");

    bool flag = false;
    if (len_method != NULL)
    {
        PyObjectContainer* size = PY_invokeBoxedMethod(len_method, source, 0, NULL, NULL);
        if (size != NULL)
        {
            PY_STD_list_init_fast_reserve(self, PY_unpackInteger(size));
            flag = true;
        }
    }
    if (!flag)
    {
        PY_STD_list_init_fast_arg_0(self);
    }

    PyObjectContainer* iter_method = PY_getObjectAttributeByNameOrStatic(source, "__iter__");
    if (iter_method == NULL)
    {
        printf("data type: %s\n", PY_getObjectClassName(source));
        PY_THROW_EXCEPTION_WITH_MESSAGE(NULL, "expected <supports __iter__>");
    }

    PyObjectContainer* iterator = PY_invokeBoxedMethod(iter_method, NULL, 0, NULL, NULL);

    PyObjectContainer* value;
    value = PY_STD_operator_next_with_default(iterator, NULL);
    while (value)
    {
        PY_STD_list_append_fast(self, value);
        value = PY_STD_operator_next_with_default(iterator, NULL);
    }

    return PY_NONE;
}

PyObjectContainer* PY_STD_list_init_fast_reserve(PyObjectContainer* self, uint16_t size)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    assert(self->raw_value == NULL);

    if (size < PY_STD_LIST_START_SIZE)
    {
        size = PY_STD_LIST_START_SIZE;
    }

    PY_STD_list_container* list = malloc(sizeof(PY_STD_list_container));

    if (list == NULL)
    {
        perror("malloc PY_STD_list_init container");
        exit(EXIT_FAILURE);
    }

    self->raw_value = list;
    list->curr_size = 0;
    list->rem_size = size;
    list->array = malloc(size * sizeof(PyObjectContainer*));

    if (list->array == NULL)
    {
        perror("malloc PY_STD_list_init_fast_reserve array");
        exit(EXIT_FAILURE);
    }

    return PY_NONE;
}

PyObjectContainer* PY_STD_list_CONSTRUCT_COMPREHENSION(PyObjectContainer* iterable, PY_FUNC_GENERATOR_ITEM transfer, PY_FUNC_GENERATOR_ITEM condition, PyObjectContainer** locals)
{
    PyObjectContainer* len_method = PY_getObjectAttributeByNameOrStatic(iterable, "__len__");
    PyObjectContainer* list = PY_createClassInstance(PY_TYPE_LIST);

    // Do we know ahead of time how many elements we will get?
    if (len_method != NULL)
    {
        int64_t len = PY_unpackInteger(PY_invokeBoxedMethod(len_method, iterable, 0, NULL, NULL));
        assert(len >= 0);
        PY_STD_list_init_fast_reserve(list, len);
    }
    else
    {
        PY_STD_list_init_fast_arg_0(list);
    }

    PyObjectContainer* iterator = PY_STD_operator_iter(iterable);

    PyObjectContainer* value;
    while ((value = PY_STD_operator_next_with_default(iterator, NULL)) != NULL)
    {
        PY_CHECK_EXCEPTION(value);
        if (condition == NULL || PY_getTruthValueOf(PY_CHECK_EXCEPTION(condition(value, locals))))
        {
            PY_CHECK_EXCEPTION(PY_STD_list_append_fast(list, transfer(value, locals)));
        }
    }

    return list;
}

PyObjectContainer* PY_STD_list_CONSTRUCT_COMPREHENSION_on_list(PyObjectContainer* iterable, PY_FUNC_GENERATOR_ITEM transfer, PY_FUNC_GENERATOR_ITEM condition, PyObjectContainer** locals)
{
    assert(iterable != NULL);
    assert(iterable->type == PY_TYPE_PY_IMPL);
    assert(iterable->py_type == PY_TYPE_LIST);

    PY_STD_list_container* source_list = iterable->raw_value;

    PyObjectContainer* list = PY_createClassInstance(PY_TYPE_LIST);
    PY_STD_list_init_fast_reserve(list, source_list->curr_size);

    for (uint16_t i = 0; i < source_list->curr_size; i++)
    {
        PyObjectContainer* value = source_list->array[i];
        if (condition == NULL || PY_getTruthValueOf(PY_CHECK_EXCEPTION(condition(value, locals))))
        {
            PY_CHECK_EXCEPTION(PY_STD_list_append_fast(list, transfer(value, locals)));
        }
    }

    return list;
}

PyObjectContainer* PY_STD_list_CONSTRUCT_COMPREHENSION_with_len_hint(PyObjectContainer* iterable, PY_FUNC_GENERATOR_ITEM transfer, PY_FUNC_GENERATOR_ITEM condition, PyObjectContainer** locals, PY_FUNC_UNBOXED len_hint)
{
    PyObjectContainer* list = PY_createClassInstance(PY_TYPE_LIST);

    int64_t len = PY_unpackInteger(len_hint(iterable, 0, NULL, NULL));
    assert(len >= 0);
    PY_STD_list_init_fast_reserve(list, len);

    PyObjectContainer* iterator = PY_STD_operator_iter(iterable);

    PyObjectContainer* value;
    while ((value = PY_STD_operator_next_with_default(iterator, NULL)) != NULL)
    {
        PY_CHECK_EXCEPTION(value);
        if (condition == NULL || PY_getTruthValueOf(PY_CHECK_EXCEPTION(condition(value, locals))))
        {
            PY_CHECK_EXCEPTION(PY_STD_list_append_fast(list, transfer(value, locals)));
        }
    }
    DECREF(iterator);

    return list;
}

PyObjectContainer* PY_STD_list_CONSTRUCT_COMPREHENSION_with_iter_hint(PyObjectContainer* iterable, PY_FUNC_GENERATOR_ITEM transfer, PY_FUNC_GENERATOR_ITEM condition, PyObjectContainer** locals, PyObjectContainer* iter_hint(PyObjectContainer*))
{
    PyObjectContainer* len_method = PY_getObjectAttributeByNameOrStatic(iterable, "__len__");
    PyObjectContainer* list = PY_createClassInstance(PY_TYPE_LIST);

    // Do we know ahead of time how many elements we will get?
    if (len_method != NULL)
    {
        int64_t len = PY_unpackInteger(PY_invokeBoxedMethod(len_method, iterable, 0, NULL, NULL));
        assert(len >= 0);
        PY_STD_list_init_fast_reserve(list, len);
    }
    else
    {
        PY_STD_list_init_fast_arg_0(list);
    }

    PyObjectContainer* iterator = iter_hint(iterable);

    PyObjectContainer* value;
    while ((value = PY_STD_operator_next_with_default(iterator, NULL)) != NULL)
    {
        PY_CHECK_EXCEPTION(value);
        if (condition == NULL || PY_getTruthValueOf(PY_CHECK_EXCEPTION(condition(value, locals))))
        {
            PY_CHECK_EXCEPTION(PY_STD_list_append_fast(list, transfer(value, locals)));
        }
    }
    DECREF(iterator);

    return list;
}

PyObjectContainer* PY_STD_list_CONSTRUCT_COMPREHENSION_with_len_hint_with_iter_hint(PyObjectContainer* iterable, PY_FUNC_GENERATOR_ITEM transfer, PY_FUNC_GENERATOR_ITEM condition, PyObjectContainer** locals, PY_FUNC_UNBOXED len_hint, PyObjectContainer* iter_hint(PyObjectContainer*))
{
    PyObjectContainer* list = PY_createClassInstance(PY_TYPE_LIST);

    int64_t len = PY_unpackInteger(len_hint(iterable, 0, NULL, NULL));
    assert(len >= 0);
    PY_STD_list_init_fast_reserve(list, len);

    PyObjectContainer* iterator = iter_hint(iterable);

    PyObjectContainer* value;
    while ((value = PY_STD_operator_next_with_default(iterator, NULL)) != NULL)
    {
        PY_CHECK_EXCEPTION(value);
        if (condition == NULL || PY_getTruthValueOf(PY_CHECK_EXCEPTION(condition(value, locals))))
        {
            PY_CHECK_EXCEPTION(PY_STD_list_append_fast(list, transfer(value, locals)));
        }
    }

    return list;
}

PyObjectContainer* PY_STD_list_CONSTRUCT(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    assert(self->raw_value == NULL);
    PY_STD_list_container* container = malloc(sizeof(PY_STD_list_container));
    if (container == NULL)
    {
        perror("malloc PY_STD_list_CONSTRUCT A");
        exit(EXIT_FAILURE);
    }
    self->raw_value = container;
    container->curr_size = argc;
    container->rem_size = argc == 0 ? 1 : 0;

    container->array = malloc((argc == 0 ? 1 : argc) * sizeof(PyObjectContainer*));
    if (container->array == NULL)
    {
        perror("malloc PY_STD_list_CONSTRUCT B");
        exit(EXIT_FAILURE);
    }
    memcpy(container->array, args, argc * sizeof(PyObjectContainer*));

    return self;
}


PyObjectContainer* PY_STD_list_CREATE(uint8_t argc, ...)
{
    PyObjectContainer* list = PY_createClassInstance(PY_TYPE_LIST);

    va_list ap;
    PyObjectContainer* args[argc];
    va_start(ap, argc);
    for(int i = 0; i < argc; i++){
        PyObjectContainer* t = va_arg(ap, PyObjectContainer*);
        INCREF(t);
        args[i] = t;
    }
    va_end(ap);

    PY_STD_list_CONSTRUCT(list, argc, args, NULL);

    return list;
}

void PY_STD_list_ensure_size(PyObjectContainer* self, uint64_t size)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    PY_STD_list_container* list = (PY_STD_list_container*)self->raw_value;

    if (size < list->curr_size + list->rem_size)
    {
        return;
    }

    list->array = realloc(list->array, size * sizeof(PyObjectContainer*));
    if (list->array == NULL)
    {
        perror("realloc PY_STD_list_ensure_size");
        exit(EXIT_FAILURE);
    }

    list->rem_size = size - list->curr_size;
}

// <list>.append(<item>)
PyObjectContainer* PY_STD_list_append(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    assert(argc == 1);

    PY_STD_list_container* list = (PY_STD_list_container*)self->raw_value;

    if (list->rem_size > 0)
    {
        list->rem_size--;
        list->array[list->curr_size] = args[0];
        list->curr_size++;
    }
    else
    {
        list->array = realloc(list->array, 2 * list->curr_size * sizeof(PyObjectContainer*));
        if (list->array == NULL)
        {
            perror("malloc PY_STD_list_append");
            exit(EXIT_FAILURE);
        }

        list->rem_size = list->curr_size - 1;
        list->array[list->curr_size] = args[0];
        list->curr_size++;
    }

    return PY_NONE;
}

PyObjectContainer* PY_STD_list_append_fast(PyObjectContainer* self, PyObjectContainer* param)
{
    assert(self != NULL);
    PY_THROW_EXCEPTION_IF_WITH_MESSAGE(self->type != PY_TYPE_PY_IMPL, NULL, PY_getObjectRepr(self));
    assert(self->py_type == PY_TYPE_LIST);

    PY_STD_list_container* list = (PY_STD_list_container*)self->raw_value;

    if (list->rem_size > 0)
    {
        list->rem_size--;
        list->array[list->curr_size] = param;
        list->curr_size++;
    }
    else
    {
        list->array = realloc(list->array, 2 * list->curr_size * sizeof(PyObjectContainer*));
        if (list->array == NULL)
        {
            perror("malloc PY_STD_list_append");
            exit(EXIT_FAILURE);
        }

        list->rem_size = list->curr_size - 1;
        list->array[list->curr_size] = param;
        list->curr_size++;
    }

    return PY_NONE;
}

// <list>.insert(<index>, <item>)
PyObjectContainer* PY_STD_list_insert(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 2);
    return PY_STD_list_insert_fast_with_int(self, PY_unpackInteger(args[0]), args[1]);
}

PyObjectContainer* PY_STD_list_insert_fast(PyObjectContainer* self, PyObjectContainer* raw_index, PyObjectContainer* value)
{
    return PY_STD_list_insert_fast_with_int(self, PY_unpackInteger(raw_index), value);
}

PyObjectContainer* PY_STD_list_insert_fast_with_int(PyObjectContainer* self, int64_t index, PyObjectContainer* value)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);

    PY_STD_list_container* list = (PY_STD_list_container*)self->raw_value;

    if (index < 0)
    {
        index = list->curr_size + index;
    }

    if (list->rem_size == 0)
    {
        list->array = realloc(list->array, 2 * list->curr_size * sizeof(PyObjectContainer*));
        if (list->array == NULL)
        {
            perror("malloc PY_STD_list_insert");
            exit(EXIT_FAILURE);
        }

        list->rem_size = list->curr_size;
    }

    for (int64_t i = index + 1; i < list->curr_size; i++)
    {
        list->array[i-1] = list->array[i];
    }

    list->array[index] = value;
    list->curr_size++;
    list->rem_size--;

    return PY_NONE;
}

PyObjectContainer* PY_STD_list_index(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    assert(argc == 1);

    PyObjectContainer* cmp = PY_getObjectAttributeByNameOrStatic(args[0], "__eq__");
    assert(cmp != NULL);

    PY_STD_list_container* list = (PY_STD_list_container*)self->raw_value;

    for (int i = 0; i < list->curr_size; i++)
    {
        PyObjectContainer* obj = list->array[i];
        PyObjectContainer* is_eq = PY_invokeBoxedMethod(cmp, args[0], 1, &obj, NULL);
        if (is_eq == PY_TRUE)
        {
            return PY_createInteger(i);
        }
    }

    PY_THROW_EXCEPTION(NULL);
}

PyObjectContainer* PY_STD_list_index_fast(PyObjectContainer* self, PyObjectContainer* value)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);

    PyObjectContainer* cmp = PY_getObjectAttributeByNameOrStatic(value, "__eq__");
    assert(cmp != NULL);

    PY_STD_list_container* list = (PY_STD_list_container*)self->raw_value;

    for (int i = 0; i < list->curr_size; i++)
    {
        PyObjectContainer* obj = list->array[i];
        PyObjectContainer* is_eq = PY_invokeBoxedMethod(cmp, value, 1, &obj, NULL);
        if (is_eq == PY_TRUE)
        {
            return PY_createInteger(i);
        }
    }

    PY_THROW_EXCEPTION(NULL);
}

int64_t PY_STD_list_index_fast_list(PyObjectContainer* self, PyObjectContainer* value)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);

    PyObjectContainer* cmp = PY_getObjectAttributeByNameOrStatic(value, "__eq__");
    assert(cmp != NULL);

    PY_STD_list_container* list = (PY_STD_list_container*)self->raw_value;

    for (int i = 0; i < list->curr_size; i++)
    {
        PyObjectContainer* obj = list->array[i];
        PyObjectContainer* is_eq = PY_invokeBoxedMethod(cmp, value, 1, &obj, NULL);
        if (is_eq == PY_TRUE)
        {
            return i;
        }
    }

    assert(false);
}

void PY_STD_list_removeIndex(PY_STD_list_container* list, uint16_t index);
PyObjectContainer* PY_STD_list_remove(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    PY_THROW_EXCEPTION_IF_WITH_MESSAGE(self == NULL, NULL, "'self' must not be NULL");
    PY_THROW_EXCEPTION_IF_WITH_MESSAGE(self->type != PY_TYPE_PY_IMPL && self->py_type == PY_TYPE_LIST, NULL, "must be of type 'list'");
    PY_THROW_EXCEPTION_IF_WITH_MESSAGE(argc != 1, NULL, "expected exactly one argument to <list>.__delitem__");

    PyObjectContainer* cmp = PY_getObjectAttributeByNameOrStatic(args[0], "__eq__");
    PY_THROW_EXCEPTION_IF_WITH_MESSAGE(cmp == NULL, NULL, "expected <supports __eq__> to be removed from a list");

    PY_STD_list_container* list = (PY_STD_list_container*)self->raw_value;
    assert(list != NULL);  // Can only happen when something internally goes wrong

    for (int i = 0; i < list->curr_size; i++)
    {
        PyObjectContainer* obj = list->array[i];
        PyObjectContainer* is_eq = PY_invokeBoxedMethod(cmp, args[0], 1, &obj, NULL);
        if (is_eq == PY_TRUE)
        {
            PY_STD_list_removeIndex(list, i);
            return PY_NONE;
        }
    }

    PY_THROW_EXCEPTION(NULL);
}

PyObjectContainer* PY_STD_list_setAtIndex(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 2);
    assert(args[0]->type == PY_TYPE_INT);
    PY_STD_list_setAtIndex_fast_with_int(self, PY_unpackInteger(args[0]), args[1]);

    return PY_NONE;
}

PyObjectContainer* PY_STD_list_setAtIndex_fast(PyObjectContainer* self, PyObjectContainer* index_wrapper, PyObjectContainer* value)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    int64_t index = PY_unpackInteger(index_wrapper);

    PY_STD_list_container* list = (PY_STD_list_container*)self->raw_value;

    assert(index >= 0 && index < list->curr_size);

    list->array[index] = value;

    return PY_NONE;
}

PyObjectContainer* PY_STD_list_setAtIndex_fast_with_int(PyObjectContainer* self, int64_t index, PyObjectContainer* value)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);

    PY_STD_list_container* list = (PY_STD_list_container*)self->raw_value;

    assert(index >= 0 && index < list->curr_size);

    list->array[index] = value;

    return PY_NONE;
}

PyObjectContainer* PY_STD_list_getAtIndex(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 1);
    assert(args[0]->type == PY_TYPE_INT);
    return PY_STD_list_getAtIndex_fast_with_int(self, PY_unpackInteger(args[0]));
}

PyObjectContainer* PY_STD_list_getAtIndex_fast(PyObjectContainer* self, PyObjectContainer* raw_index)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    int64_t index = PY_unpackInteger(raw_index);

    PY_STD_list_container* list = (PY_STD_list_container*)self->raw_value;

    assert(index >= 0 && index < list->curr_size);

    return list->array[index];
}

PyObjectContainer* PY_STD_list_getAtIndex_fast_with_int(PyObjectContainer* self, int64_t index)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);

    PY_STD_list_container* list = (PY_STD_list_container*)self->raw_value;

    assert(index >= 0 && index < list->curr_size);

    return list->array[index];
}

PyObjectContainer* PY_STD_list_removeAtIndex(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    assert(argc == 1);
    assert(args[0] != NULL && args[0]->type == PY_TYPE_INT);
    int64_t index = *(int64_t*)args[0]->raw_value;

    PY_STD_list_container* list = (PY_STD_list_container*)self->raw_value;

    assert(list != NULL);
    assert(index >= 0 && index < list->curr_size);

    PY_STD_list_removeIndex(list, index);

    return PY_NONE;
}

PyObjectContainer* PY_STD_list_clear(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 0);
    return PY_STD_list_clear_fast(self);
}

PyObjectContainer* PY_STD_list_clear_fast(PyObjectContainer* self)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    PY_STD_list_container* list = (PY_STD_list_container*)self->raw_value;
    assert(list != NULL);

    free(list->array);
    list->array = malloc(PY_STD_LIST_START_SIZE * sizeof(PyObjectContainer*));

    if (list->array == NULL)
    {
        perror("malloc PY_STD_list_clear");
        exit(EXIT_FAILURE);
    }
    list->curr_size = 0;
    list->rem_size = PY_STD_LIST_START_SIZE;

    return PY_NONE;
}

PyObjectContainer* PY_STD_list_eq(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    assert(argc == 1);
    assert(args[0] != NULL);

    if (args[0]->type != PY_TYPE_PY_IMPL || args[0]->py_type != PY_TYPE_LIST)
    {
        return PY_FALSE;
    }

    PY_STD_list_container* lhs = (PY_STD_list_container*)self->raw_value;
    PY_STD_list_container* rhs = (PY_STD_list_container*)args[0]->raw_value;

    if (lhs->curr_size != rhs->curr_size)
    {
        return PY_FALSE;
    }

    for (int i = 0; i < lhs->curr_size; i++)
    {
        PyObjectContainer* lhs_element = lhs->array[i];
        PyObjectContainer* rhs_element = rhs->array[i];

        if (PY_STD_operator_equals(lhs_element, rhs_element) == PY_FALSE)
        {
            return PY_FALSE;
        }
    }

    return PY_TRUE;
}

PyObjectContainer* PY_STD_list_len(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    if (self != NULL)
    {
        assert(argc == 0);
    }
    else
    {
        assert(argc == 1);
        self = args[0];
    }
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    PY_STD_list_container* list = (PY_STD_list_container*)self->raw_value;
    return PY_createInteger(list->curr_size);
}

PyObjectContainer* PY_STD_list_len_fast(PyObjectContainer* self)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    PY_STD_list_container* list = (PY_STD_list_container*)self->raw_value;
    return PY_createInteger(list->curr_size);
}

PyObjectContainer* PY_STD_list_toBool(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    assert(argc == 0);

    PY_STD_list_container* list = (PY_STD_list_container*)self->raw_value;

    if (list->curr_size == 0)
    {
        return PY_FALSE;
    }
    return PY_TRUE;
}

PyObjectContainer* PY_STD_list_toBool_fast(PyObjectContainer* self)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);

    PY_STD_list_container* list = (PY_STD_list_container*)self->raw_value;

    if (list->curr_size == 0)
    {
        return PY_FALSE;
    }
    return PY_TRUE;
}

#ifdef PY_ENABLE_GENERATORS
PyObjectContainer* PY_STD_list_iter(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 0);
    return PY_STD_list_iter_fast(self);
}

PyObjectContainer* PY_STD_list_iterator(PyGeneratorContainer* generator)
{
    PyObjectContainer* self = generator->locals[0];
    PY_STD_list_container* list = (PY_STD_list_container*)self->raw_value;
    if (generator->section_id >= list->curr_size)
    {
        return NULL;
    }
    return list->array[generator->section_id++];
}

PyObjectContainer* PY_STD_list_iter_fast(PyObjectContainer* self)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);

    PyObjectContainer* generator = PY_STD_GENERATOR_create(1);
    PyGeneratorContainer* container = generator->raw_value;
    container->section_id = 0;
    container->locals[0] = self;
    container->next_section = PY_STD_list_iterator;
    return generator;
}
#endif

PyObjectContainer* PY_STD_list_repr(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 0);
    return PY_STD_list_repr_fast(self);
}

PyObjectContainer* PY_STD_list_repr_fast(PyObjectContainer* self)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);

    PY_STD_list_container* list = (PY_STD_list_container*)self->raw_value;

    if (list->curr_size == 0)
    {
        return PY_createString("[]");
    }

    char* buffer = strdup("[]");
    buffer[1] = '\0';
    if (buffer == NULL)
    {
        perror("strdup list repr");
        exit(EXIT_FAILURE);
    }
    size_t size = 3;
    bool is_first_entry = true;

    for (int i = 0; i < list->curr_size; i++) {
        char *frag_repr = PY_getObjectRepr(list->array[i]);
        if (!is_first_entry)
        {
            size = size + 2 + strlen(frag_repr);
        }
        else
        {
            size = size + strlen(frag_repr);
        }
        buffer = realloc(buffer, size);
        if (buffer == NULL)
        {
            perror("realloc list repr fast");
            exit(EXIT_FAILURE);
        }
        if (!is_first_entry)
        {
            strcat(buffer, ", ");
        }
        strcat(buffer, frag_repr);
        is_first_entry = false;
    }
    buffer[strlen(buffer)] = ']';

    return PY_createString(buffer);
}

void PY_STD_list_removeIndex(PY_STD_list_container* list, uint16_t index)
{
    assert(list != NULL);
    assert(0 <= index && index < list->curr_size);

    PyObjectContainer* obj = list->array[index];
    list->array[index] = NULL;
    DECREF(obj);

    if (list->curr_size - index > 2) {
        memcpy(list->array[index + 1], list->array[index], sizeof(PyObjectContainer *) * (list->curr_size - index - 2));
    }
    list->array[list->curr_size] = NULL;
    list->curr_size++;
    list->rem_size++;

    // TODO: maybe release some memory?
}

static int PY_STD_list_sort_cmp(const void* lhs_r, const void* rhs_r)
{
    PyObjectContainer* lhs = *(PyObjectContainer**)lhs_r;
    PyObjectContainer* rhs = *(PyObjectContainer**)rhs_r;

    PyObjectContainer* cmp = PY_getObjectAttributeByNameOrStatic(lhs, "__lt__");
    if (PY_invokeBoxedMethod(cmp, lhs, 1, &rhs, NULL) == PY_TRUE)
    {
        return -1;
    }

    PyObjectContainer* eq = PY_getObjectAttributeByNameOrStatic(lhs, "__eq__");
    if (PY_invokeBoxedMethod(eq, lhs, 1, &rhs, NULL) == PY_TRUE)
    {
        return 0;
    }

    return 1;
}

PyObjectContainer* PY_STD_list_sort(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    assert(argc <= 1);

    PY_STD_list_container* list = (PY_STD_list_container*)self->raw_value;

    PyObjectContainer* sort_key = PY_ARGS_getKeywordParameter(args, info, PY_createString("key"));
    // todo: use sort_key if provided

    qsort(list->array, list->curr_size, sizeof(PyObjectContainer*), PY_STD_list_sort_cmp);

    return PY_NONE;
}

PyObjectContainer* PY_STD_list_sort_fast_arg_0(PyObjectContainer* self)
{
    PY_STD_list_container* list = (PY_STD_list_container*)self->raw_value;
    qsort(list->array, list->curr_size, sizeof(PyObjectContainer*), PY_STD_list_sort_cmp);

    return PY_NONE;
}

PyObjectContainer* PY_STD_list_extend(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 1);
    return PY_STD_list_extend_fast(self, args[0]);
}

PyObjectContainer* PY_STD_list_extend_fast(PyObjectContainer* self, PyObjectContainer* other)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);

    PyObjectContainer* list;
    if (other != NULL && other->type == PY_TYPE_PY_IMPL && other->py_type == PY_TYPE_LIST)
    {
        list = other;
    }
    else
    {
        list = PY_createClassInstance(PY_TYPE_LIST);
        PY_STD_list_init_fast_arg_1(list, other);
    }

   return PY_STD_list_extend_fast_with_list(self, list);
}

PyObjectContainer* PY_STD_list_extend_fast_with_list(PyObjectContainer* self, PyObjectContainer* list)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);

    PY_STD_list_container* list_lhs = (PY_STD_list_container*)self->raw_value;
    PY_STD_list_container* list_rhs = (PY_STD_list_container*)list->raw_value;

    if (list_lhs->rem_size >= list_rhs->curr_size)
    {
        memcpy(list_lhs->array + list_lhs->curr_size, list_rhs->array, list_rhs->curr_size * sizeof(PyObjectContainer *));
        list_lhs->curr_size += list_rhs->curr_size;
    }
    else
    {
        list_lhs->array = realloc(list_lhs->array, (list_lhs->curr_size + list_rhs->curr_size) * sizeof(PyObjectContainer *));
        if (list_lhs->array == NULL) {
            perror("malloc extend");
            exit(EXIT_FAILURE);
        }

        memcpy(list_lhs->array + list_lhs->curr_size, list_rhs->array, list_rhs->curr_size * sizeof(PyObjectContainer *));
        list_lhs->rem_size = 0;
        list_lhs->curr_size += list_rhs->curr_size;
    }
    return self;
}

PyObjectContainer* PY_STD_list_add(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 1);
    return PY_STD_list_add_fast(self, args[0]);
}

PyObjectContainer* PY_STD_list_add_fast(PyObjectContainer* self, PyObjectContainer* other)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    assert(other != NULL);
    assert(other->type == PY_TYPE_PY_IMPL);
    assert(other->py_type == PY_TYPE_LIST);

    PyObjectContainer* new_list = PY_STD_list_CREATE(0);
    PY_STD_list_extend_fast(new_list, self);
    PY_STD_list_extend_fast(new_list, other);
    return new_list;
}

PyObjectContainer* PY_STD_list_mul(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 1);
    return PY_STD_list_mul_fast(self, args[0]);
}

PyObjectContainer* PY_STD_list_mul_fast(PyObjectContainer* self, PyObjectContainer* times)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    assert(times != NULL);
    assert(times->type == PY_TYPE_INT);
    int64_t factor = PY_unpackInteger(times);
    assert(factor >= 0);
    PY_STD_list_container* list_lhs = (PY_STD_list_container*)self->raw_value;

    if (factor == 0)
    {
        PyObjectContainer* list = PY_createClassInstance(PY_TYPE_LIST);
        PY_STD_list_init_fast_arg_0(list);
        return list;
    }

    // Create the new list to be returned
    // TODO: incref all references!
    PyObjectContainer* list = PY_createClassInstance(PY_TYPE_LIST);
    PY_STD_list_init_fast_reserve(list, list_lhs->curr_size * factor);
    PY_STD_list_container* new_list = list->raw_value;

    for (int64_t i = 0; i < factor; i++)
    {
        memcpy(new_list->array + new_list->curr_size, list_lhs->array, list_lhs->curr_size * sizeof(PyObjectContainer *));
        new_list->curr_size += list_lhs->curr_size;
    }

    return list;
}

PyObjectContainer* PY_STD_list_imul(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 1);
    return PY_STD_list_imul_fast(self, args[0]);
}

PyObjectContainer* PY_STD_list_imul_fast(PyObjectContainer* self, PyObjectContainer* times)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    assert(times != NULL);
    assert(times->type == PY_TYPE_INT);
    int64_t factor = PY_unpackInteger(times);
    assert(factor >= 0);
    PY_STD_list_container* list_lhs = (PY_STD_list_container*)self->raw_value;
    uint16_t original_size = list_lhs->curr_size;

    if (factor == 0)
    {
        PY_STD_list_clear_fast(self);
        return self;
    }

    // Ensure that the array is big enough, so we can copy over the data
    // TODO: incref all references!
    PY_STD_list_ensure_size(self, list_lhs->curr_size * factor);

    for (int64_t i = 0; i < factor; i++)
    {
        memcpy(list_lhs->array + list_lhs->curr_size, list_lhs->array, original_size * sizeof(PyObjectContainer *));
        list_lhs->curr_size += original_size;
    }

    return self;
}

PyObjectContainer* PY_STD_list_copy(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 0);
    return PY_STD_list_copy_fast(self);
}

PyObjectContainer* PY_STD_list_copy_fast(PyObjectContainer* self)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    PY_STD_list_container* list_lhs = (PY_STD_list_container*)self->raw_value;
    PyObjectContainer* result = PY_createClassInstance(PY_TYPE_LIST);
    PY_STD_list_container* new_list = result->raw_value;
    PY_CHECK_EXCEPTION(PY_STD_list_init_fast_reserve(result, list_lhs->curr_size + list_lhs->rem_size));
    memcpy(new_list->array, list_lhs->array, sizeof(PyObjectContainer*) * list_lhs->curr_size);
    new_list->curr_size = list_lhs->curr_size;
    new_list->rem_size = list_lhs->rem_size;

    return result;
}

PyObjectContainer* PY_STD_list_del(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info) {
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    PY_STD_list_container* list = (PY_STD_list_container*)self->raw_value;
    free(list->array);
    free(list);
    return PY_NONE;
}

void PY_STD_initListType(void)
{
    PY_TYPE_LIST = PY_createClassContainer("list");
    PY_TYPE_LIST->flags |= PY_CLASS_IS_STD_IMPLEMENTED;
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "__init__", PY_createBoxForFunction(PY_STD_list_init));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "append", PY_createBoxForFunction(PY_STD_list_append));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "insert", PY_createBoxForFunction(PY_STD_list_insert));
    // extend(<array>)
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "index", PY_createBoxForFunction(PY_STD_list_index));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "remove", PY_createBoxForFunction(PY_STD_list_remove));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "__setitem__", PY_createBoxForFunction(PY_STD_list_setAtIndex));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "__getitem__", PY_createBoxForFunction(PY_STD_list_getAtIndex));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "__delitem__", PY_createBoxForFunction(PY_STD_list_removeAtIndex));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "clear", PY_createBoxForFunction(PY_STD_list_clear));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "__eq__", PY_createBoxForFunction(PY_STD_list_eq));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "__len__", PY_createBoxForFunction(PY_STD_list_len));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "extend", PY_createBoxForFunction(PY_STD_list_extend));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "__add__", PY_createBoxForFunction(PY_STD_list_add));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "__iadd__", PY_createBoxForFunction(PY_STD_list_extend));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "__mul__", PY_createBoxForFunction(PY_STD_list_mul));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "__del__", PY_createBoxForFunction(PY_STD_list_del));
#ifdef PY_ENABLE_GENERATORS
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "__iter__", PY_createBoxForFunction(PY_STD_list_iter));
#endif
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "__repr__", PY_createBoxForFunction(PY_STD_list_repr));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "__bool__", PY_createBoxForFunction(PY_STD_list_toBool));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "sort", PY_createBoxForFunction(PY_STD_list_sort));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "__copy__", PY_createBoxForFunction(PY_STD_list_copy));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "copy", PY_createBoxForFunction(PY_STD_list_copy));
    // __sorted__
    // count
    // __contains__
    // pop
    // __imul__
}