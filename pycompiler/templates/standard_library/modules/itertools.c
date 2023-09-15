//
// Created by baulu on 15.09.2023.
//

#include <stdlib.h>
#include "pyinclude.h"
#include "standard_library/list.h"
#include "standard_library/generator.h"
#include "standard_library/importhelper.h"
#include "itertools.h"

PyObjectContainer* PY_MODULE_INSTANCE_itertools;

PyObjectContainer* PY_MODULE_itertools_chain(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    return PY_NONE;
}

PyObjectContainer* PY_MODULE_itertools_init(void)
{
    INVOKE_SINGLE();

    PY_MODULE_INSTANCE_itertools = PY_createModuleObject("unittest");

    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_itertools, "chain", PY_createBoxForFunction(PY_MODULE_itertools_chain));

    return PY_NONE;
}
