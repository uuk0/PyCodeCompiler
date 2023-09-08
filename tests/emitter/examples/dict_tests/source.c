#include <stdlib.h>

#include "pyinclude.h"
#include "standard_library/init.h"
#include "standard_library/exceptions.h"

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

    PyObjectContainer* obj_instance_0 = PY_createClassInstance(PY_TYPE_DICT);
    PY_CHECK_EXCEPTION(PY_STD_dict_init_fast_arg_zero(obj_instance_0));

    obj_1 = obj_instance_0;

    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (obj_1 , PY_createString("test") , PY_createInteger(10)));

    PyObjectContainer* assert_target_2 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (obj_1 , PY_createString("test"))), PY_createInteger(10)));
    assert(PY_getTruthValueOf(assert_target_2));

    PyObjectContainer* assert_target_3 = PY_CHECK_EXCEPTION(PY_STD_operator_contains(obj_1, PY_createString("test")));
    assert(PY_getTruthValueOf(assert_target_3));


    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (obj_1 , PY_createString("test") , PY_createInteger(20)));

    PyObjectContainer* assert_target_4 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (obj_1 , PY_createString("test"))), PY_createInteger(20)));
    assert(PY_getTruthValueOf(assert_target_4));

    PyObjectContainer* assert_target_5 = PY_CHECK_EXCEPTION(PY_STD_operator_contains(obj_1, PY_createString("test")));
    assert(PY_getTruthValueOf(assert_target_5));


    PY_CHECK_EXCEPTION(PY_STD_dict_setitem_fast (obj_1 , PY_createString("other") , PY_createInteger(5)));

    PyObjectContainer* assert_target_6 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_STD_dict_getitem_fast (obj_1 , PY_createString("other"))), PY_createInteger(5)));
    assert(PY_getTruthValueOf(assert_target_6));
    return PY_NONE;
}

PyObjectContainer* test_0_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return test_0();
}

