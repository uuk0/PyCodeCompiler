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
PyObjectContainer* comprehension_transfer_8(PyObjectContainer* value , PyObjectContainer** locals);
PyObjectContainer* value;
PyObjectContainer* comprehension_transfer_10(PyObjectContainer* value , PyObjectContainer** locals);



// implementations

PyObjectContainer* PY_MODULE_source_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_MODULE_INSTANCE_source = PY_createModuleObject("source");
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "test", PY_createBoxForFunction(test_0_safeWrap));
    PY_exposeModuleObject(PY_MODULE_INSTANCE_source);
    #endif
}

PyObjectContainer* test_0(void) {
    PyObjectContainer* obj_1;
    PyObjectContainer* t_2;

    PyObjectContainer* obj_instance_0 = PY_createClassInstance(PY_TYPE_LIST);
    PY_CHECK_EXCEPTION(PY_STD_list_init_fast_arg_0(obj_instance_0));

    obj_1 = obj_instance_0;

    PY_CHECK_EXCEPTION(PY_STD_list_append_fast (obj_1 , PY_createInteger(10)));

    PY_CHECK_EXCEPTION(PY_STD_list_append_fast (obj_1 , PY_createInteger(20)));


    PyObjectContainer* assert_target_2 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_list_index_fast (obj_1 , PY_createInteger(10))), PY_createInteger(0)));
    assert(PY_getTruthValueOf(assert_target_2));


    PyObjectContainer* temporary_3 = PY_createInteger(10);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(obj_1, "remove"), NULL, 1, &temporary_3, NULL));

    PY_CHECK_EXCEPTION(PY_STD_list_append_fast (obj_1 , PY_createInteger(30)));

    PY_CHECK_EXCEPTION(PY_STD_list_insert_fast (obj_1 , PY_createInteger(0) , PY_createInteger(20)));

    PY_CHECK_EXCEPTION(PY_STD_list_setAtIndex_fast (obj_1 , PY_createInteger(0) , PY_createInteger(25)));

    PY_CHECK_EXCEPTION(PY_STD_list_setAtIndex_fast (obj_1 , PY_createInteger(1) , PY_GetSubscriptionValue(obj_1, PY_createInteger(1))));

    PY_CHECK_EXCEPTION(PY_STD_list_clear_fast (obj_1));


    PY_STD_list_CREATE(3, PY_createInteger(10), PY_createInteger(20), PY_STD_list_CREATE(2, PY_createInteger(50), PY_createInteger(423)));


    PyObjectContainer* assert_target_4 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_list_len_fast (obj_1)), PY_createInteger(0)));
    assert(PY_getTruthValueOf(assert_target_4));

    PY_CHECK_EXCEPTION(PY_STD_list_append_fast (obj_1 , PY_createInteger(10)));

    PyObjectContainer* assert_target_5 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_list_len_fast (obj_1)), PY_createInteger(1)));
    assert(PY_getTruthValueOf(assert_target_5));


    PY_CHECK_EXCEPTION(PY_STD_list_extend_fast (obj_1 , PY_STD_list_CREATE(1, PY_createInteger(10))));

    PyObjectContainer* assert_target_6 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_list_len_fast (obj_1)), PY_createInteger(2)));
    assert(PY_getTruthValueOf(assert_target_6));


    obj_1 = PY_CHECK_EXCEPTION(PY_STD_list_add_fast (obj_1 , PY_STD_list_CREATE(1, PY_createInteger(20))));

    PyObjectContainer* assert_target_7 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_list_len_fast (obj_1)), PY_createInteger(3)));
    assert(PY_getTruthValueOf(assert_target_7));


    obj_1 = PY_STD_list_CONSTRUCT_COMPREHENSION_with_len_hint_with_iter_hint(obj_1, comprehension_transfer_8, NULL, NULL, PY_STD_list_len_fast, PY_STD_list_iter_fast);

    PyObjectContainer* assert_target_9 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(obj_1, PY_STD_list_CREATE(3, PY_createInteger(12), PY_createInteger(12), PY_createInteger(22))));
    assert(PY_getTruthValueOf(assert_target_9));


    t_2 = PY_createInteger(2);

    obj_1 = PY_STD_list_CONSTRUCT_COMPREHENSION_with_len_hint_with_iter_hint(obj_1, comprehension_transfer_10, NULL, (PyObjectContainer*[]) { t_2 }, PY_STD_list_len_fast, PY_STD_list_iter_fast);

    PyObjectContainer* assert_target_11 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(obj_1, PY_STD_list_CREATE(3, PY_createInteger(14), PY_createInteger(14), PY_createInteger(24))));
    assert(PY_getTruthValueOf(assert_target_11));
    return PY_NONE;
}

PyObjectContainer* comprehension_transfer_8(PyObjectContainer* value , PyObjectContainer** locals) {
    PyObjectContainer* x_3;
    x_3 = value;
    return PY_STD_operator_add(x_3, PY_createInteger(2));
}

PyObjectContainer* comprehension_transfer_10(PyObjectContainer* value , PyObjectContainer** locals) {
    PyObjectContainer* x_4;
    x_4 = value;
    return PY_STD_operator_add(x_4, locals[0]);
}

PyObjectContainer* test_0_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return test_0();
}

