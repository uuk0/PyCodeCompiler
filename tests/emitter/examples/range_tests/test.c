#include <assert.h>
#include "pyinclude.h"
#include "source.h"


int main()
{
    PY_MODULE_source_init();
    assert(PY_unpackInteger(test_0()) == 0 + 1 + 2 + 3);
}