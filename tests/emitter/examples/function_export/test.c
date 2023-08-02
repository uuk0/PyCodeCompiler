#include <assert.h>
#include "pyinclude.h"


PyObjectContainer* test_0();


int main()
{
    assert(PY_unpackInteger(test_0()) == 10);
}