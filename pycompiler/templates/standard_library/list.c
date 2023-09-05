#include <stdlib.h>
#include <assert.h>
#include <memory.h>
#include <stdarg.h>
#include "list.h"
#include "operators.h"

PyClassContainer* PY_TYPE_LIST;

struct PY_STD_list_container
{
    uint16_t curr_size;
    uint16_t rem_size;
    PyObjectContainer** array;
};
typedef struct PY_STD_list_container PY_STD_list_container;

#define PY_STD_LIST_START_SIZE 4

PyObjectContainer* PY_STD_list_init(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    assert(self->raw_value == NULL);  // only one init!

    if (argc == 0)
    {
        PY_STD_list_container* list = malloc(sizeof(PY_STD_list_container));

        if (list == NULL)
        {
            perror("malloc PY_STD_list_init A");
            exit(EXIT_FAILURE);
        }

        self->raw_value = list;
        list->curr_size = 0;
        list->rem_size = PY_STD_LIST_START_SIZE;
        list->array = malloc(PY_STD_LIST_START_SIZE * sizeof(PyObjectContainer*));

        if (list->array == NULL)
        {
            perror("malloc PY_STD_list_init B");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        assert(false);  // not implemented todo: implement
    }

    return NULL;
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
    container->array = malloc(argc * sizeof(PyObjectContainer*));
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
    PyObjectContainer* tuple = PY_createClassInstance(PY_TYPE_LIST);

    va_list ap;
    PyObjectContainer* args[argc];
    va_start(ap, argc);
    for(int i = 0; i < argc; i++){
        PyObjectContainer* t = va_arg(ap, PyObjectContainer*);
        INCREF(t);
        args[i] = t;
    }
    va_end(ap);

    PY_STD_list_CONSTRUCT(tuple, argc, args, NULL);

    return tuple;
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

// <list>.insert(<index>, <item>)
PyObjectContainer* PY_STD_list_insert(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    assert(argc == 2);

    PY_STD_list_container* list = (PY_STD_list_container*)self->raw_value;

    int64_t index = PY_unpackInteger(args[0]);
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

    // TODO: are all indices correct?
    // Copy over all data one pointer over, so we have space for the one to insert
    memcpy(list->array[index + 1], list->array[index], (list->curr_size - index) * sizeof(PyObjectContainer*));

    list->array[index] = args[1];
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

    return PY_NONE;  // TODO: raise exception?
}

void PY_STD_list_removeIndex(PY_STD_list_container* list, uint16_t index);
PyObjectContainer* PY_STD_list_remove(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    assert(argc == 1);

    PyObjectContainer* cmp = PY_getObjectAttributeByNameOrStatic(args[0], "__eq__");
    assert(cmp != NULL);

    PY_STD_list_container* list = (PY_STD_list_container*)self->raw_value;
    assert(list != NULL);

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

    assert(false);  // IndexError
}

PyObjectContainer* PY_STD_list_setAtIndex(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    assert(argc == 2);
    assert(args[0]->type == PY_TYPE_INT);
    int64_t index = *(int64_t*)args[0]->raw_value;

    PY_STD_list_container* list = (PY_STD_list_container*)self->raw_value;

    assert(index >= 0 && index < list->curr_size);

    list->array[index] = args[1];

    return PY_NONE;
}

PyObjectContainer* PY_STD_list_getAtIndex(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    assert(argc == 1);
    assert(args[0]->type == PY_TYPE_INT);
    int64_t index = *(int64_t*)args[0]->raw_value;

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
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    assert(argc == 0);
    PY_STD_list_container* list = (PY_STD_list_container*)self->raw_value;
    assert(list != NULL);

    // for (int i = 0; i < list->curr_size; i++)
    // {
    //     DECREF(list->array[i]);
    // }

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
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    assert(argc == 0);
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

    PyObjectContainer* sort_key = PY_ARGUMENT_getKeywordArgumentOrNull(argc, args, info, "key");
    // todo: use sort_key if provided

    qsort(list->array, list->curr_size, sizeof(PyObjectContainer*), PY_STD_list_sort_cmp);

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
    // __iter__
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "__bool__", PY_createBoxForFunction(PY_STD_list_toBool));
    // __iadd__
    // __add__
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "sort", PY_createBoxForFunction(PY_STD_list_sort));
    // copy
    // __sorted__
    // count
    // __contains__
    // pop
    // copy
    // __mul__
    // __imul__
    // __iter__
}