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
PyObjectContainer* function_container_test_0;



// implementations

PyObjectContainer* PY_MODULE_source_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_MODULE_INSTANCE_source = PY_createModuleObject("source");
    #endif
    function_container_test_0 = PY_createBoxForFunction(test_0_safeWrap);
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "test", (function_container_test_0 = PY_createBoxForFunction(test_0_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_exposeModuleObject(PY_MODULE_INSTANCE_source);
    #endif
}

PyObjectContainer* test_0(void) {
    // Source Location: .test
    PyObjectContainer* obj_1;

    PyObjectContainer* obj_instance_1 = PY_createClassInstance(PY_TYPE_DICT);
    PY_CHECK_EXCEPTION(PY_STD_dict_init_fast_arg_zero(obj_instance_1));

    obj_1 = obj_instance_1;

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (obj_1 , PY_createString("test") , PY_createInteger(10)));

    PyObjectContainer* assert_target_3 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (obj_1 , PY_createString("test"))), PY_createInteger(10)));
    assert(PY_getTruthValueOf(assert_target_3));

    PyObjectContainer* assert_target_4 = PY_CHECK_EXCEPTION(PY_STD_operator_contains(obj_1, PY_createString("test")));
    assert(PY_getTruthValueOf(assert_target_4));


    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (obj_1 , PY_createString("test") , PY_createInteger(20)));

    PyObjectContainer* assert_target_5 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (obj_1 , PY_createString("test"))), PY_createInteger(20)));
    assert(PY_getTruthValueOf(assert_target_5));

    PyObjectContainer* assert_target_6 = PY_CHECK_EXCEPTION(PY_STD_operator_contains(obj_1, PY_createString("test")));
    assert(PY_getTruthValueOf(assert_target_6));


    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (obj_1 , PY_createString("other") , PY_createInteger(5)));

    PyObjectContainer* assert_target_7 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (obj_1 , PY_createString("other"))), PY_createInteger(5)));
    assert(PY_getTruthValueOf(assert_target_7));


    PyObjectContainer* assert_target_8 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_dict_get_fast_arg_1 (obj_1 , PY_createString("test"))), PY_createInteger(20)));
    assert(PY_getTruthValueOf(assert_target_8));

    PyObjectContainer* assert_target_9 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_dict_get_fast_arg_2 (obj_1 , PY_createString("test") , PY_createInteger(10))), PY_createInteger(20)));
    assert(PY_getTruthValueOf(assert_target_9));

    PyObjectContainer* assert_target_10 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_dict_get_fast_arg_2 (obj_1 , PY_createString("test 2") , PY_createInteger(10))), PY_createInteger(10)));
    assert(PY_getTruthValueOf(assert_target_10));


    obj_1 = PY_STD_dict_CREATE(1, PY_createString("test"), PY_createInteger(30));

    PyObjectContainer* assert_target_11 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_dict_get_fast_arg_1 (obj_1 , PY_createString("test"))), PY_createInteger(30)));
    assert(PY_getTruthValueOf(assert_target_11));

    PyObjectContainer* assert_target_12 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_dict_get_fast_arg_2 (obj_1 , PY_createString("test") , PY_createInteger(10))), PY_createInteger(30)));
    assert(PY_getTruthValueOf(assert_target_12));

    PyObjectContainer* assert_target_13 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_dict_get_fast_arg_2 (obj_1 , PY_createString("test 2") , PY_createInteger(10))), PY_createInteger(10)));
    assert(PY_getTruthValueOf(assert_target_13));
    return PY_NONE;
}

PyObjectContainer* test_0_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return test_0();
}

