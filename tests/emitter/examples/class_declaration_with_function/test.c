#include <assert.h>
#include <string.h>
#include "pyinclude.h"

extern PyClassContainer* PY_CLASS_test_4;


int _initialise();
void PY_CLASS_INIT_PY_CLASS_test_4();
PyObjectContainer* target_1(PyObjectContainer* self_0);
PyObjectContainer* target_1_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info);
PyObjectContainer* testtarget_3(PyObjectContainer* self_2);
PyObjectContainer* testtarget_3_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info);


int main()
{
    _initialise();

    assert(PY_CLASS_test_4 != NULL);
    PyObjectContainer* obj = PY_createClassInstance(PY_CLASS_test_4);
    assert(obj != NULL);
    PyObjectContainer* func = PY_getObjectAttributeByNameOrStatic(obj, "test_target");
    assert(func != NULL);

    PyObjectContainer* result = PY_invokeBoxedMethod(func, NULL, 0, NULL, NULL);
    assert(result != NULL);

    assert(PY_unpackInteger(result) == 10);
}

