//
// Created by baulu on 15.09.2023.
//

#include <stdlib.h>
#include "pyinclude.h"
#include "standard_library/list.h"
#include "standard_library/generator.h"
#include "standard_library/importhelper.h"
#include "standard_library/exceptions.h"
#include "itertools.h"

PyObjectContainer* PY_MODULE_INSTANCE_itertools;

PyObjectContainer* PY_MODULE_itertools_chain_next(PyGeneratorContainer* generator)
{
    head:;
    if (generator->locals[generator->section_id] == NULL)
    {
        return NULL;
    }

    PyObjectContainer* value = PY_STD_GENERATOR_next_fast_arg_1(generator->locals[generator->section_id], NULL);

    if (value == NULL)
    {
        generator->section_id++;
        goto head;
    }

    return value;
}

PyObjectContainer* PY_MODULE_itertools_chain(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    PyObjectContainer** persistent_args = malloc((argc + 1) * sizeof(PyObjectContainer*));
    for (int i = 0; i < argc; i++)
    {
        persistent_args[i] = PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(args[i], "__iter__"), args[i], 0, NULL, NULL));
        assert(persistent_args[i] != NULL);
    }
    persistent_args[argc] = NULL;

    PyObjectContainer* generator = PY_STD_GENERATOR_create(0);
    PyGeneratorContainer* container = generator->raw_value;
    container->locals = persistent_args;  // this is the simplest variant, each local entry
    container->section_id = 0;
    container->next_section = PY_MODULE_itertools_chain_next;
    return generator;
}

PyObjectContainer* PY_MODULE_itertools_init(void)
{
    INVOKE_SINGLE();

    PY_MODULE_INSTANCE_itertools = PY_createModuleObject("unittest");

    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_itertools, "chain", PY_createBoxForFunction(PY_MODULE_itertools_chain));

    return PY_NONE;
}
