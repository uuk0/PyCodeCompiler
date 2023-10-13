#include <stdlib.h>

#include "pyinclude.h"
#include "standard_library/config.h"

#include "standard_library/init.h"
#include "standard_library/exceptions.h"

#ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
#include "standard_library/importhelper.h"
#endif

#include "source.h"

#ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
PyObjectContainer* PY_MODULE_INSTANCE_source;
#endif

// code compiled from python to c via PyCodeCompiler

#include <assert.h>



// Global Variables
PyObjectContainer* function_container_test_one_0;
PyObjectContainer* function_container_test_two_1;
PyObjectContainer* function_container_test_three_2;
PyObjectContainer* function_container_test_four_3;



// implementations

PyObjectContainer* PY_MODULE_source_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_MODULE_INSTANCE_source = PY_createModuleObject("source");
    #endif
    function_container_test_one_0 = PY_createBoxForFunction(testone_0_safeWrap);
    function_container_test_two_1 = PY_createBoxForFunction(testtwo_1_safeWrap);
    function_container_test_three_2 = PY_createBoxForFunction(testthree_2_safeWrap);
    function_container_test_four_3 = PY_createBoxForFunction(testfour_3_safeWrap);
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "test_one", (function_container_test_one_0 = PY_createBoxForFunction(testone_0_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "test_two", (function_container_test_two_1 = PY_createBoxForFunction(testtwo_1_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "test_three", (function_container_test_three_2 = PY_createBoxForFunction(testthree_2_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "test_four", (function_container_test_four_3 = PY_createBoxForFunction(testfour_3_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_exposeModuleObject(PY_MODULE_INSTANCE_source);
    #endif
}

PyObjectContainer* testone_0(void) {
    // Source Location: .test_one

    return PY_STD_operator_add(PY_createInteger(10), PY_STD_operator_mul(PY_createInteger(20), PY_createInteger(30)));



    return PY_NONE;
}

PyObjectContainer* testone_0_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return testone_0();
}

PyObjectContainer* testtwo_1(void) {
    // Source Location: .test_two

    return PY_STD_operator_sub(PY_STD_operator_mul(PY_createInteger(20), PY_createInteger(30)), PY_createInteger(10));



    return PY_NONE;
}

PyObjectContainer* testtwo_1_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return testtwo_1();
}

PyObjectContainer* testthree_2(void) {
    // Source Location: .test_three

    return PY_STD_operator_floordiv(PY_createInteger(10), PY_createInteger(2));



    return PY_NONE;
}

PyObjectContainer* testthree_2_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return testthree_2();
}

PyObjectContainer* testfour_3(void) {
    // Source Location: .test_four

    return PY_STD_operator_floordiv(PY_createInteger(10), PY_createInteger(3));
}

PyObjectContainer* testfour_3_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return testfour_3();
}

