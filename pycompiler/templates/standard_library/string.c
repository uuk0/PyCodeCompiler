//
// Created by baulu on 05.09.2023.
//

#include <string.h>
#include "string.h"
#include "helpers/hashmap.h"

PyObjectContainer* PY_STD_string_hash_CONTAINER;
PyObjectContainer* PY_STD_string_hash(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 0);
    assert(self != NULL);
    assert(self->type == PY_TYPE_STRING);
    assert(self->raw_value != NULL);

    return PY_createInteger(HASH_string(self->raw_value));
}

PyObjectContainer* PY_STD_string_eq_CONTAINER;
PyObjectContainer* PY_STD_string_eq(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 1);
    assert(self != NULL);
    return PY_STD_string_eq_fast(self, args[0]);
}

PyObjectContainer* PY_STD_string_eq_fast(PyObjectContainer* lhs, PyObjectContainer* rhs)
{
    assert(lhs != NULL);
    assert(lhs->type == PY_TYPE_STRING);
    assert(rhs->raw_value != NULL);
    assert(rhs != NULL);

    if (rhs->type != PY_TYPE_STRING || rhs->raw_value == NULL)
    {
        return PY_FALSE;
    }

    return strcmp(PY_unpackString(lhs), PY_unpackString(rhs)) == 0 ? PY_TRUE : PY_FALSE;
}

void PY_STD_initStringType(void)
{
    PY_STD_string_hash_CONTAINER = PY_createBoxForFunction(PY_STD_string_hash);
    PY_STD_string_eq_CONTAINER = PY_createBoxForFunction(PY_STD_string_eq);
}
