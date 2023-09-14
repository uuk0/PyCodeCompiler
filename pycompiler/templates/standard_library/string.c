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

PyObjectContainer* PY_STD_string_startswith(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 1);
    return PY_STD_string_startswith_fast(self, args[0]);
}

PyObjectContainer* PY_STD_string_startswith_fast(PyObjectContainer* self, PyObjectContainer* other)
{
    return PY_createBoolean(PY_STD_string_startswith_impl(PY_unpackString(self), PY_unpackString(other)));
}

bool PY_STD_string_startswith_impl(char* self, char* other)
{
    if (strlen(self) < strlen(other)) return false;

    for (int i = 0; i < strlen(other); i++)
    {
        if (self[i] != other[i])
        {
            return false;
        }
    }
    return true;
}

void PY_STD_initStringType(void)
{
    PY_STD_string_hash_CONTAINER = PY_createBoxForFunction(PY_STD_string_hash);
    PY_STD_string_eq_CONTAINER = PY_createBoxForFunction(PY_STD_string_eq);
}
