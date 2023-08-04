#include <assert.h>
#include "pyinclude.h"


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
    assert(PY_unpackInteger(testone_0()) == 610);
    assert(PY_unpackInteger(testtwo_1()) == 590);
    assert(PY_unpackInteger(testthree_2()) == 5);
    assert(PY_unpackInteger(testfour_3()) == 3);
}