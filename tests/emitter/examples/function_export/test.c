#include <assert.h>
#include "pyinclude.h"


PyObjectContainer* test();


int main()
{
    assert(PY_unpackInteger(test()) == 10);
}