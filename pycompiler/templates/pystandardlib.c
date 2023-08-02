//
// Created by baulu on 02.08.2023.
//

#include <stdlib.h>
#include <assert.h>
#include <memory.h>
#include "pystandardlib.h"

PyObjectContainer* PY_issubclass(PyObjectContainer* self, int argc, PyObjectContainer** args)
{
    assert(argc == 2);
    assert(self == NULL);
    assert(args[0]->type == PY_TYPE_PY_TYPE);
    assert(args[1]->type == PY_TYPE_PY_TYPE);

    return PY_createBoolean(PY_isSubclassOf(args[0]->raw_value, args[1]->raw_value));
}

PyObjectContainer* PY_isinstance(PyObjectContainer* self, int argc, PyObjectContainer** args)
{
    assert(argc == 2);
    assert(self == NULL);
    assert(args[0]->type == PY_TYPE_PY_IMPL);
    assert(args[1]->type == PY_TYPE_PY_TYPE);

    return PY_createBoolean(PY_isInstanceOf(args[0], args[1]->raw_value));
}

PyClassContainer* PY_TYPE_LIST;

struct PY_STD_list_container
{
    uint16_t curr_size;
    uint16_t rem_size;
    PyObjectContainer** array;
};
typedef struct PY_STD_list_container PY_STD_list_container;

#define PY_STD_LIST_START_SIZE 4

PyObjectContainer* PY_STD_list_init(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    assert(self->raw_value == NULL);  // only one init!

    if (argc == 0)
    {
        PY_STD_list_container* list = malloc(sizeof(PY_STD_list_container));

        if (self->raw_value == NULL)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        self->raw_value = list;
        list->curr_size = 0;
        list->rem_size = PY_STD_LIST_START_SIZE;
        list->array = malloc(PY_STD_LIST_START_SIZE * sizeof(PyObjectContainer*));

        if (list->array == NULL)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        assert(false);  // not implemented todo: implement
    }

    return NULL;
}

// <list>.append(<item>)
PyObjectContainer* PY_STD_list_append(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args)
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
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        list->rem_size = list->curr_size - 1;
        list->array[list->curr_size] = args[0];
        list->curr_size++;
    }

    return PY_NONE;
}

// <list>.insert(<index>, <item>)
PyObjectContainer* PY_STD_list_insert(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args)
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
            perror("malloc");
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

PyObjectContainer* PY_STD_list_index(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    assert(argc == 1);

    PyObjectContainer* cmp = PY_getObjectAttributeByNameOrStatic(args[0], "__eq__");
    assert(cmp == NULL);

    PY_STD_list_container* list = (PY_STD_list_container*)self->raw_value;

    for (int i = 0; i < list->curr_size; i++)
    {
        PyObjectContainer* obj = list->array[i];
        PyObjectContainer* is_eq = PY_invokeBoxedMethod(cmp, args[0], 1, &obj);
        if (is_eq == PY_TRUE)
        {
            return PY_createInteger(i);
        }
    }

    return PY_NONE;  // TODO: raise exception?
}

void PY_STD_list_removeIndex(PY_STD_list_container* list, uint16_t index);
PyObjectContainer* PY_STD_list_remove(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    assert(argc == 1);

    PyObjectContainer* cmp = PY_getObjectAttributeByNameOrStatic(args[0], "__eq__");
    assert(cmp == NULL);

    PY_STD_list_container* list = (PY_STD_list_container*)self->raw_value;

    for (int i = 0; i < list->curr_size; i++)
    {
        PyObjectContainer* obj = list->array[i];
        PyObjectContainer* is_eq = PY_invokeBoxedMethod(cmp, args[0], 1, &obj);
        if (is_eq == PY_TRUE)
        {
            PY_STD_list_removeIndex(list, i);
            return PY_NONE;
        }
    }

    assert(false);  // IndexError
}

PyObjectContainer* PY_STD_list_setAtIndex(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args)
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

PyObjectContainer* PY_STD_list_getAtIndex(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args)
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

PyObjectContainer* PY_STD_list_removeAtIndex(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    assert(argc == 1);
    assert(args[0] != NULL && args[0]->type == PY_TYPE_INT);
    int64_t index = *(int64_t*)args[0]->raw_value;

    PY_STD_list_container* list = (PY_STD_list_container*)self->raw_value;

    assert(index >= 0 && index < list->curr_size);

    PY_STD_list_removeIndex(list, index);

    return PY_NONE;
}

PyObjectContainer* PY_STD_list_toBool(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args)
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

    memcpy(list->array[index + 1], list->array[index], sizeof(PyObjectContainer*) * (list->curr_size - index));
    list->array[list->curr_size] = NULL;
    list->curr_size++;
    list->rem_size++;

    // TODO: maybe release some memory?
}

static void PY_STD_initListType()
{
    PY_TYPE_LIST = PY_createClassContainer("list");
    PY_TYPE_LIST->flags |= PY_CLASS_IS_STD_IMPLEMENTED;
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "__init__", PY_createBoxForFunction(PY_STD_list_init));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "append", PY_createBoxForFunction(PY_STD_list_append));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "insert", PY_createBoxForFunction(PY_STD_list_insert));
    // extend(<array>)
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "remove", PY_createBoxForFunction(PY_STD_list_remove));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "__setitem__", PY_createBoxForFunction(PY_STD_list_setAtIndex));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "__getitem__", PY_createBoxForFunction(PY_STD_list_getAtIndex));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "__delitem__", PY_createBoxForFunction(PY_STD_list_removeAtIndex));
    // clear()
    // ==
    // !=
    // __len__
    // __iter__
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "__bool__", PY_createBoxForFunction(PY_STD_list_toBool));
    // __iadd__
    // __add__
}

static bool STD_IS_INITIALISED = false;

void PY_STD_INIT()
{
    if (STD_IS_INITIALISED)
    {
        return;
    }

    STD_IS_INITIALISED = true;

    initialize();
    PY_STD_initListType();
}
