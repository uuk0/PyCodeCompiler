#include <assert.h>
#include "pyinclude.h"


int _initialise();
PyObjectContainer* test_0();


int main()
{
    _initialise();
    assert(test_0() == PY_NONE);
}