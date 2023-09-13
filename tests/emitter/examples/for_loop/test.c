#include <assert.h>
#include "pyinclude.h"
#include "standard_library/exceptions.h"
#include "source.h"


int main()
{
    PY_MODULE_source_init();
    PyObjectContainer* result = PY_CHECK_EXCEPTION_AND_EXIT(test_0());
    assert(PY_unpackInteger(result) == 6);
}