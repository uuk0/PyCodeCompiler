#include <stdlib.h>

#include "pyinclude.h"
#include "standard_library/init.h"
#include "standard_library/exceptions.h"
#include "standard_library/importhelper.h"

// code compiled from python to c via PyCodeCompiler

#include <assert.h>


void PY_MODULE_source_init();
PyObjectContainer* test_0();
PyObjectContainer* test_0_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info);


// implementations

void PY_MODULE_source_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
}

PyObjectContainer* test_0(void) {
    PyObjectContainer* obj_1;

    PyObjectContainer* obj_instance_0 = PY_createClassInstance(PY_TYPE_LIST);
    PY_CHECK_EXCEPTION(PY_STD_list_init_fast_arg_0(obj_instance_0));

    obj_1 = obj_instance_0;

    PY_CHECK_EXCEPTION(PY_STD_list_append_fast (obj_1 , PY_createInteger(10)));

    PY_CHECK_EXCEPTION(PY_STD_list_append_fast (obj_1 , PY_createInteger(20)));


    PyObjectContainer* assert_target_2 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_list_index_fast (obj_1 , PY_createInteger(10))), PY_createInteger(0)));
    assert(PY_getTruthValueOf(assert_target_2));


    PyObjectContainer* temporary_3 = PY_getObjectAttributeByNameOrStatic(obj_1, "remove");
    PyObjectContainer* args_4[1];
    args_4[0] = PY_createInteger(10);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(temporary_3, NULL, 1, args_4, NULL));

    PY_CHECK_EXCEPTION(PY_STD_list_append_fast (obj_1 , PY_createInteger(30)));

    PY_CHECK_EXCEPTION(PY_STD_list_insert_fast (obj_1 , PY_createInteger(0) , PY_createInteger(20)));

    PY_CHECK_EXCEPTION(PY_STD_list_setAtIndex_fast (obj_1 , PY_createInteger(0) , PY_createInteger(25)));

    PY_CHECK_EXCEPTION(PY_STD_list_setAtIndex_fast (obj_1 , PY_createInteger(1) , PY_GetSubscriptionValue(obj_1, PY_createInteger(1))));

    PY_CHECK_EXCEPTION(PY_STD_list_clear_fast (obj_1));


    PY_STD_list_CREATE(3, PY_createInteger(10), PY_createInteger(20), PY_STD_list_CREATE(2, PY_createInteger(50), PY_createInteger(423)));


    PyObjectContainer* assert_target_5 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_list_len_fast (obj_1)), PY_createInteger(0)));
    assert(PY_getTruthValueOf(assert_target_5));

    PY_CHECK_EXCEPTION(PY_STD_list_append_fast (obj_1 , PY_createInteger(10)));

    PyObjectContainer* assert_target_6 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_list_len_fast (obj_1)), PY_createInteger(1)));
    assert(PY_getTruthValueOf(assert_target_6));
    return PY_NONE;
}

PyObjectContainer* test_0_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return test_0();
}

