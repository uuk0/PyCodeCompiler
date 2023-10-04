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
#include "standard_library/lambdas.h"



// Global Variables
PyObjectContainer* function_container_simple_target_0;
PyObjectContainer* function_container_simple_target_keyword_1;
PyObjectContainer* function_container_target_2;
PyObjectContainer* function_container_target_3;
PyObjectContainer* function_container_test_basic_4;
PyObjectContainer* function_container_test_local_capture_5;
PyObjectContainer* function_container_test_simple_6;
PyObjectContainer* function_container_test_simple_7;
PyObjectContainer* function_container_test_simple_8;
PyObjectContainer* function_container___lambda___9;
PyObjectContainer* function_container___lambda___10;
PyObjectContainer* function_container___lambda___11;
PyObjectContainer* function_container___lambda___12;
PyObjectContainer* function_container_test_basic_13;
PyObjectContainer* function_container_test_with_param_14;
PyObjectContainer* function_container_test_lambda_ception_15;
PyObjectContainer* default_keyword_a_16;
PyObjectContainer** keyword_name_table_17;
PyClassContainer* PY_CLASS_TestFunctionInception_10;
PyClassContainer* PY_CLASS_TestCallStar_13;
PyClassContainer* PY_CLASS_TestKeyword_16;
PyObjectContainer** keyword_name_var_27;
PyClassContainer* PY_CLASS_TestStarStar_19;
PyClassContainer* PY_CLASS_TestLambdaDeclaration_31;



// implementations

PyObjectContainer* PY_MODULE_test_calling_conventions_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_MODULE_INSTANCE_test_calling_conventions = PY_createModuleObject("test_calling_conventions");
    #endif
    PyObjectContainer* TestCallStar_13;
    PyObjectContainer* TestFunctionInception_10;
    PyObjectContainer* TestKeyword_16;
    PyObjectContainer* TestLambdaDeclaration_31;
    PyObjectContainer* TestStarStar_19;
    PyObjectContainer* simpletarget_1;
    PyObjectContainer* simpletargetkeyword_3;
    PyObjectContainer* unittest_35;
    PY_CHECK_EXCEPTION(PY_MODULE_unittest_init());
    unittest_35 = PY_MODULE_INSTANCE_unittest;



    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "simple_target", (function_container_simple_target_0 = PY_createBoxForFunction(simpletarget_1_safeWrap)));
    #endif

    default_keyword_a_16 = PY_createInteger(10);
    keyword_name_table_17 = (PyObjectContainer*[]){PY_createString("a")};
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "simple_target_keyword", (function_container_simple_target_keyword_1 = PY_createBoxForFunction(simpletargetkeyword_3_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "target", (function_container_target_2 = PY_createBoxForFunction(target_4_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "target", (function_container_target_3 = PY_createBoxForFunction(target_33_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_basic", (function_container_test_basic_4 = PY_createBoxForFunction(testbasic_7_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_local_capture", (function_container_test_local_capture_5 = PY_createBoxForFunction(testlocalcapture_34_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestFunctionInception_10();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_simple", (function_container_test_simple_6 = PY_createBoxForFunction(testsimple_12_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestCallStar_13();
    keyword_name_var_27 = (PyObjectContainer*[]) {PY_createString("a")};
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_simple", (function_container_test_simple_7 = PY_createBoxForFunction(testsimple_15_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestKeyword_16();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_simple", (function_container_test_simple_8 = PY_createBoxForFunction(testsimple_18_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestStarStar_19();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "__lambda__", (function_container___lambda___9 = PY_createBoxForFunction(lambda_20_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "__lambda__", (function_container___lambda___10 = PY_createBoxForFunction(lambda_22_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "__lambda__", (function_container___lambda___11 = PY_createBoxForFunction(lambda_23_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "__lambda__", (function_container___lambda___12 = PY_createBoxForFunction(lambda_24_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_basic", (function_container_test_basic_13 = PY_createBoxForFunction(testbasic_26_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_with_param", (function_container_test_with_param_14 = PY_createBoxForFunction(testwithparam_28_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_lambda_ception", (function_container_test_lambda_ception_15 = PY_createBoxForFunction(testlambdaception_30_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestLambdaDeclaration_31();
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
    PyObjectContainer** new_args = PY_ARGS_unpackArgTableForUnsafeCall(0, args, info, &argc, 1, keyword_name_table_17, (PyObjectContainer*[]) {default_keyword_a_16});
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

PyObjectContainer* target_33(PyObjectContainer* self_arg_local_36) {
    // Local capturing resolving
    // extern
    assert(self_arg_local_36 != NULL);
    assert(self_arg_local_36->type == PY_TYPE_PY_IMPL);
    assert(self_arg_local_36->py_type == PY_TYPE_lambda);
    PyObjectContainer** locals = PY_getObjectAttributeByName(self_arg_local_36, "locals")->raw_value;

    // Source Location: TestFunctionInception.target

    return locals[0];


    return PY_NONE;
}

PyObjectContainer* target_33_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self != NULL);
    assert(argc == 0);
    return target_33(self);
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestFunctionInception_10(void) {
    // Create Class PY_CLASS_TestFunctionInception_10 ('TestFunctionInception' in source code)
    PY_CLASS_TestFunctionInception_10 = PY_createClassContainer("TestFunctionInception");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_TestFunctionInception_10, 1);

    // Create Parent Objects for class 'TestFunctionInception'
    PY_CLASS_TestFunctionInception_10 -> parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_18 = PY_getClassAttributeByName(PY_CLASS_TestFunctionInception_10->parents[0], "__init_subclass__");
    if (init_subclass_18 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_18, PY_createClassWrapper(PY_CLASS_TestFunctionInception_10), 0, NULL, NULL));
    }

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestFunctionInception_10, "test_basic", PY_createBoxForFunction(testbasic_7_safeWrap));
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestFunctionInception_10, "test_local_capture", PY_createBoxForFunction(testlocalcapture_34_safeWrap));
}

PyObjectContainer* testbasic_7(PyObjectContainer* self_6) {
    // Source Location: TestFunctionInception.test_basic
    PyObjectContainer* target_4;

    target_4 = function_container_target_2;
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_6, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(target_4, NULL, 0, NULL, NULL)), PY_createInteger(10)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testbasic_7_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testbasic_7(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testbasic_7(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testlocalcapture_34(PyObjectContainer* self_32) {
    // Source Location: TestFunctionInception.test_local_capture
    PyObjectContainer* extern_37;
    PyObjectContainer* target_33;

    extern_37 = PY_createInteger(10);


    target_33 = PY_CREATE_lambda_WRAPPER(function_container_target_3, PY_CREATE_lambda_locals(1, extern_37));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_32, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(target_33, NULL, 0, NULL, NULL)), PY_createInteger(10)}, NULL));



    return PY_NONE;
}

PyObjectContainer* testlocalcapture_34_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testlocalcapture_34(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testlocalcapture_34(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestCallStar_13(void) {
    // Create Class PY_CLASS_TestCallStar_13 ('TestCallStar' in source code)
    PY_CLASS_TestCallStar_13 = PY_createClassContainer("TestCallStar");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_TestCallStar_13, 1);

    // Create Parent Objects for class 'TestCallStar'
    PY_CLASS_TestCallStar_13 -> parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_21 = PY_getClassAttributeByName(PY_CLASS_TestCallStar_13->parents[0], "__init_subclass__");
    if (init_subclass_21 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_21, PY_createClassWrapper(PY_CLASS_TestCallStar_13), 0, NULL, NULL));
    }

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestCallStar_13, "test_simple", PY_createBoxForFunction(testsimple_12_safeWrap));
}

PyObjectContainer* testsimple_12(PyObjectContainer* self_11) {
    // Source Location: TestCallStar.test_simple
    PyObjectContainer* f_38;

    f_38 = function_container_simple_target_0;

    PyObjectContainer* temporary_23 = PY_STD_list_CREATE(1, PY_createInteger(10));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_11, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_38, NULL, 1, &temporary_23, PY_ARGS_createCallInfo(0, 1, (uint64_t[]) {CALL_STRUCTURE_STAR, 0, 0, 0, 0, 0, 0, 0}, NULL))), PY_createInteger(10)}, NULL));



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

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestKeyword_16(void) {
    // Create Class PY_CLASS_TestKeyword_16 ('TestKeyword' in source code)
    PY_CLASS_TestKeyword_16 = PY_createClassContainer("TestKeyword");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_TestKeyword_16, 1);

    // Create Parent Objects for class 'TestKeyword'
    PY_CLASS_TestKeyword_16 -> parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_24 = PY_getClassAttributeByName(PY_CLASS_TestKeyword_16->parents[0], "__init_subclass__");
    if (init_subclass_24 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_24, PY_createClassWrapper(PY_CLASS_TestKeyword_16), 0, NULL, NULL));
    }

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestKeyword_16, "test_simple", PY_createBoxForFunction(testsimple_15_safeWrap));
}

PyObjectContainer* testsimple_15(PyObjectContainer* self_14) {
    // Source Location: TestKeyword.test_simple
    PyObjectContainer* f_39;

    f_39 = function_container_simple_target_keyword_1;

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_14, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_39, NULL, 0, NULL, NULL)), PY_createInteger(10)}, NULL));

    PyObjectContainer* temporary_28 = PY_createInteger(20);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_14, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_39, NULL, 1, &temporary_28, PY_ARGS_createCallInfo(0, 1, (uint64_t[]) {CALL_STRUCTURE_KEYWORD, 0, 0, 0, 0, 0, 0, 0}, keyword_name_var_27))), PY_createInteger(20)}, NULL));

    PyObjectContainer* temporary_30 = PY_createInteger(20);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_14, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_39, NULL, 1, &temporary_30, NULL)), PY_createInteger(20)}, NULL));



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

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestStarStar_19(void) {
    // Create Class PY_CLASS_TestStarStar_19 ('TestStarStar' in source code)
    PY_CLASS_TestStarStar_19 = PY_createClassContainer("TestStarStar");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_TestStarStar_19, 1);

    // Create Parent Objects for class 'TestStarStar'
    PY_CLASS_TestStarStar_19 -> parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_31 = PY_getClassAttributeByName(PY_CLASS_TestStarStar_19->parents[0], "__init_subclass__");
    if (init_subclass_31 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_31, PY_createClassWrapper(PY_CLASS_TestStarStar_19), 0, NULL, NULL));
    }

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestStarStar_19, "test_simple", PY_createBoxForFunction(testsimple_18_safeWrap));
}

PyObjectContainer* testsimple_18(PyObjectContainer* self_17) {
    // Source Location: TestStarStar.test_simple
    PyObjectContainer* f_40;

    f_40 = function_container_simple_target_keyword_1;

    PyObjectContainer* temporary_33 = PY_STD_dict_CREATE(0);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_17, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_40, NULL, 1, &temporary_33, PY_ARGS_createCallInfo(0, 1, (uint64_t[]) {CALL_STRUCTURE_STAR_STAR, 0, 0, 0, 0, 0, 0, 0}, NULL))), PY_createInteger(10)}, NULL));

    PyObjectContainer* temporary_35 = PY_STD_dict_CREATE(1, PY_createString("a"), PY_createInteger(20));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_17, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_40, NULL, 1, &temporary_35, PY_ARGS_createCallInfo(0, 1, (uint64_t[]) {CALL_STRUCTURE_STAR_STAR, 0, 0, 0, 0, 0, 0, 0}, NULL))), PY_createInteger(20)}, NULL));



    return PY_NONE;
}

PyObjectContainer* testsimple_18_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testsimple_18(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testsimple_18(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* lambda_20(void) {
    // Source Location: TestLambdaDeclaration.__lambda__
    return PY_createInteger(10);
}

PyObjectContainer* lambda_20_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return lambda_20();
}

PyObjectContainer* lambda_22(PyObjectContainer* a_21) {
    // Source Location: TestLambdaDeclaration.__lambda__
    return PY_STD_operator_add(a_21, PY_createInteger(2));
}

PyObjectContainer* lambda_22_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = lambda_22(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = lambda_22(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* lambda_23(void) {
    // Source Location: .__lambda__
    return PY_createInteger(10);
}

PyObjectContainer* lambda_23_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return lambda_23();
}

PyObjectContainer* lambda_24(void) {
    // Source Location: TestLambdaDeclaration.__lambda__
    return function_container___lambda___11;
}

PyObjectContainer* lambda_24_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return lambda_24();
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestLambdaDeclaration_31(void) {
    // Create Class PY_CLASS_TestLambdaDeclaration_31 ('TestLambdaDeclaration' in source code)
    PY_CLASS_TestLambdaDeclaration_31 = PY_createClassContainer("TestLambdaDeclaration");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_TestLambdaDeclaration_31, 1);

    // Create Parent Objects for class 'TestLambdaDeclaration'
    PY_CLASS_TestLambdaDeclaration_31 -> parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_36 = PY_getClassAttributeByName(PY_CLASS_TestLambdaDeclaration_31->parents[0], "__init_subclass__");
    if (init_subclass_36 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_36, PY_createClassWrapper(PY_CLASS_TestLambdaDeclaration_31), 0, NULL, NULL));
    }

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestLambdaDeclaration_31, "test_basic", PY_createBoxForFunction(testbasic_26_safeWrap));
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestLambdaDeclaration_31, "test_with_param", PY_createBoxForFunction(testwithparam_28_safeWrap));
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestLambdaDeclaration_31, "test_lambda_ception", PY_createBoxForFunction(testlambdaception_30_safeWrap));
}

PyObjectContainer* testbasic_26(PyObjectContainer* self_25) {
    // Source Location: TestLambdaDeclaration.test_basic
    PyObjectContainer* x_41;

    x_41 = function_container___lambda___9;

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_25, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(x_41, NULL, 0, NULL, NULL)), PY_createInteger(10)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testbasic_26_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testbasic_26(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testbasic_26(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testwithparam_28(PyObjectContainer* self_27) {
    // Source Location: TestLambdaDeclaration.test_with_param
    PyObjectContainer* x_42;

    x_42 = function_container___lambda___10;

    PyObjectContainer* temporary_39 = PY_createInteger(2);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_27, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(x_42, NULL, 1, &temporary_39, NULL)), PY_createInteger(4)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testwithparam_28_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testwithparam_28(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testwithparam_28(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testlambdaception_30(PyObjectContainer* self_29) {
    // Source Location: TestLambdaDeclaration.test_lambda_ception
    PyObjectContainer* x_43;

    x_43 = function_container___lambda___12;

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_29, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(x_43, NULL, 0, NULL, NULL)), NULL, 0, NULL, NULL)), PY_createInteger(10)}, NULL));



    return PY_NONE;
}

PyObjectContainer* testlambdaception_30_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testlambdaception_30(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testlambdaception_30(self);
    }

    if (info) free(new_args);
    return result;
}

