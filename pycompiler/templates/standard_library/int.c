//
// Created by baulu on 03.08.2023.
//

#include <stdlib.h>
#include <assert.h>

#include "int.h"
#include "pyinclude.h"


PyObjectContainer* PY_builtin_int_compare(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 1);
    // TODO: do float check!
    if (args[0]->type != PY_TYPE_INT)
    {
        return PY_FALSE;
    }

    if (*(int64_t*)self->raw_value == *(int64_t*)args[0]->raw_value)
    {
        return PY_TRUE;
    }
    return PY_FALSE;
}

void PY_STD_initIntType(void)
{
    PY_builtin_int_compare_container = PY_createBoxForFunction(PY_builtin_int_compare);
}
