//
// Created by baulu on 05.09.2023.
//

#include "string.h"
#include "helpers/hashmap.h"

PyObjectContainer* PY_STD_string_hash_CONTAINER;
PyObjectContainer* PY_STD_string_hash(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 0);
    assert(self->type == PY_TYPE_STRING);
    assert(self->raw_value != NULL);

    return PY_createInteger(HASH_string(self->raw_value));
}

void PY_STD_initStringType(void)
{
    PY_STD_string_hash_CONTAINER = PY_createBoxForFunction(PY_STD_string_hash);
}
