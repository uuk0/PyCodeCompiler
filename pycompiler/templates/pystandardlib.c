//
// Created by baulu on 02.08.2023.
//

#include <stdlib.h>
#include <assert.h>
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

PyObjectContainer* PY_STD_list_append(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_LIST);
    assert(argc == 1);
    assert(self != NULL);

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

static void PY_STD_initListType()
{
    PY_TYPE_LIST = PY_createClassContainer("list");
    PY_TYPE_LIST->flags |= PY_CLASS_IS_STD_IMPLEMENTED;
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "__init__", PY_createBoxForFunction(PY_STD_list_init));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_LIST, "append", PY_createBoxForFunction(PY_STD_list_append));
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
