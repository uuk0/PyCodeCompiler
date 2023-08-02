#include <assert.h>
#include "pyinclude.h"


int _initialise();
PyObjectContainer* test_5();


int main()
{
    _initialise();
    assert(PY_unpackInteger(test_5()) == 10);
}