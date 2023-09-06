#include <assert.h>
#include "pyinclude.h"
#include "standard_library/exceptions.h"


int _initialise();
PyObjectContainer* test_0();


int main()
{
    _initialise();
    PY_CHECK_EXCEPTION_AND_EXIT(test_0());
}