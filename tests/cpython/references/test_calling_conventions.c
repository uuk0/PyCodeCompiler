#include <stdlib.h>

#include "pyinclude.h"
#include "standard_library/config.h"

#include "standard_library/init.h"
#include "standard_library/exceptions.h"

#ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
#include "standard_library/importhelper.h"
#endif

#include "test_calling_conventions.h"

#ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
PyObjectContainer* PY_MODULE_INSTANCE_test_calling_conventions;
#endif

// code compiled from python to c via PyCodeCompiler

#include "standard_library/modules/unittest.h"
#include <assert.h>



// Global Variables
PyObjectContainer* function_container_simple_target_0;
PyObjectContainer* function_container_basic_test_1;
PyObjectContainer* function_container_simple_target_keyword_2;
PyObjectContainer* function_container_test_simple_keyword_3;
PyObjectContainer* function_container_test_star_star_4;
PyObjectContainer* function_container_test_simple_5;
PyObjectContainer* function_container_test_simple_6;
PyObjectContainer* function_container_test_simple_7;
PyObjectContainer* function_container___lambda___8;
PyObjectContainer* function_container___lambda___9;
PyObjectContainer* function_container___lambda___10;
PyObjectContainer* function_container___lambda___11;
PyObjectContainer* function_container_test_basic_12;
PyObjectContainer* function_container_test_with_param_13;
PyObjectContainer* function_container_test_lambda_ception_14;
PyObjectContainer* default_keyword_a_17;
PyObjectContainer** keyword_name_table_18;
PyObjectContainer** keyword_name_var_21;
PyClassContainer* PY_CLASS_TestCallStar_15;
PyClassContainer* PY_CLASS_TestKeyword_18;
PyClassContainer* PY_CLASS_TestStarStar_21;
PyClassContainer* PY_CLASS_TestLambdaDeclaration_33;



// implementations

PyObjectContainer* PY_MODULE_test_calling_conventions_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_MODULE_INSTANCE_test_calling_conventions = PY_createModuleObject("test_calling_conventions");
    #endif
    PyObjectContainer* TestCallStar_15;
    PyObjectContainer* TestKeyword_18;
    PyObjectContainer* TestLambdaDeclaration_33;
    PyObjectContainer* TestStarStar_21;
    PyObjectContainer* __lambda___34;
    PyObjectContainer* basictest_4;
    PyObjectContainer* simpletarget_1;
    PyObjectContainer* simpletargetkeyword_6;
    PyObjectContainer* testsimplekeyword_9;
    PyObjectContainer* teststarstar_12;
    PyObjectContainer* unittest_35;
    PY_CHECK_EXCEPTION(PY_MODULE_unittest_init());
    unittest_35 = PY_MODULE_INSTANCE_unittest;



    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "simple_target", (function_container_simple_target_0 = PY_createBoxForFunction(simpletarget_1_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "basic_test", (function_container_basic_test_1 = PY_createBoxForFunction(basictest_4_safeWrap)));
    #endif

    default_keyword_a_17 = PY_createInteger(10);
    keyword_name_table_18 = (PyObjectContainer*[]){PY_createString("a")};
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "simple_target_keyword", (function_container_simple_target_keyword_2 = PY_createBoxForFunction(simpletargetkeyword_6_safeWrap)));
    #endif

    keyword_name_var_21 = (PyObjectContainer*[]) {PY_createString("a")};
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_simple_keyword", (function_container_test_simple_keyword_3 = PY_createBoxForFunction(testsimplekeyword_9_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_star_star", (function_container_test_star_star_4 = PY_createBoxForFunction(teststarstar_12_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_simple", (function_container_test_simple_5 = PY_createBoxForFunction(testsimple_14_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestCallStar_15();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_simple", (function_container_test_simple_6 = PY_createBoxForFunction(testsimple_17_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestKeyword_18();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_simple", (function_container_test_simple_7 = PY_createBoxForFunction(testsimple_20_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestStarStar_21();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "__lambda__", (function_container___lambda___8 = PY_createBoxForFunction(lambda_22_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "__lambda__", (function_container___lambda___9 = PY_createBoxForFunction(lambda_24_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "__lambda__", (function_container___lambda___10 = PY_createBoxForFunction(lambda_25_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "__lambda__", (function_container___lambda___11 = PY_createBoxForFunction(lambda_26_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_basic", (function_container_test_basic_12 = PY_createBoxForFunction(testbasic_28_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_with_param", (function_container_test_with_param_13 = PY_createBoxForFunction(testwithparam_30_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_lambda_ception", (function_container_test_lambda_ception_14 = PY_createBoxForFunction(testlambdaception_32_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestLambdaDeclaration_33();
    if (PY_unpackBoolean(PY_CHECK_EXCEPTION(PY_CHECK_EXCEPTION(PY_STD_string_eq_fast (PY_createString("__main__") , PY_createString("__main__")))))) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "main"), NULL, 0, NULL, NULL));
    }
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_exposeModuleObject(PY_MODULE_INSTANCE_test_calling_conventions);
    #endif
}

PyObjectContainer* simpletarget_1(PyObjectContainer* a_0) {
    // Source Location: .simple_target

    return a_0;



    return PY_NONE;
}

PyObjectContainer* simpletarget_1_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = simpletarget_1(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = simpletarget_1(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* basictest_4(PyObjectContainer* self_2 , PyObjectContainer* f_3) {
    // Source Location: .basic_test

    PyObjectContainer* temporary_16 = PY_STD_list_CREATE(1, PY_createInteger(10));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_2, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_3, NULL, 1, &temporary_16, PY_ARGS_createCallInfo(0, 1, (uint64_t[]) {CALL_STRUCTURE_STAR, 0, 0, 0, 0, 0, 0, 0}, NULL))), PY_createInteger(10)}, NULL));



    return PY_NONE;
}

PyObjectContainer* basictest_4_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 2);
        result = basictest_4(new_args[0] , new_args[1]);
    }
    else {
        assert(argc == 1);
        result = basictest_4(self , new_args[0]);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* simpletargetkeyword_6(PyObjectContainer* a_5) {
    // Source Location: .simple_target_keyword

    return a_5;



    return PY_NONE;
}

PyObjectContainer* simpletargetkeyword_6_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackArgTableForUnsafeCall(0, args, info, &argc, 1, keyword_name_table_18, (PyObjectContainer*[]) {default_keyword_a_17});
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = simpletargetkeyword_6(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = simpletargetkeyword_6(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testsimplekeyword_9(PyObjectContainer* self_7 , PyObjectContainer* f_8) {
    // Source Location: .test_simple_keyword

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_7, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_8, NULL, 0, NULL, NULL)), PY_createInteger(10)}, NULL));

    PyObjectContainer* temporary_22 = PY_createInteger(20);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_7, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_8, NULL, 1, &temporary_22, PY_ARGS_createCallInfo(0, 1, (uint64_t[]) {CALL_STRUCTURE_KEYWORD, 0, 0, 0, 0, 0, 0, 0}, keyword_name_var_21))), PY_createInteger(20)}, NULL));

    PyObjectContainer* temporary_24 = PY_createInteger(20);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_7, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_8, NULL, 1, &temporary_24, NULL)), PY_createInteger(20)}, NULL));



    return PY_NONE;
}

PyObjectContainer* testsimplekeyword_9_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 2);
        result = testsimplekeyword_9(new_args[0] , new_args[1]);
    }
    else {
        assert(argc == 1);
        result = testsimplekeyword_9(self , new_args[0]);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* teststarstar_12(PyObjectContainer* self_10 , PyObjectContainer* f_11) {
    // Source Location: .test_star_star

    PyObjectContainer* temporary_26 = PY_STD_dict_CREATE(0);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_10, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_11, NULL, 1, &temporary_26, PY_ARGS_createCallInfo(0, 1, (uint64_t[]) {CALL_STRUCTURE_STAR_STAR, 0, 0, 0, 0, 0, 0, 0}, NULL))), PY_createInteger(10)}, NULL));

    PyObjectContainer* temporary_28 = PY_STD_dict_CREATE(1, PY_createString("a"), PY_createInteger(20));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_10, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_11, NULL, 1, &temporary_28, PY_ARGS_createCallInfo(0, 1, (uint64_t[]) {CALL_STRUCTURE_STAR_STAR, 0, 0, 0, 0, 0, 0, 0}, NULL))), PY_createInteger(20)}, NULL));



    return PY_NONE;
}

PyObjectContainer* teststarstar_12_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 2);
        result = teststarstar_12(new_args[0] , new_args[1]);
    }
    else {
        assert(argc == 1);
        result = teststarstar_12(self , new_args[0]);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestCallStar_15(void) {
    // Create Class PY_CLASS_TestCallStar_15 ('TestCallStar' in source code)
    PY_CLASS_TestCallStar_15 = PY_createClassContainer("TestCallStar");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_TestCallStar_15, 1);

    // Create Parent Objects for class 'TestCallStar'
    PY_CLASS_TestCallStar_15 -> parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_29 = PY_getClassAttributeByName(PY_CLASS_TestCallStar_15->parents[0], "__init_subclass__");
    if (init_subclass_29 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_29, PY_createClassWrapper(PY_CLASS_TestCallStar_15), 0, NULL, NULL));
    }

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestCallStar_15, "test_simple", PY_createBoxForFunction(testsimple_14_safeWrap));
}

PyObjectContainer* testsimple_14(PyObjectContainer* self_13) {
    // Source Location: TestCallStar.test_simple

    PY_CHECK_EXCEPTION(basictest_4 (self_13 , function_container_simple_target_0));



    return PY_NONE;
}

PyObjectContainer* testsimple_14_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testsimple_14(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testsimple_14(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestKeyword_18(void) {
    // Create Class PY_CLASS_TestKeyword_18 ('TestKeyword' in source code)
    PY_CLASS_TestKeyword_18 = PY_createClassContainer("TestKeyword");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_TestKeyword_18, 1);

    // Create Parent Objects for class 'TestKeyword'
    PY_CLASS_TestKeyword_18 -> parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_30 = PY_getClassAttributeByName(PY_CLASS_TestKeyword_18->parents[0], "__init_subclass__");
    if (init_subclass_30 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_30, PY_createClassWrapper(PY_CLASS_TestKeyword_18), 0, NULL, NULL));
    }

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestKeyword_18, "test_simple", PY_createBoxForFunction(testsimple_17_safeWrap));
}

PyObjectContainer* testsimple_17(PyObjectContainer* self_16) {
    // Source Location: TestKeyword.test_simple

    PY_CHECK_EXCEPTION(testsimplekeyword_9 (self_16 , function_container_simple_target_keyword_2));



    return PY_NONE;
}

PyObjectContainer* testsimple_17_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testsimple_17(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testsimple_17(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestStarStar_21(void) {
    // Create Class PY_CLASS_TestStarStar_21 ('TestStarStar' in source code)
    PY_CLASS_TestStarStar_21 = PY_createClassContainer("TestStarStar");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_TestStarStar_21, 1);

    // Create Parent Objects for class 'TestStarStar'
    PY_CLASS_TestStarStar_21 -> parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_31 = PY_getClassAttributeByName(PY_CLASS_TestStarStar_21->parents[0], "__init_subclass__");
    if (init_subclass_31 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_31, PY_createClassWrapper(PY_CLASS_TestStarStar_21), 0, NULL, NULL));
    }

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestStarStar_21, "test_simple", PY_createBoxForFunction(testsimple_20_safeWrap));
}

PyObjectContainer* testsimple_20(PyObjectContainer* self_19) {
    // Source Location: TestStarStar.test_simple

    PY_CHECK_EXCEPTION(teststarstar_12 (self_19 , function_container_simple_target_keyword_2));



    return PY_NONE;
}

PyObjectContainer* testsimple_20_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testsimple_20(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testsimple_20(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* lambda_22(void) {
    // Source Location: TestLambdaDeclaration.__lambda__
    return PY_createInteger(10);
}

PyObjectContainer* lambda_22_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return lambda_22();
}

PyObjectContainer* lambda_24(PyObjectContainer* a_23) {
    // Source Location: TestLambdaDeclaration.__lambda__
    return PY_STD_operator_add(a_23, PY_createInteger(2));
}

PyObjectContainer* lambda_24_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = lambda_24(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = lambda_24(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* lambda_25(void) {
    // Source Location: .__lambda__
    return PY_createInteger(10);
}

PyObjectContainer* lambda_25_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return lambda_25();
}

PyObjectContainer* lambda_26(void) {
    // Source Location: TestLambdaDeclaration.__lambda__
    return function_container___lambda___10;
}

PyObjectContainer* lambda_26_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return lambda_26();
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestLambdaDeclaration_33(void) {
    // Create Class PY_CLASS_TestLambdaDeclaration_33 ('TestLambdaDeclaration' in source code)
    PY_CLASS_TestLambdaDeclaration_33 = PY_createClassContainer("TestLambdaDeclaration");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_TestLambdaDeclaration_33, 1);

    // Create Parent Objects for class 'TestLambdaDeclaration'
    PY_CLASS_TestLambdaDeclaration_33 -> parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_32 = PY_getClassAttributeByName(PY_CLASS_TestLambdaDeclaration_33->parents[0], "__init_subclass__");
    if (init_subclass_32 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_32, PY_createClassWrapper(PY_CLASS_TestLambdaDeclaration_33), 0, NULL, NULL));
    }

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestLambdaDeclaration_33, "test_basic", PY_createBoxForFunction(testbasic_28_safeWrap));
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestLambdaDeclaration_33, "test_with_param", PY_createBoxForFunction(testwithparam_30_safeWrap));
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestLambdaDeclaration_33, "test_lambda_ception", PY_createBoxForFunction(testlambdaception_32_safeWrap));
}

PyObjectContainer* testbasic_28(PyObjectContainer* self_27) {
    // Source Location: TestLambdaDeclaration.test_basic
    PyObjectContainer* x_36;

    x_36 = function_container___lambda___8;

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_27, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(x_36, NULL, 0, NULL, NULL)), PY_createInteger(10)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testbasic_28_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testbasic_28(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testbasic_28(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testwithparam_30(PyObjectContainer* self_29) {
    // Source Location: TestLambdaDeclaration.test_with_param
    PyObjectContainer* x_37;

    x_37 = function_container___lambda___9;

    PyObjectContainer* temporary_35 = PY_createInteger(2);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_29, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(x_37, NULL, 1, &temporary_35, NULL)), PY_createInteger(4)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testwithparam_30_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testwithparam_30(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testwithparam_30(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testlambdaception_32(PyObjectContainer* self_31) {
    // Source Location: TestLambdaDeclaration.test_lambda_ception
    PyObjectContainer* x_38;

    x_38 = function_container___lambda___11;

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_31, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(x_38, NULL, 0, NULL, NULL)), NULL, 0, NULL, NULL)), PY_createInteger(10)}, NULL));



    return PY_NONE;
}

PyObjectContainer* testlambdaception_32_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testlambdaception_32(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testlambdaception_32(self);
    }

    if (info) free(new_args);
    return result;
}

