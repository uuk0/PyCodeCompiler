//
// Created by baulu on 08.09.2023.
//

#include <assert.h>
#include "generator.h"
#include "exceptions.h"

PyClassContainer* PY_TYPE_GENERATOR;

PyObjectContainer* PY_STD_GENERATOR_create(uint16_t local_count)
{
    PyObjectContainer* container = PY_createClassInstance(PY_TYPE_GENERATOR);
    PyGeneratorContainer* generator = malloc(sizeof(PyGeneratorContainer));
    if (generator == NULL)
    {
        perror("malloc PY_STD_GENERATOR_createGeneratorFromFunction generator-container");
        exit(EXIT_FAILURE);
    }
    container->raw_value = generator;
    generator->next_section = NULL;
    generator->locals = malloc(local_count * sizeof(PyObjectContainer*));
    if (generator->locals == NULL)
    {
        perror("malloc PY_STD_GENERATOR_createGeneratorFromFunction locals");
        exit(EXIT_FAILURE);
    }
    return container;
}

PyObjectContainer* PY_STD_GENERATOR_next(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    if (argc == 0)
    {
        return PY_STD_GENERATOR_next_fast_arg_0(self);
    }

    assert(argc <= 1);
    return PY_STD_GENERATOR_next_fast_arg_1(self, args[0]);
}

PyObjectContainer* PY_STD_GENERATOR_next_fast_arg_0(PyObjectContainer* self)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL && self->py_type == PY_TYPE_GENERATOR);

    PyGeneratorContainer* container = self->raw_value;

    if (container->next_section == NULL)
    {
        PY_THROW_EXCEPTION_WITH_MESSAGE(NULL, "generator exhausted");
    }

    return container->next_section(container);
}

PyObjectContainer* PY_STD_GENERATOR_next_fast_arg_1(PyObjectContainer* self, PyObjectContainer* default_value)
{
    assert(self != NULL);
    assert(self->type == PY_TYPE_PY_IMPL && self->py_type == PY_TYPE_GENERATOR);

    PyGeneratorContainer* container = self->raw_value;

    if (container->next_section == NULL)
    {
        return default_value;
    }

    PyObjectContainer* result = container->next_section(container);
    return result != NULL ? result : default_value;
}

void PY_STD_initGeneratorType(void)
{
    PY_TYPE_GENERATOR = PY_createClassContainer("<generator>");
    PY_setClassAttributeByNameOrCreate(PY_TYPE_GENERATOR, "__next__", PY_createBoxForFunction(PY_STD_GENERATOR_next));
}

