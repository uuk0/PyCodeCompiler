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
PyObjectContainer* function_container_simple_target_keyword_1;
PyObjectContainer* function_container_target_2;
PyObjectContainer* function_container_test_basic_3;
PyObjectContainer* function_container_test_simple_4;
PyObjectContainer* function_container_test_simple_5;
PyObjectContainer* function_container_test_simple_6;
PyObjectContainer* function_container___lambda___7;
PyObjectContainer* function_container___lambda___8;
PyObjectContainer* function_container___lambda___9;
PyObjectContainer* function_container___lambda___10;
PyObjectContainer* function_container_test_basic_11;
PyObjectContainer* function_container_test_with_param_12;
PyObjectContainer* function_container_test_lambda_ception_13;
PyObjectContainer* default_keyword_a_14;
PyObjectContainer** keyword_name_table_15;
PyClassContainer* PY_CLASS_TestFunctionInception_7;
PyClassContainer* PY_CLASS_TestCallStar_10;
PyClassContainer* PY_CLASS_TestKeyword_13;
PyObjectContainer** keyword_name_var_24;
PyClassContainer* PY_CLASS_TestStarStar_16;
PyClassContainer* PY_CLASS_TestLambdaDeclaration_28;



// implementations

PyObjectContainer* PY_MODULE_test_calling_conventions_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_MODULE_INSTANCE_test_calling_conventions = PY_createModuleObject("test_calling_conventions");
    #endif
    PyObjectContainer* TestCallStar_10;
    PyObjectContainer* TestFunctionInception_7;
    PyObjectContainer* TestKeyword_13;
    PyObjectContainer* TestLambdaDeclaration_28;
    PyObjectContainer* TestStarStar_16;
    PyObjectContainer* simpletarget_1;
    PyObjectContainer* simpletargetkeyword_3;
    PyObjectContainer* unittest_29;
    PY_CHECK_EXCEPTION(PY_MODULE_unittest_init());
    unittest_29 = PY_MODULE_INSTANCE_unittest;



    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "simple_target", (function_container_simple_target_0 = PY_createBoxForFunction(simpletarget_1_safeWrap)));
    #endif

    default_keyword_a_14 = PY_createInteger(10);
    keyword_name_table_15 = (PyObjectContainer*[]){PY_createString("a")};
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "simple_target_keyword", (function_container_simple_target_keyword_1 = PY_createBoxForFunction(simpletargetkeyword_3_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "target", (function_container_target_2 = PY_createBoxForFunction(target_4_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_basic", (function_container_test_basic_3 = PY_createBoxForFunction(testbasic_6_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestFunctionInception_7();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_simple", (function_container_test_simple_4 = PY_createBoxForFunction(testsimple_9_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestCallStar_10();
    keyword_name_var_24 = (PyObjectContainer*[]) {PY_createString("a")};
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_simple", (function_container_test_simple_5 = PY_createBoxForFunction(testsimple_12_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestKeyword_13();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_simple", (function_container_test_simple_6 = PY_createBoxForFunction(testsimple_15_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestStarStar_16();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "__lambda__", (function_container___lambda___7 = PY_createBoxForFunction(lambda_17_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "__lambda__", (function_container___lambda___8 = PY_createBoxForFunction(lambda_19_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "__lambda__", (function_container___lambda___9 = PY_createBoxForFunction(lambda_20_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "__lambda__", (function_container___lambda___10 = PY_createBoxForFunction(lambda_21_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_basic", (function_container_test_basic_11 = PY_createBoxForFunction(testbasic_23_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_with_param", (function_container_test_with_param_12 = PY_createBoxForFunction(testwithparam_25_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_lambda_ception", (function_container_test_lambda_ception_13 = PY_createBoxForFunction(testlambdaception_27_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestLambdaDeclaration_28();
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

PyObjectContainer* simpletargetkeyword_3(PyObjectContainer* a_2) {
    // Source Location: .simple_target_keyword

    return a_2;



    return PY_NONE;
}

PyObjectContainer* simpletargetkeyword_3_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackArgTableForUnsafeCall(0, args, info, &argc, 1, keyword_name_table_15, (PyObjectContainer*[]) {default_keyword_a_14});
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = simpletargetkeyword_3(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = simpletargetkeyword_3(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* target_4(void) {
    // Source Location: TestFunctionInception.target

    return PY_createInteger(10);


    return PY_NONE;
}

PyObjectContainer* target_4_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return target_4();
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestFunctionInception_7(void) {
    // Create Class PY_CLASS_TestFunctionInception_7 ('TestFunctionInception' in source code)
    PY_CLASS_TestFunctionInception_7 = PY_createClassContainer("TestFunctionInception");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_TestFunctionInception_7, 1);

    // Create Parent Objects for class 'TestFunctionInception'
    PY_CLASS_TestFunctionInception_7 -> parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_16 = PY_getClassAttributeByName(PY_CLASS_TestFunctionInception_7->parents[0], "__init_subclass__");
    if (init_subclass_16 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_16, PY_createClassWrapper(PY_CLASS_TestFunctionInception_7), 0, NULL, NULL));
    }

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestFunctionInception_7, "test_basic", PY_createBoxForFunction(testbasic_6_safeWrap));
}

PyObjectContainer* testbasic_6(PyObjectContainer* self_5) {
    // Source Location: TestFunctionInception.test_basic
    PyObjectContainer* target_4;

    target_4 = function_container_target_2;
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_5, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(target_4, NULL, 0, NULL, NULL)), PY_createInteger(10)}, NULL));



    return PY_NONE;
}

PyObjectContainer* testbasic_6_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testbasic_6(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testbasic_6(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestCallStar_10(void) {
    // Create Class PY_CLASS_TestCallStar_10 ('TestCallStar' in source code)
    PY_CLASS_TestCallStar_10 = PY_createClassContainer("TestCallStar");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_TestCallStar_10, 1);

    // Create Parent Objects for class 'TestCallStar'
    PY_CLASS_TestCallStar_10 -> parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_18 = PY_getClassAttributeByName(PY_CLASS_TestCallStar_10->parents[0], "__init_subclass__");
    if (init_subclass_18 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_18, PY_createClassWrapper(PY_CLASS_TestCallStar_10), 0, NULL, NULL));
    }

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestCallStar_10, "test_simple", PY_createBoxForFunction(testsimple_9_safeWrap));
}

PyObjectContainer* testsimple_9(PyObjectContainer* self_8) {
    // Source Location: TestCallStar.test_simple
    PyObjectContainer* f_30;

    f_30 = function_container_simple_target_0;

    PyObjectContainer* temporary_20 = PY_STD_list_CREATE(1, PY_createInteger(10));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_8, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_30, NULL, 1, &temporary_20, PY_ARGS_createCallInfo(0, 1, (uint64_t[]) {CALL_STRUCTURE_STAR, 0, 0, 0, 0, 0, 0, 0}, NULL))), PY_createInteger(10)}, NULL));



    return PY_NONE;
}

PyObjectContainer* testsimple_9_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testsimple_9(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testsimple_9(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestKeyword_13(void) {
    // Create Class PY_CLASS_TestKeyword_13 ('TestKeyword' in source code)
    PY_CLASS_TestKeyword_13 = PY_createClassContainer("TestKeyword");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_TestKeyword_13, 1);

    // Create Parent Objects for class 'TestKeyword'
    PY_CLASS_TestKeyword_13 -> parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_21 = PY_getClassAttributeByName(PY_CLASS_TestKeyword_13->parents[0], "__init_subclass__");
    if (init_subclass_21 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_21, PY_createClassWrapper(PY_CLASS_TestKeyword_13), 0, NULL, NULL));
    }

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestKeyword_13, "test_simple", PY_createBoxForFunction(testsimple_12_safeWrap));
}

PyObjectContainer* testsimple_12(PyObjectContainer* self_11) {
    // Source Location: TestKeyword.test_simple
    PyObjectContainer* f_31;

    f_31 = function_container_simple_target_keyword_1;

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_11, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_31, NULL, 0, NULL, NULL)), PY_createInteger(10)}, NULL));

    PyObjectContainer* temporary_25 = PY_createInteger(20);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_11, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_31, NULL, 1, &temporary_25, PY_ARGS_createCallInfo(0, 1, (uint64_t[]) {CALL_STRUCTURE_KEYWORD, 0, 0, 0, 0, 0, 0, 0}, keyword_name_var_24))), PY_createInteger(20)}, NULL));

    PyObjectContainer* temporary_27 = PY_createInteger(20);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_11, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_31, NULL, 1, &temporary_27, NULL)), PY_createInteger(20)}, NULL));



    return PY_NONE;
}

PyObjectContainer* testsimple_12_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testsimple_12(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testsimple_12(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestStarStar_16(void) {
    // Create Class PY_CLASS_TestStarStar_16 ('TestStarStar' in source code)
    PY_CLASS_TestStarStar_16 = PY_createClassContainer("TestStarStar");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_TestStarStar_16, 1);

    // Create Parent Objects for class 'TestStarStar'
    PY_CLASS_TestStarStar_16 -> parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_28 = PY_getClassAttributeByName(PY_CLASS_TestStarStar_16->parents[0], "__init_subclass__");
    if (init_subclass_28 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_28, PY_createClassWrapper(PY_CLASS_TestStarStar_16), 0, NULL, NULL));
    }

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestStarStar_16, "test_simple", PY_createBoxForFunction(testsimple_15_safeWrap));
}

PyObjectContainer* testsimple_15(PyObjectContainer* self_14) {
    // Source Location: TestStarStar.test_simple
    PyObjectContainer* f_32;

    f_32 = function_container_simple_target_keyword_1;

    PyObjectContainer* temporary_30 = PY_STD_dict_CREATE(0);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_14, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_32, NULL, 1, &temporary_30, PY_ARGS_createCallInfo(0, 1, (uint64_t[]) {CALL_STRUCTURE_STAR_STAR, 0, 0, 0, 0, 0, 0, 0}, NULL))), PY_createInteger(10)}, NULL));

    PyObjectContainer* temporary_32 = PY_STD_dict_CREATE(1, PY_createString("a"), PY_createInteger(20));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_14, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_32, NULL, 1, &temporary_32, PY_ARGS_createCallInfo(0, 1, (uint64_t[]) {CALL_STRUCTURE_STAR_STAR, 0, 0, 0, 0, 0, 0, 0}, NULL))), PY_createInteger(20)}, NULL));



    return PY_NONE;
}

PyObjectContainer* testsimple_15_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testsimple_15(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testsimple_15(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* lambda_17(void) {
    // Source Location: TestLambdaDeclaration.__lambda__
    return PY_createInteger(10);
}

PyObjectContainer* lambda_17_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return lambda_17();
}

PyObjectContainer* lambda_19(PyObjectContainer* a_18) {
    // Source Location: TestLambdaDeclaration.__lambda__
    return PY_STD_operator_add(a_18, PY_createInteger(2));
}

PyObjectContainer* lambda_19_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = lambda_19(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = lambda_19(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* lambda_20(void) {
    // Source Location: .__lambda__
    return PY_createInteger(10);
}

PyObjectContainer* lambda_20_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return lambda_20();
}

PyObjectContainer* lambda_21(void) {
    // Source Location: TestLambdaDeclaration.__lambda__
    return function_container___lambda___9;
}

PyObjectContainer* lambda_21_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return lambda_21();
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestLambdaDeclaration_28(void) {
    // Create Class PY_CLASS_TestLambdaDeclaration_28 ('TestLambdaDeclaration' in source code)
    PY_CLASS_TestLambdaDeclaration_28 = PY_createClassContainer("TestLambdaDeclaration");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_TestLambdaDeclaration_28, 1);

    // Create Parent Objects for class 'TestLambdaDeclaration'
    PY_CLASS_TestLambdaDeclaration_28 -> parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_33 = PY_getClassAttributeByName(PY_CLASS_TestLambdaDeclaration_28->parents[0], "__init_subclass__");
    if (init_subclass_33 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_33, PY_createClassWrapper(PY_CLASS_TestLambdaDeclaration_28), 0, NULL, NULL));
    }

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestLambdaDeclaration_28, "test_basic", PY_createBoxForFunction(testbasic_23_safeWrap));
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestLambdaDeclaration_28, "test_with_param", PY_createBoxForFunction(testwithparam_25_safeWrap));
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestLambdaDeclaration_28, "test_lambda_ception", PY_createBoxForFunction(testlambdaception_27_safeWrap));
}

PyObjectContainer* testbasic_23(PyObjectContainer* self_22) {
    // Source Location: TestLambdaDeclaration.test_basic
    PyObjectContainer* x_33;

    x_33 = function_container___lambda___7;

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_22, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(x_33, NULL, 0, NULL, NULL)), PY_createInteger(10)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testbasic_23_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testbasic_23(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testbasic_23(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testwithparam_25(PyObjectContainer* self_24) {
    // Source Location: TestLambdaDeclaration.test_with_param
    PyObjectContainer* x_34;

    x_34 = function_container___lambda___8;

    PyObjectContainer* temporary_36 = PY_createInteger(2);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_24, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(x_34, NULL, 1, &temporary_36, NULL)), PY_createInteger(4)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testwithparam_25_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testwithparam_25(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testwithparam_25(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testlambdaception_27(PyObjectContainer* self_26) {
    // Source Location: TestLambdaDeclaration.test_lambda_ception
    PyObjectContainer* x_35;

    x_35 = function_container___lambda___10;

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_26, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(x_35, NULL, 0, NULL, NULL)), NULL, 0, NULL, NULL)), PY_createInteger(10)}, NULL));



    return PY_NONE;
}

PyObjectContainer* testlambdaception_27_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testlambdaception_27(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testlambdaception_27(self);
    }

    if (info) free(new_args);
    return result;
}

