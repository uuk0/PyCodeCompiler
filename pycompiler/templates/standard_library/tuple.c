//
// Created by baulu on 03.08.2023.
//

#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <memory.h>
#include <stdarg.h>
#include "tuple.h"
#include "config.h"

#ifdef PY_ENABLE_GENERATORS
#include "generator.h"
#endif

PyClassContainer* PY_TYPE_TUPLE;

struct PY_STD_tuple_container
{
    uint16_t curr_size;
    PyObjectContainer** array;
};
typedef struct PY_STD_tuple_container PY_STD_tuple_container;

#define PY_STD_TUPLE_START_SIZE 4


PyObjectContainer* PY_STD_tuple_init(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_TUPLE);
    assert(self->raw_value == NULL);
    PY_STD_tuple_container* container = malloc(sizeof(PY_STD_tuple_container));
    if (container == NULL)
    {
        perror("malloc PY_STD_tuple_init");
        exit(EXIT_FAILURE);
    }
    self->raw_value = container;

    if (argc == 0)
    {
        container->curr_size = 0;
        container->array = NULL;
    }
    else if (argc == 1)
    {
        // TODO: use __iter__ on parameter and build with that the tuple!
        assert(false == "not implemented");
    }
    else
    {
        assert(false == "invalid parameter count");
    }

    return NULL;
}

/*
 * Construct a tuple from an array of objects
 * Not directly exposed as a python function, but acts like
 * the (...) expression
 * */
PyObjectContainer* PY_STD_tuple_CONSTRUCT(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_TUPLE);
    assert(self->raw_value == NULL);
    PY_STD_tuple_container* container = malloc(sizeof(PY_STD_tuple_container));
    if (container == NULL)
    {
        perror("malloc PY_STD_tuple_CONSTRUCT A");
        exit(EXIT_FAILURE);
    }
    self->raw_value = container;
    container->curr_size = argc;
    container->array = malloc(argc * sizeof(PyObjectContainer*));
    if (container->array == NULL)
    {
        perror("malloc PY_STD_tuple_CONSTRUCT B");
        exit(EXIT_FAILURE);
    }
    memcpy(container->array, args, argc * sizeof(PyObjectContainer*));

    return self;
}


PyObjectContainer* PY_STD_tuple_CREATE(uint8_t argc, ...)
{
    PyObjectContainer* tuple = PY_createClassInstance(PY_TYPE_TUPLE);

    va_list ap;
    PyObjectContainer* args[argc];
    va_start(ap, argc);
    for(int i = 0; i < argc; i++){
        PyObjectContainer* t = va_arg(ap, PyObjectContainer*);
        INCREF(t);
        args[i] = t;
    }
    va_end(ap);

    PY_STD_tuple_CONSTRUCT(tuple, argc, args, NULL);

    return tuple;
}


PyObjectContainer* PY_STD_tuple_index(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_TUPLE);
    assert(argc == 1);

    PyObjectContainer* cmp = PY_getObjectAttributeByNameOrStatic(args[0], "__eq__");
    assert(cmp != NULL);

    PY_STD_tuple_container* tuple = (PY_STD_tuple_container*)self->raw_value;

    for (int i = 0; i < tuple->curr_size; i++)
    {
        PyObjectContainer* obj = tuple->array[i];
        PyObjectContainer* is_eq = PY_invokeBoxedMethod(cmp, args[0], 1, &obj, NULL);
        if (is_eq == PY_TRUE)
        {
            return PY_createInteger(i);
        }
    }

    return PY_NONE;  // TODO: raise exception?
}

PyObjectContainer* PY_STD_tuple_getAtIndex(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_TUPLE);
    assert(argc == 1);
    assert(args[0]->type == PY_TYPE_INT);
    int64_t index = *(int64_t*)args[0]->raw_value;

    PY_STD_tuple_container* tuple = (PY_STD_tuple_container*)self->raw_value;

    assert(index >= 0 && index < tuple->curr_size);

    return tuple->array[index];
}


PyObjectContainer* PY_STD_tuple_toBool(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_TUPLE);
    assert(argc == 0);

    PY_STD_tuple_container* tuple = (PY_STD_tuple_container*)self->raw_value;

    if (tuple->curr_size == 0)
    {
        return PY_FALSE;
    }
    return PY_TRUE;
}

#ifdef PY_ENABLE_GENERATORS
PyObjectContainer* PY_STD_tuple_iterator(PyGeneratorContainer* generator)
{
    PyObjectContainer* self = generator->locals[0];
    PY_STD_tuple_container* list = (PY_STD_tuple_container*)self->raw_value;
    if (generator->section_id >= list->curr_size)
    {
        return NULL;
    }
    return list->array[generator->section_id++];
}
#endif

PyObjectContainer* PY_STD_tuple_iter(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 0);
    return PY_STD_tuple_iter_fast(self);
}

PyObjectContainer* PY_STD_tuple_iter_fast(PyObjectContainer* self)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL);
    assert(self->py_type == PY_TYPE_TUPLE);

    PyObjectContainer* generator = PY_STD_GENERATOR_create(1);
    PyGeneratorContainer* container = generator->raw_value;
    container->section_id = 0;
    container->locals[0] = self;
    container->next_section = PY_STD_tuple_iterator;
    return generator;
}


void PY_STD_initTupleType(void)
{
    PY_TYPE_TUPLE = PY_createClassContainer("tuple");
    PY_TYPE_TUPLE->flags |= PY_CLASS_IS_STD_IMPLEMENTED;
    PY_setClassAttributeByNameOrCreate(PY_TYPE_TUPLE, "__init__", PY_createBoxForFunction(PY_STD_tuple_init));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_TUPLE, "index", PY_createBoxForFunction(PY_STD_tuple_index));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_TUPLE, "__getitem__", PY_createBoxForFunction(PY_STD_tuple_getAtIndex));
    // __eq__
    // __len__
#ifdef PY_ENABLE_GENERATORS
    PY_setClassAttributeByNameOrCreate(PY_TYPE_TUPLE, "__iter__", PY_createBoxForFunction(PY_STD_tuple_iter));
#endif
    PY_setClassAttributeByNameOrCreate(PY_TYPE_TUPLE, "__bool__", PY_createBoxForFunction(PY_STD_tuple_toBool));
    // __iadd__
    // __add__
    // __hash__
    // count
    // __contains__
    // __mul__
    // __imul__
    // __iter__
}

