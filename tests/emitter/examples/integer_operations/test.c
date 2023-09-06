#include <assert.h>
#include "pyinclude.h"
#include "standard_library/exceptions.h"


int _initialise();
PyObjectContainer* testone_0();
PyObjectContainer* testone_0_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info);
PyObjectContainer* testtwo_1();
PyObjectContainer* testtwo_1_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info);
PyObjectContainer* testthree_2();
PyObjectContainer* testthree_2_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info);
PyObjectContainer* testfour_3();
PyObjectContainer* testfour_3_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info);


int main()
{
    _initialise();
    assert(PY_unpackInteger(PY_CHECK_EXCEPTION_AND_EXIT_WITH_MESSAGE(testone_0(), "0")) == 610);
    assert(PY_unpackInteger(PY_CHECK_EXCEPTION_AND_EXIT_WITH_MESSAGE(testtwo_1(), "1")) == 590);
    assert(PY_unpackInteger(PY_CHECK_EXCEPTION_AND_EXIT_WITH_MESSAGE(testthree_2(), "2")) == 5);
    assert(PY_unpackInteger(PY_CHECK_EXCEPTION_AND_EXIT_WITH_MESSAGE(testfour_3(), "3")) == 3);
}