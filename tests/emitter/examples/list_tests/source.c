#include <stdlib.h>

#include "pyinclude.h"
#include "standard_library/init.h"

// code compiled from python to c via PyCodeCompiler

#include <assert.h>


int _initialise();
PyObjectContainer* test_0();
PyObjectContainer* test_0_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info);


// implementations

int _initialise() {
    PY_STD_INIT();
}

PyObjectContainer* test_0() {
    PyObjectContainer* obj_1;


    PyObjectContainer* obj_instance_0 = PY_createClassInstance(PY_TYPE_LIST);
    PyObjectContainer* constructor_1 = PY_getObjectAttributeByNameOrStatic(obj_instance_0, "__init__");

    assert(constructor_1 != NULL);
    PY_invokeBoxedMethod(constructor_1, NULL, 0, NULL, NULL);
    DECREF(constructor_1);
    obj_1 = obj_instance_0;

    PY_STD_list_append_fast (obj_1 , PY_createInteger(10));

    PY_STD_list_append_fast (obj_1 , PY_createInteger(20));

    PyObjectContainer* temporary_2 = PY_getObjectAttributeByNameOrStatic(obj_1, "index");
    PyObjectContainer* args_3[1];
    args_3[0] = PY_createInteger(10);
    PY_invokeBoxedMethod(temporary_2, NULL, 1, args_3, NULL);

    PyObjectContainer* temporary_4 = PY_getObjectAttributeByNameOrStatic(obj_1, "remove");
    PyObjectContainer* args_5[1];
    args_5[0] = PY_createInteger(10);
    PY_invokeBoxedMethod(temporary_4, NULL, 1, args_5, NULL);

    PY_STD_list_append_fast (obj_1 , PY_createInteger(30));

    PY_STD_list_setAtIndex_fast (obj_1 , PY_createInteger(0) , PY_createInteger(25));

    PY_STD_list_setAtIndex_fast (obj_1 , PY_createInteger(1) , PY_GetSubscriptionValue(obj_1, PY_createInteger(1)));

    PY_STD_list_clear_fast (obj_1);


    PY_STD_list_CREATE(3, PY_createInteger(10), PY_createInteger(20), PY_STD_list_CREATE(2, PY_createInteger(50), PY_createInteger(423)));


    PyObjectContainer* assert_target_6 = PY_STD_operator_equals(PY_STD_list_len_fast (obj_1), PY_createInteger(0));
    assert(PY_getTruthValueOf(assert_target_6));

    PY_STD_list_append_fast (obj_1 , PY_createInteger(10));

    PyObjectContainer* assert_target_7 = PY_STD_operator_equals(PY_STD_list_len_fast (obj_1), PY_createInteger(1));
    assert(PY_getTruthValueOf(assert_target_7));
}

PyObjectContainer* test_0_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return test_0();
}

