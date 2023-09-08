#include <assert.h>
#include <string.h>
#include "pyinclude.h"
#include "source.h"


int main()
{
    PY_MODULE_source_init();

    assert(PY_CLASS_test_4 != NULL);
    PyObjectContainer* obj = PY_createClassInstance(PY_CLASS_test_4);
    assert(obj != NULL);
    PyObjectContainer* func = PY_getObjectAttributeByNameOrStatic(obj, "test_target");
    assert(func != NULL);

    PyObjectContainer* result = PY_invokeBoxedMethod(func, NULL, 0, NULL, NULL);
    assert(result != NULL);

    assert(PY_unpackInteger(result) == 10);
}

