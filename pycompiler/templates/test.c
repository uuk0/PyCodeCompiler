//
// Created by baulu on 01.08.2023.
//
#include <stdlib.h>
#include <assert.h>

#include "pyinclude.h"

PyObjectContainer* test(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args)
{
    return PY_createInteger(10);
}

int main()
{
    PyClassContainer* cls = PY_createClassContainer("test");
    PY_setClassAttributeByNameOrCreate(cls, "test", PY_createBoxForFunction(test));

    PyObjectContainer* obj = PY_createClassInstance(cls);
    PyObjectContainer* func = PY_getObjectAttributeByNameOrStatic(obj, "test");
    PyObjectContainer* value = PY_invokeBoxedMethod(func, NULL, 0, NULL);
    int64_t unboxed_value = PY_unpackInteger(value);
    assert(unboxed_value == 10);
}
