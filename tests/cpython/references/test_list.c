#include <stdlib.h>

#include "pyinclude.h"
#include "standard_library/config.h"

#include "standard_library/init.h"
#include "standard_library/exceptions.h"

#ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
#include "standard_library/importhelper.h"
#endif

#include "test_list.h"

#ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
PyObjectContainer* PY_MODULE_INSTANCE_test_list;
#endif

// code compiled from python to c via PyCodeCompiler

#include "standard_library/modules/unittest.h"
#include <assert.h>



// Global Variables
PyObjectContainer* function_container_test_basic_0;
PyObjectContainer* function_container_test_truth_1;
PyObjectContainer* function_container_test_identity_2;
PyObjectContainer* function_container_test_len_3;
PyClassContainer* PY_CLASS_ListTest_8;



// implementations

PyObjectContainer* PY_MODULE_test_list_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_MODULE_INSTANCE_test_list = PY_createModuleObject("test_list");
    #endif
    PyObjectContainer* ListTest_8;
    PyObjectContainer* unittest_9;








    PY_CHECK_EXCEPTION(PY_MODULE_unittest_init());
    unittest_9 = PY_MODULE_INSTANCE_unittest;



    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_list, "test_basic", (function_container_test_basic_0 = PY_createBoxForFunction(testbasic_1_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_list, "test_truth", (function_container_test_truth_1 = PY_createBoxForFunction(testtruth_3_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_list, "test_identity", (function_container_test_identity_2 = PY_createBoxForFunction(testidentity_5_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_list, "test_len", (function_container_test_len_3 = PY_createBoxForFunction(testlen_7_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_ListTest_8();
    if (PY_unpackBoolean(PY_CHECK_EXCEPTION(PY_CHECK_EXCEPTION(PY_STD_string_eq_fast (PY_createString("__main__") , PY_createString("__main__")))))) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "main"), NULL, 0, NULL, NULL));
    }
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_exposeModuleObject(PY_MODULE_INSTANCE_test_list);
    #endif
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_ListTest_8(void) {
    // Create Class PY_CLASS_ListTest_8 ('ListTest' in source code)
    PY_CLASS_ListTest_8 = PY_createClassContainer("ListTest");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_ListTest_8, 1);

    // Create Parent Objects for class 'ListTest'
    PY_CLASS_ListTest_8 -> parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_4 = PY_getClassAttributeByName(PY_CLASS_ListTest_8->parents[0], "__init_subclass__");
    if (init_subclass_4 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_4, PY_createClassWrapper(PY_CLASS_ListTest_8), 0, NULL, NULL));
    }

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_ListTest_8, "test_basic", PY_createBoxForFunction(testbasic_1_safeWrap));
    PY_setClassAttributeByNameOrCreate(PY_CLASS_ListTest_8, "test_truth", PY_createBoxForFunction(testtruth_3_safeWrap));
    PY_setClassAttributeByNameOrCreate(PY_CLASS_ListTest_8, "test_identity", PY_createBoxForFunction(testidentity_5_safeWrap));
    PY_setClassAttributeByNameOrCreate(PY_CLASS_ListTest_8, "test_len", PY_createBoxForFunction(testlen_7_safeWrap));
}

PyObjectContainer* testbasic_1(PyObjectContainer* self_0) {
    // Source Location: ListTest.test_basic
    PyObjectContainer* l03_10;
    PyObjectContainer* l03bis_11;
    PyObjectContainer* x_12;

    PyObjectContainer* obj_instance_6 = PY_createClassInstance(PY_TYPE_LIST);
    PY_CHECK_EXCEPTION(PY_STD_list_init_fast_arg_1(obj_instance_6 , PY_STD_list_CREATE(0)));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_0, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {obj_instance_6, PY_STD_list_CREATE(0)}, NULL));

    l03_10 = PY_STD_list_CREATE(4, PY_createInteger(0), PY_createInteger(1), PY_createInteger(2), PY_createInteger(3));

    PyObjectContainer* obj_instance_8 = PY_createClassInstance(PY_TYPE_LIST);
    PY_CHECK_EXCEPTION(PY_STD_list_init_fast_arg_1(obj_instance_8 , l03_10));

    l03bis_11 = obj_instance_8;

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_0, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {l03_10, l03bis_11}, NULL));

    PyObjectContainer* temporary_11 = PY_STD_operator_is_not(l03_10, l03bis_11);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_0, "assertTrue"), NULL, 1, &temporary_11, NULL));

    PyObjectContainer* obj_instance_13 = PY_createClassInstance(PY_TYPE_LIST);
    PY_CHECK_EXCEPTION(PY_STD_list_init_fast_arg_1(obj_instance_13 , PY_STD_tuple_CREATE(0)));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_0, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {obj_instance_13, PY_STD_list_CREATE(0)}, NULL));

    PyObjectContainer* obj_instance_16 = PY_createClassInstance(PY_TYPE_LIST);
    PY_CHECK_EXCEPTION(PY_STD_list_init_fast_arg_1(obj_instance_16 , PY_STD_tuple_CREATE(4, PY_createInteger(0), PY_createInteger(1), PY_createInteger(2), PY_createInteger(3))));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_0, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {obj_instance_16, PY_STD_list_CREATE(4, PY_createInteger(0), PY_createInteger(1), PY_createInteger(2), PY_createInteger(3))}, NULL));

    PyObjectContainer* obj_instance_19 = PY_createClassInstance(PY_TYPE_LIST);
    PY_CHECK_EXCEPTION(PY_STD_list_init_fast_arg_1(obj_instance_19 , PY_createString("")));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_0, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {obj_instance_19, PY_STD_list_CREATE(0)}, NULL));

    PyObjectContainer* obj_instance_22 = PY_createClassInstance(PY_TYPE_LIST);
    PY_CHECK_EXCEPTION(PY_STD_list_init_fast_arg_1(obj_instance_22 , PY_createString("spam")));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_0, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {obj_instance_22, PY_STD_list_CREATE(4, PY_createString("s"), PY_createString("p"), PY_createString("a"), PY_createString("m"))}, NULL));






    x_12 = PY_STD_list_CREATE(0);



    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_0, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {x_12, PY_STD_list_CREATE(0)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testbasic_1_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testbasic_1(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testbasic_1(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testtruth_3(PyObjectContainer* self_2) {
    // Source Location: ListTest.test_truth

    PyObjectContainer* temporary_25 = PY_STD_operator_not(PY_STD_list_CREATE(0));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_2, "assertTrue"), NULL, 1, &temporary_25, NULL));

    PyObjectContainer* temporary_26 = PY_STD_list_CREATE(1, PY_createInteger(42));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_2, "assertTrue"), NULL, 1, &temporary_26, NULL));


    return PY_NONE;
}

PyObjectContainer* testtruth_3_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testtruth_3(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testtruth_3(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testidentity_5(PyObjectContainer* self_4) {
    // Source Location: ListTest.test_identity

    PyObjectContainer* temporary_27 = PY_STD_operator_is_not(PY_STD_list_CREATE(0), PY_STD_list_CREATE(0));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_4, "assertTrue"), NULL, 1, &temporary_27, NULL));


    return PY_NONE;
}

PyObjectContainer* testidentity_5_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testidentity_5(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testidentity_5(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testlen_7(PyObjectContainer* self_6) {
    // Source Location: ListTest.test_len

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_6, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_list_len_fast (PY_STD_list_CREATE(0))), PY_createInteger(0)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_6, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_list_len_fast (PY_STD_list_CREATE(1, PY_createInteger(0)))), PY_createInteger(1)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_6, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_STD_list_len_fast (PY_STD_list_CREATE(3, PY_createInteger(0), PY_createInteger(1), PY_createInteger(2)))), PY_createInteger(3)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testlen_7_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testlen_7(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testlen_7(self);
    }

    if (info) free(new_args);
    return result;
}

