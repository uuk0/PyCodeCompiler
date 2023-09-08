#include <stdlib.h>

#include "pyinclude.h"
#include "standard_library/init.h"
#include "standard_library/exceptions.h"
#include "standard_library/importhelper.h"

#include "source.h"

PyObjectContainer* PY_MODULE_INSTANCE_source;

// code compiled from python to c via PyCodeCompiler

#include <assert.h>




// implementations

void PY_MODULE_source_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    PY_MODULE_INSTANCE_source = PY_createModuleObject("source");




    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "test_one", PY_createBoxForFunction(testone_0_safeWrap));
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "test_two", PY_createBoxForFunction(testtwo_1_safeWrap));
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "test_three", PY_createBoxForFunction(testthree_2_safeWrap));
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "test_four", PY_createBoxForFunction(testfour_3_safeWrap));
    PY_exposeModuleObject(PY_MODULE_INSTANCE_source);
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

