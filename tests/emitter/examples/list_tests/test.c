#include <assert.h>
#include "pyinclude.h"
#include "source.h"


int main()
{
    PY_MODULE_source_init();
    assert(test_0() == PY_NONE);
}