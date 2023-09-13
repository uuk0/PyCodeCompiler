//
// Created by baulu on 08.09.2023.
//

#include <assert.h>
#include "generator.h"
#include "exceptions.h"
#include "config.h"

PyClassContainer* PY_TYPE_GENERATOR;

PyObjectContainer* PY_STD_GENERATOR_create(uint16_t local_count)
{
#ifndef PY_ENABLE_GENERATORS
    assert(0 && "generators are not enabled!");
#endif

    PyObjectContainer* container = PY_createClassInstance(PY_TYPE_GENERATOR);
    PyGeneratorContainer* generator = malloc(sizeof(PyGeneratorContainer));
    if (generator == NULL)
    {
        perror("malloc PY_STD_GENERATOR_createGeneratorFromFunction generator-container");
        exit(EXIT_FAILURE);
    }
    container->raw_value = generator;
    generator->next_section = NULL;
    generator->locals = calloc(local_count, sizeof(PyObjectContainer*));
    generator->section_id = 0;
    if (generator->locals == NULL)
    {
        perror("malloc PY_STD_GENERATOR_createGeneratorFromFunction locals");
        exit(EXIT_FAILURE);
    }
    return container;
}

PyObjectContainer* PY_STD_GENERATOR_next(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
#ifndef PY_ENABLE_GENERATORS
    assert(0 && "generators are not enabled!");
#endif

    if (argc == 0)
    {
        return PY_STD_GENERATOR_next_fast_arg_0(self);
    }

    assert(argc <= 1);
    return PY_STD_GENERATOR_next_fast_arg_1(self, args[0]);
}

PyObjectContainer* PY_STD_GENERATOR_next_fast_arg_0(PyObjectContainer* self)
{
#ifndef PY_ENABLE_GENERATORS
    assert(0 && "generators are not enabled!");
#endif

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
#ifndef PY_ENABLE_GENERATORS
    assert(0 && "generators are not enabled!");
#endif

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

PyObjectContainer* PY_STD_GENERATOR_iter(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
#ifndef PY_ENABLE_GENERATORS
    assert(0 && "generators are not enabled!");
#endif
    assert(self != NULL);
    if (!(self->type == PY_TYPE_PY_IMPL && self->py_type == PY_TYPE_GENERATOR))
    {
        printf("%s\n", PY_getObjectClassName(self));
        PY_THROW_EXCEPTION_WITH_MESSAGE(NULL, "argument is not a generator!");
    }
    return self;
}

PyObjectContainer* PY_STD_NEXT_FORWARD_arg_0(PyObjectContainer* self)
{
    assert(self != NULL);
    PyObjectContainer* method = PY_getObjectAttributeByNameOrStatic(self, "__next__");
    assert(method != NULL);
    return PY_invokeBoxedMethod(method, self, 0, NULL, NULL);
}

PyObjectContainer* PY_STD_NEXT_FORWARD_arg_1(PyObjectContainer* self, PyObjectContainer* default_value)
{
    assert(self != NULL);
    PyObjectContainer* method = PY_getObjectAttributeByNameOrStatic(self, "__next__");
    if (method == NULL)
    {
        printf("Data type: %s\n", PY_getObjectClassName(self));
        PY_THROW_EXCEPTION_WITH_MESSAGE(NULL, "could not get '__next__'");
    }
    return PY_invokeBoxedMethod(method, self, 1, &default_value, NULL);
}

void PY_STD_initGeneratorType(void)
{
    PY_TYPE_GENERATOR = PY_createClassContainer("<generator>");
    PY_setClassAttributeByNameOrCreate(PY_TYPE_GENERATOR, "__next__", PY_createBoxForFunction(PY_STD_GENERATOR_next));
    PY_setClassAttributeByNameOrCreate(PY_TYPE_GENERATOR, "__iter__", PY_createBoxForFunction(PY_STD_GENERATOR_iter));
}

