#include <stdlib.h>

#include "pyinclude.h"
#include "standard_library/init.h"
#include "standard_library/exceptions.h"
#include "standard_library/importhelper.h"

// code compiled from python to c via PyCodeCompiler

#include <assert.h>


void PY_MODULE_source_init();
PyObjectContainer* testone_0();
PyObjectContainer* testone_0_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info);
PyObjectContainer* testtwo_1();
PyObjectContainer* testtwo_1_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info);
PyObjectContainer* testthree_2();
PyObjectContainer* testthree_2_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info);
PyObjectContainer* testfour_3();
PyObjectContainer* testfour_3_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info);


// implementations

void PY_MODULE_source_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
}

PyObjectContainer* testone_0(void) {
    return PY_STD_operator_add(PY_createInteger(10), PY_STD_operator_mul(PY_createInteger(20), PY_createInteger(30)));



    return PY_NONE;
}

PyObjectContainer* testone_0_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return testone_0();
}

PyObjectContainer* testtwo_1(void) {
    return PY_STD_operator_sub(PY_STD_operator_mul(PY_createInteger(20), PY_createInteger(30)), PY_createInteger(10));



    return PY_NONE;
}

PyObjectContainer* testtwo_1_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return testtwo_1();
}

PyObjectContainer* testthree_2(void) {
    return PY_STD_operator_floordiv(PY_createInteger(10), PY_createInteger(2));



    return PY_NONE;
}

PyObjectContainer* testthree_2_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return testthree_2();
}

PyObjectContainer* testfour_3(void) {
    return PY_STD_operator_floordiv(PY_createInteger(10), PY_createInteger(3));
}

PyObjectContainer* testfour_3_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return testfour_3();
}

