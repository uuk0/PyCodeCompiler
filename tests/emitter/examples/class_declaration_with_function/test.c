#include <assert.h>
#include <string.h>
#include "pyinclude.h"

extern PyClassContainer* PY_CLASS_test;


int _initialise();
void PY_CLASS_INIT_PY_CLASS_test();
PyObjectContainer* target(PyObjectContainer* self);
PyObjectContainer* test_target(PyObjectContainer* self);
PyObjectContainer* test_target_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args);
PyObjectContainer* target_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args);


int main()
{
    _initialise();

    assert(PY_CLASS_test != NULL);
    PyObjectContainer* obj = PY_createClassInstance(PY_CLASS_test);
    assert(obj != NULL);
    PyObjectContainer* func = PY_getObjectAttributeByNameOrStatic(obj, "test_target");
    assert(func != NULL);

    PyObjectContainer* result = PY_invokeBoxedMethod(func, NULL, 0, NULL);
    assert(result != NULL);

    assert(PY_unpackInteger(result) == 10);
}

