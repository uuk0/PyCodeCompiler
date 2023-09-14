#include <assert.h>
#include "pyinclude.h"
#include "source.h"


int main()
{
    PY_MODULE_source_init();
    assert(PY_unpackInteger(test_1(PY_createInteger(0))) == 1);
    assert(PY_unpackInteger(test_1(PY_createInteger(1))) == 2);
    assert(PY_unpackInteger(test_1(PY_createInteger(2))) == 3);
    assert(PY_unpackInteger(test_1(PY_createInteger(6))) == 3);
    assert(PY_unpackInteger(test_1(PY_createInteger(-2))) == 3);
}