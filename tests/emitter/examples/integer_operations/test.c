#include <assert.h>
#include "pyinclude.h"
#include "standard_library/exceptions.h"
#include "source.h"


int main()
{
    PY_MODULE_source_init();
    assert(PY_unpackInteger(PY_CHECK_EXCEPTION_AND_EXIT_WITH_MESSAGE(testone_0(), "0")) == 610);
    assert(PY_unpackInteger(PY_CHECK_EXCEPTION_AND_EXIT_WITH_MESSAGE(testtwo_1(), "1")) == 590);
    assert(PY_unpackInteger(PY_CHECK_EXCEPTION_AND_EXIT_WITH_MESSAGE(testthree_2(), "2")) == 5);
    assert(PY_unpackInteger(PY_CHECK_EXCEPTION_AND_EXIT_WITH_MESSAGE(testfour_3(), "3")) == 3);
}