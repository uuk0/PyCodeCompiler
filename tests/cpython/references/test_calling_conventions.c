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
PyObjectContainer* function_container_test_simple_2;
PyObjectContainer* function_container_test_simple_3;
PyObjectContainer* function_container_test_simple_4;
PyObjectContainer* function_container___lambda___5;
PyObjectContainer* function_container___lambda___6;
PyObjectContainer* function_container___lambda___7;
PyObjectContainer* function_container___lambda___8;
PyObjectContainer* function_container_test_basic_9;
PyObjectContainer* function_container_test_with_param_10;
PyObjectContainer* function_container_test_lambda_ception_11;
PyObjectContainer* default_keyword_a_12;
PyObjectContainer** keyword_name_table_13;
PyClassContainer* PY_CLASS_TestCallStar_6;
PyClassContainer* PY_CLASS_TestKeyword_9;
PyObjectContainer** keyword_name_var_20;
PyClassContainer* PY_CLASS_TestStarStar_12;
PyClassContainer* PY_CLASS_TestLambdaDeclaration_24;



// implementations

PyObjectContainer* PY_MODULE_test_calling_conventions_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_MODULE_INSTANCE_test_calling_conventions = PY_createModuleObject("test_calling_conventions");
    #endif
    PyObjectContainer* TestCallStar_6;
    PyObjectContainer* TestKeyword_9;
    PyObjectContainer* TestLambdaDeclaration_24;
    PyObjectContainer* TestStarStar_12;
    PyObjectContainer* __lambda___25;
    PyObjectContainer* simpletarget_1;
    PyObjectContainer* simpletargetkeyword_3;
    PyObjectContainer* unittest_26;
    PY_CHECK_EXCEPTION(PY_MODULE_unittest_init());
    unittest_26 = PY_MODULE_INSTANCE_unittest;



    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "simple_target", (function_container_simple_target_0 = PY_createBoxForFunction(simpletarget_1_safeWrap)));
    #endif

    default_keyword_a_12 = PY_createInteger(10);
    keyword_name_table_13 = (PyObjectContainer*[]){PY_createString("a")};
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "simple_target_keyword", (function_container_simple_target_keyword_1 = PY_createBoxForFunction(simpletargetkeyword_3_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_simple", (function_container_test_simple_2 = PY_createBoxForFunction(testsimple_5_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestCallStar_6();
    keyword_name_var_20 = (PyObjectContainer*[]) {PY_createString("a")};
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_simple", (function_container_test_simple_3 = PY_createBoxForFunction(testsimple_8_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestKeyword_9();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_simple", (function_container_test_simple_4 = PY_createBoxForFunction(testsimple_11_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestStarStar_12();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "__lambda__", (function_container___lambda___5 = PY_createBoxForFunction(lambda_13_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "__lambda__", (function_container___lambda___6 = PY_createBoxForFunction(lambda_15_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "__lambda__", (function_container___lambda___7 = PY_createBoxForFunction(lambda_16_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "__lambda__", (function_container___lambda___8 = PY_createBoxForFunction(lambda_17_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_basic", (function_container_test_basic_9 = PY_createBoxForFunction(testbasic_19_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_with_param", (function_container_test_with_param_10 = PY_createBoxForFunction(testwithparam_21_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_lambda_ception", (function_container_test_lambda_ception_11 = PY_createBoxForFunction(testlambdaception_23_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestLambdaDeclaration_24();
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
    PyObjectContainer** new_args = PY_ARGS_unpackArgTableForUnsafeCall(0, args, info, &argc, 1, keyword_name_table_13, (PyObjectContainer*[]) {default_keyword_a_12});
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

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestCallStar_6(void) {
    // Create Class PY_CLASS_TestCallStar_6 ('TestCallStar' in source code)
    PY_CLASS_TestCallStar_6 = PY_createClassContainer("TestCallStar");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_TestCallStar_6, 1);

    // Create Parent Objects for class 'TestCallStar'
    PY_CLASS_TestCallStar_6 -> parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_14 = PY_getClassAttributeByName(PY_CLASS_TestCallStar_6->parents[0], "__init_subclass__");
    if (init_subclass_14 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_14, PY_createClassWrapper(PY_CLASS_TestCallStar_6), 0, NULL, NULL));
    }

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestCallStar_6, "test_simple", PY_createBoxForFunction(testsimple_5_safeWrap));
}

PyObjectContainer* testsimple_5(PyObjectContainer* self_4) {
    // Source Location: TestCallStar.test_simple
    PyObjectContainer* f_27;

    f_27 = function_container_simple_target_0;

    PyObjectContainer* temporary_16 = PY_STD_list_CREATE(1, PY_createInteger(10));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_4, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_27, NULL, 1, &temporary_16, PY_ARGS_createCallInfo(0, 1, (uint64_t[]) {CALL_STRUCTURE_STAR, 0, 0, 0, 0, 0, 0, 0}, NULL))), PY_createInteger(10)}, NULL));



    return PY_NONE;
}

PyObjectContainer* testsimple_5_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testsimple_5(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testsimple_5(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestKeyword_9(void) {
    // Create Class PY_CLASS_TestKeyword_9 ('TestKeyword' in source code)
    PY_CLASS_TestKeyword_9 = PY_createClassContainer("TestKeyword");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_TestKeyword_9, 1);

    // Create Parent Objects for class 'TestKeyword'
    PY_CLASS_TestKeyword_9 -> parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_17 = PY_getClassAttributeByName(PY_CLASS_TestKeyword_9->parents[0], "__init_subclass__");
    if (init_subclass_17 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_17, PY_createClassWrapper(PY_CLASS_TestKeyword_9), 0, NULL, NULL));
    }

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestKeyword_9, "test_simple", PY_createBoxForFunction(testsimple_8_safeWrap));
}

PyObjectContainer* testsimple_8(PyObjectContainer* self_7) {
    // Source Location: TestKeyword.test_simple
    PyObjectContainer* f_28;

    f_28 = function_container_simple_target_keyword_1;

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_7, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_28, NULL, 0, NULL, NULL)), PY_createInteger(10)}, NULL));

    PyObjectContainer* temporary_21 = PY_createInteger(20);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_7, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_28, NULL, 1, &temporary_21, PY_ARGS_createCallInfo(0, 1, (uint64_t[]) {CALL_STRUCTURE_KEYWORD, 0, 0, 0, 0, 0, 0, 0}, keyword_name_var_20))), PY_createInteger(20)}, NULL));

    PyObjectContainer* temporary_23 = PY_createInteger(20);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_7, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_28, NULL, 1, &temporary_23, NULL)), PY_createInteger(20)}, NULL));



    return PY_NONE;
}

PyObjectContainer* testsimple_8_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testsimple_8(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testsimple_8(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestStarStar_12(void) {
    // Create Class PY_CLASS_TestStarStar_12 ('TestStarStar' in source code)
    PY_CLASS_TestStarStar_12 = PY_createClassContainer("TestStarStar");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_TestStarStar_12, 1);

    // Create Parent Objects for class 'TestStarStar'
    PY_CLASS_TestStarStar_12 -> parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_24 = PY_getClassAttributeByName(PY_CLASS_TestStarStar_12->parents[0], "__init_subclass__");
    if (init_subclass_24 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_24, PY_createClassWrapper(PY_CLASS_TestStarStar_12), 0, NULL, NULL));
    }

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestStarStar_12, "test_simple", PY_createBoxForFunction(testsimple_11_safeWrap));
}

PyObjectContainer* testsimple_11(PyObjectContainer* self_10) {
    // Source Location: TestStarStar.test_simple
    PyObjectContainer* f_29;

    f_29 = function_container_simple_target_keyword_1;

    PyObjectContainer* temporary_26 = PY_STD_dict_CREATE(0);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_10, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_29, NULL, 1, &temporary_26, PY_ARGS_createCallInfo(0, 1, (uint64_t[]) {CALL_STRUCTURE_STAR_STAR, 0, 0, 0, 0, 0, 0, 0}, NULL))), PY_createInteger(10)}, NULL));

    PyObjectContainer* temporary_28 = PY_STD_dict_CREATE(1, PY_createString("a"), PY_createInteger(20));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_10, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_29, NULL, 1, &temporary_28, PY_ARGS_createCallInfo(0, 1, (uint64_t[]) {CALL_STRUCTURE_STAR_STAR, 0, 0, 0, 0, 0, 0, 0}, NULL))), PY_createInteger(20)}, NULL));



    return PY_NONE;
}

PyObjectContainer* testsimple_11_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testsimple_11(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testsimple_11(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* lambda_13(void) {
    // Source Location: TestLambdaDeclaration.__lambda__
    return PY_createInteger(10);
}

PyObjectContainer* lambda_13_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return lambda_13();
}

PyObjectContainer* lambda_15(PyObjectContainer* a_14) {
    // Source Location: TestLambdaDeclaration.__lambda__
    return PY_STD_operator_add(a_14, PY_createInteger(2));
}

PyObjectContainer* lambda_15_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = lambda_15(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = lambda_15(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* lambda_16(void) {
    // Source Location: .__lambda__
    return PY_createInteger(10);
}

PyObjectContainer* lambda_16_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return lambda_16();
}

PyObjectContainer* lambda_17(void) {
    // Source Location: TestLambdaDeclaration.__lambda__
    return function_container___lambda___7;
}

PyObjectContainer* lambda_17_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return lambda_17();
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestLambdaDeclaration_24(void) {
    // Create Class PY_CLASS_TestLambdaDeclaration_24 ('TestLambdaDeclaration' in source code)
    PY_CLASS_TestLambdaDeclaration_24 = PY_createClassContainer("TestLambdaDeclaration");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_TestLambdaDeclaration_24, 1);

    // Create Parent Objects for class 'TestLambdaDeclaration'
    PY_CLASS_TestLambdaDeclaration_24 -> parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_29 = PY_getClassAttributeByName(PY_CLASS_TestLambdaDeclaration_24->parents[0], "__init_subclass__");
    if (init_subclass_29 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_29, PY_createClassWrapper(PY_CLASS_TestLambdaDeclaration_24), 0, NULL, NULL));
    }

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestLambdaDeclaration_24, "test_basic", PY_createBoxForFunction(testbasic_19_safeWrap));
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestLambdaDeclaration_24, "test_with_param", PY_createBoxForFunction(testwithparam_21_safeWrap));
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestLambdaDeclaration_24, "test_lambda_ception", PY_createBoxForFunction(testlambdaception_23_safeWrap));
}

PyObjectContainer* testbasic_19(PyObjectContainer* self_18) {
    // Source Location: TestLambdaDeclaration.test_basic
    PyObjectContainer* x_30;

    x_30 = function_container___lambda___5;

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_18, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(x_30, NULL, 0, NULL, NULL)), PY_createInteger(10)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testbasic_19_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testbasic_19(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testbasic_19(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testwithparam_21(PyObjectContainer* self_20) {
    // Source Location: TestLambdaDeclaration.test_with_param
    PyObjectContainer* x_31;

    x_31 = function_container___lambda___6;

    PyObjectContainer* temporary_32 = PY_createInteger(2);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_20, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(x_31, NULL, 1, &temporary_32, NULL)), PY_createInteger(4)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testwithparam_21_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testwithparam_21(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testwithparam_21(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testlambdaception_23(PyObjectContainer* self_22) {
    // Source Location: TestLambdaDeclaration.test_lambda_ception
    PyObjectContainer* x_32;

    x_32 = function_container___lambda___8;

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_22, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(x_32, NULL, 0, NULL, NULL)), NULL, 0, NULL, NULL)), PY_createInteger(10)}, NULL));



    return PY_NONE;
}

PyObjectContainer* testlambdaception_23_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testlambdaception_23(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testlambdaception_23(self);
    }

    if (info) free(new_args);
    return result;
}

