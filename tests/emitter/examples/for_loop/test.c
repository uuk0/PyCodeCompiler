#include <assert.h>
#include "pyinclude.h"
#include "standard_library/exceptions.h"
#include "source.h"


int main()
{
    PyObjectContainer* result;

    PY_MODULE_source_init();

    result = PY_CHECK_EXCEPTION_AND_EXIT(test_0());
    assert(PY_unpackInteger(result) == 6);

    result = PY_CHECK_EXCEPTION_AND_EXIT(test2_1());
    assert(PY_unpackInteger(result) == 1);
}