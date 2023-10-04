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
PyObjectContainer* function_container_target_4;
PyObjectContainer* function_container_target_5;
PyObjectContainer* function_container_test_basic_6;
PyObjectContainer* function_container_test_local_capture_7;
PyObjectContainer* function_container_test_local_capture_two_vars_8;
PyObjectContainer* function_container_test_local_capture_with_arg_9;
PyObjectContainer* function_container_test_simple_10;
PyObjectContainer* function_container_test_simple_11;
PyObjectContainer* function_container_test_simple_12;
PyObjectContainer* function_container___lambda___13;
PyObjectContainer* function_container___lambda___14;
PyObjectContainer* function_container___lambda___15;
PyObjectContainer* function_container___lambda___16;
PyObjectContainer* function_container_test_basic_17;
PyObjectContainer* function_container_test_with_param_18;
PyObjectContainer* function_container_test_lambda_ception_19;
PyObjectContainer* default_keyword_a_20;
PyObjectContainer** keyword_name_table_21;
PyClassContainer* PY_CLASS_TestFunctionInception_17;
PyClassContainer* PY_CLASS_TestCallStar_20;
PyClassContainer* PY_CLASS_TestKeyword_23;
PyObjectContainer** keyword_name_var_34;
PyClassContainer* PY_CLASS_TestStarStar_26;
PyClassContainer* PY_CLASS_TestLambdaDeclaration_38;



// implementations

PyObjectContainer* PY_MODULE_test_calling_conventions_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_MODULE_INSTANCE_test_calling_conventions = PY_createModuleObject("test_calling_conventions");
    #endif
    PyObjectContainer* TestCallStar_20;
    PyObjectContainer* TestFunctionInception_17;
    PyObjectContainer* TestKeyword_23;
    PyObjectContainer* TestLambdaDeclaration_38;
    PyObjectContainer* TestStarStar_26;
    PyObjectContainer* simpletarget_1;
    PyObjectContainer* simpletargetkeyword_3;
    PyObjectContainer* unittest_52;
    PY_CHECK_EXCEPTION(PY_MODULE_unittest_init());
    unittest_52 = PY_MODULE_INSTANCE_unittest;



    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "simple_target", (function_container_simple_target_0 = PY_createBoxForFunction(simpletarget_1_safeWrap)));
    #endif

    default_keyword_a_20 = PY_createInteger(10);
    keyword_name_table_21 = (PyObjectContainer*[]){PY_createString("a")};
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "simple_target_keyword", (function_container_simple_target_keyword_1 = PY_createBoxForFunction(simpletargetkeyword_3_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "target", (function_container_target_2 = PY_createBoxForFunction(target_4_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "target", (function_container_target_3 = PY_createBoxForFunction(target_40_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "target", (function_container_target_4 = PY_createBoxForFunction(target_46_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "target", (function_container_target_5 = PY_createBoxForFunction(target_50_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_basic", (function_container_test_basic_6 = PY_createBoxForFunction(testbasic_10_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_local_capture", (function_container_test_local_capture_7 = PY_createBoxForFunction(testlocalcapture_41_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_local_capture_two_vars", (function_container_test_local_capture_two_vars_8 = PY_createBoxForFunction(testlocalcapturetwovars_47_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_local_capture_with_arg", (function_container_test_local_capture_with_arg_9 = PY_createBoxForFunction(testlocalcapturewitharg_51_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestFunctionInception_17();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_simple", (function_container_test_simple_10 = PY_createBoxForFunction(testsimple_19_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestCallStar_20();
    keyword_name_var_34 = (PyObjectContainer*[]) {PY_createString("a")};
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_simple", (function_container_test_simple_11 = PY_createBoxForFunction(testsimple_22_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestKeyword_23();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_simple", (function_container_test_simple_12 = PY_createBoxForFunction(testsimple_25_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestStarStar_26();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "__lambda__", (function_container___lambda___13 = PY_createBoxForFunction(lambda_27_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "__lambda__", (function_container___lambda___14 = PY_createBoxForFunction(lambda_29_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "__lambda__", (function_container___lambda___15 = PY_createBoxForFunction(lambda_30_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "__lambda__", (function_container___lambda___16 = PY_createBoxForFunction(lambda_31_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_basic", (function_container_test_basic_17 = PY_createBoxForFunction(testbasic_33_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_with_param", (function_container_test_with_param_18 = PY_createBoxForFunction(testwithparam_35_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_lambda_ception", (function_container_test_lambda_ception_19 = PY_createBoxForFunction(testlambdaception_37_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestLambdaDeclaration_38();
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
    PyObjectContainer** new_args = PY_ARGS_unpackArgTableForUnsafeCall(0, args, info, &argc, 1, keyword_name_table_21, (PyObjectContainer*[]) {default_keyword_a_20});
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

PyObjectContainer* target_40(PyObjectContainer* self_arg_local_53) {
    // Local capturing resolving
    // extern
    assert(self_arg_local_53 != NULL);
    assert(self_arg_local_53->type == PY_TYPE_PY_IMPL);
    assert(self_arg_local_53->py_type == PY_TYPE_lambda);
    PyObjectContainer** locals = PY_getObjectAttributeByName(self_arg_local_53, "locals")->raw_value;

    // Source Location: TestFunctionInception.target

    return locals[0];


    return PY_NONE;
}

PyObjectContainer* target_40_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self != NULL);
    assert(argc == 0);
    return target_40(self);
}

PyObjectContainer* target_46(PyObjectContainer* self_arg_local_54) {
    // Local capturing resolving
    // extern add
    assert(self_arg_local_54 != NULL);
    assert(self_arg_local_54->type == PY_TYPE_PY_IMPL);
    assert(self_arg_local_54->py_type == PY_TYPE_lambda);
    PyObjectContainer** locals = PY_getObjectAttributeByName(self_arg_local_54, "locals")->raw_value;

    // Source Location: TestFunctionInception.target

    return PY_STD_operator_add(locals[0], locals[1]);


    return PY_NONE;
}

PyObjectContainer* target_46_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self != NULL);
    assert(argc == 0);
    return target_46(self);
}

PyObjectContainer* target_50(PyObjectContainer* self_arg_local_55 , PyObjectContainer* add_49) {
    // Local capturing resolving
    // extern
    assert(self_arg_local_55 != NULL);
    assert(self_arg_local_55->type == PY_TYPE_PY_IMPL);
    assert(self_arg_local_55->py_type == PY_TYPE_lambda);
    PyObjectContainer** locals = PY_getObjectAttributeByName(self_arg_local_55, "locals")->raw_value;

    // Source Location: TestFunctionInception.target

    return PY_STD_operator_add(locals[0], add_49);


    return PY_NONE;
}

PyObjectContainer* target_50_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self != NULL);
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    assert(argc == 1);
    result = target_50(self, new_args[0]);
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestFunctionInception_17(void) {
    // Create Class PY_CLASS_TestFunctionInception_17 ('TestFunctionInception' in source code)
    PY_CLASS_TestFunctionInception_17 = PY_createClassContainer("TestFunctionInception");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_TestFunctionInception_17, 1);

    // Create Parent Objects for class 'TestFunctionInception'
    PY_CLASS_TestFunctionInception_17 -> parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_22 = PY_getClassAttributeByName(PY_CLASS_TestFunctionInception_17->parents[0], "__init_subclass__");
    if (init_subclass_22 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_22, PY_createClassWrapper(PY_CLASS_TestFunctionInception_17), 0, NULL, NULL));
    }

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestFunctionInception_17, "test_basic", PY_createBoxForFunction(testbasic_10_safeWrap));
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestFunctionInception_17, "test_local_capture", PY_createBoxForFunction(testlocalcapture_41_safeWrap));
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestFunctionInception_17, "test_local_capture_two_vars", PY_createBoxForFunction(testlocalcapturetwovars_47_safeWrap));
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestFunctionInception_17, "test_local_capture_with_arg", PY_createBoxForFunction(testlocalcapturewitharg_51_safeWrap));
}

PyObjectContainer* testbasic_10(PyObjectContainer* self_9) {
    // Source Location: TestFunctionInception.test_basic
    PyObjectContainer* target_4;

    target_4 = function_container_target_2;
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_9, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(target_4, NULL, 0, NULL, NULL)), PY_createInteger(10)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testbasic_10_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testbasic_10(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testbasic_10(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testlocalcapture_41(PyObjectContainer* self_39) {
    // Source Location: TestFunctionInception.test_local_capture
    PyObjectContainer* extern_56;
    PyObjectContainer* target_40;

    extern_56 = PY_createInteger(10);


    target_40 = PY_CREATE_lambda_WRAPPER(function_container_target_3, PY_CREATE_lambda_locals(1, extern_56));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_39, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(target_40, NULL, 0, NULL, NULL)), PY_createInteger(10)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testlocalcapture_41_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testlocalcapture_41(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testlocalcapture_41(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testlocalcapturetwovars_47(PyObjectContainer* self_45) {
    // Source Location: TestFunctionInception.test_local_capture_two_vars
    PyObjectContainer* add_57;
    PyObjectContainer* extern_58;
    PyObjectContainer* target_46;

    extern_58 = PY_createInteger(10);

    add_57 = PY_createInteger(2);


    target_46 = PY_CREATE_lambda_WRAPPER(function_container_target_4, PY_CREATE_lambda_locals(2, extern_58, add_57));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_45, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(target_46, NULL, 0, NULL, NULL)), PY_createInteger(12)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testlocalcapturetwovars_47_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testlocalcapturetwovars_47(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testlocalcapturetwovars_47(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testlocalcapturewitharg_51(PyObjectContainer* self_48) {
    // Source Location: TestFunctionInception.test_local_capture_with_arg
    PyObjectContainer* extern_59;
    PyObjectContainer* target_50;

    extern_59 = PY_createInteger(10);


    target_50 = PY_CREATE_lambda_WRAPPER(function_container_target_5, PY_CREATE_lambda_locals(1, extern_59));
    PyObjectContainer* temporary_27 = PY_createInteger(2);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_48, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(target_50, NULL, 1, &temporary_27, NULL)), PY_createInteger(12)}, NULL));



    return PY_NONE;
}

PyObjectContainer* testlocalcapturewitharg_51_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testlocalcapturewitharg_51(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testlocalcapturewitharg_51(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestCallStar_20(void) {
    // Create Class PY_CLASS_TestCallStar_20 ('TestCallStar' in source code)
    PY_CLASS_TestCallStar_20 = PY_createClassContainer("TestCallStar");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_TestCallStar_20, 1);

    // Create Parent Objects for class 'TestCallStar'
    PY_CLASS_TestCallStar_20 -> parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_28 = PY_getClassAttributeByName(PY_CLASS_TestCallStar_20->parents[0], "__init_subclass__");
    if (init_subclass_28 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_28, PY_createClassWrapper(PY_CLASS_TestCallStar_20), 0, NULL, NULL));
    }

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestCallStar_20, "test_simple", PY_createBoxForFunction(testsimple_19_safeWrap));
}

PyObjectContainer* testsimple_19(PyObjectContainer* self_18) {
    // Source Location: TestCallStar.test_simple
    PyObjectContainer* f_60;

    f_60 = function_container_simple_target_0;

    PyObjectContainer* temporary_30 = PY_STD_list_CREATE(1, PY_createInteger(10));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_18, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_60, NULL, 1, &temporary_30, PY_ARGS_createCallInfo(0, 1, (uint64_t[]) {CALL_STRUCTURE_STAR, 0, 0, 0, 0, 0, 0, 0}, NULL))), PY_createInteger(10)}, NULL));



    return PY_NONE;
}

PyObjectContainer* testsimple_19_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testsimple_19(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testsimple_19(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestKeyword_23(void) {
    // Create Class PY_CLASS_TestKeyword_23 ('TestKeyword' in source code)
    PY_CLASS_TestKeyword_23 = PY_createClassContainer("TestKeyword");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_TestKeyword_23, 1);

    // Create Parent Objects for class 'TestKeyword'
    PY_CLASS_TestKeyword_23 -> parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_31 = PY_getClassAttributeByName(PY_CLASS_TestKeyword_23->parents[0], "__init_subclass__");
    if (init_subclass_31 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_31, PY_createClassWrapper(PY_CLASS_TestKeyword_23), 0, NULL, NULL));
    }

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestKeyword_23, "test_simple", PY_createBoxForFunction(testsimple_22_safeWrap));
}

PyObjectContainer* testsimple_22(PyObjectContainer* self_21) {
    // Source Location: TestKeyword.test_simple
    PyObjectContainer* f_61;

    f_61 = function_container_simple_target_keyword_1;

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_21, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_61, NULL, 0, NULL, NULL)), PY_createInteger(10)}, NULL));

    PyObjectContainer* temporary_35 = PY_createInteger(20);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_21, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_61, NULL, 1, &temporary_35, PY_ARGS_createCallInfo(0, 1, (uint64_t[]) {CALL_STRUCTURE_KEYWORD, 0, 0, 0, 0, 0, 0, 0}, keyword_name_var_34))), PY_createInteger(20)}, NULL));

    PyObjectContainer* temporary_37 = PY_createInteger(20);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_21, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_61, NULL, 1, &temporary_37, NULL)), PY_createInteger(20)}, NULL));



    return PY_NONE;
}

PyObjectContainer* testsimple_22_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testsimple_22(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testsimple_22(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestStarStar_26(void) {
    // Create Class PY_CLASS_TestStarStar_26 ('TestStarStar' in source code)
    PY_CLASS_TestStarStar_26 = PY_createClassContainer("TestStarStar");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_TestStarStar_26, 1);

    // Create Parent Objects for class 'TestStarStar'
    PY_CLASS_TestStarStar_26 -> parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_38 = PY_getClassAttributeByName(PY_CLASS_TestStarStar_26->parents[0], "__init_subclass__");
    if (init_subclass_38 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_38, PY_createClassWrapper(PY_CLASS_TestStarStar_26), 0, NULL, NULL));
    }

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestStarStar_26, "test_simple", PY_createBoxForFunction(testsimple_25_safeWrap));
}

PyObjectContainer* testsimple_25(PyObjectContainer* self_24) {
    // Source Location: TestStarStar.test_simple
    PyObjectContainer* f_62;

    f_62 = function_container_simple_target_keyword_1;

    PyObjectContainer* temporary_40 = PY_STD_dict_CREATE(0);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_24, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_62, NULL, 1, &temporary_40, PY_ARGS_createCallInfo(0, 1, (uint64_t[]) {CALL_STRUCTURE_STAR_STAR, 0, 0, 0, 0, 0, 0, 0}, NULL))), PY_createInteger(10)}, NULL));

    PyObjectContainer* temporary_42 = PY_STD_dict_CREATE(1, PY_createString("a"), PY_createInteger(20));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_24, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_62, NULL, 1, &temporary_42, PY_ARGS_createCallInfo(0, 1, (uint64_t[]) {CALL_STRUCTURE_STAR_STAR, 0, 0, 0, 0, 0, 0, 0}, NULL))), PY_createInteger(20)}, NULL));



    return PY_NONE;
}

PyObjectContainer* testsimple_25_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testsimple_25(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testsimple_25(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* lambda_27(void) {
    // Source Location: TestLambdaDeclaration.__lambda__
    return PY_createInteger(10);
}

PyObjectContainer* lambda_27_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return lambda_27();
}

PyObjectContainer* lambda_29(PyObjectContainer* a_28) {
    // Source Location: TestLambdaDeclaration.__lambda__
    return PY_STD_operator_add(a_28, PY_createInteger(2));
}

PyObjectContainer* lambda_29_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = lambda_29(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = lambda_29(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* lambda_30(void) {
    // Source Location: .__lambda__
    return PY_createInteger(10);
}

PyObjectContainer* lambda_30_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return lambda_30();
}

PyObjectContainer* lambda_31(void) {
    // Source Location: TestLambdaDeclaration.__lambda__
    return function_container___lambda___15;
}

PyObjectContainer* lambda_31_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return lambda_31();
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestLambdaDeclaration_38(void) {
    // Create Class PY_CLASS_TestLambdaDeclaration_38 ('TestLambdaDeclaration' in source code)
    PY_CLASS_TestLambdaDeclaration_38 = PY_createClassContainer("TestLambdaDeclaration");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_TestLambdaDeclaration_38, 1);

    // Create Parent Objects for class 'TestLambdaDeclaration'
    PY_CLASS_TestLambdaDeclaration_38 -> parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_43 = PY_getClassAttributeByName(PY_CLASS_TestLambdaDeclaration_38->parents[0], "__init_subclass__");
    if (init_subclass_43 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_43, PY_createClassWrapper(PY_CLASS_TestLambdaDeclaration_38), 0, NULL, NULL));
    }

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestLambdaDeclaration_38, "test_basic", PY_createBoxForFunction(testbasic_33_safeWrap));
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestLambdaDeclaration_38, "test_with_param", PY_createBoxForFunction(testwithparam_35_safeWrap));
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestLambdaDeclaration_38, "test_lambda_ception", PY_createBoxForFunction(testlambdaception_37_safeWrap));
}

PyObjectContainer* testbasic_33(PyObjectContainer* self_32) {
    // Source Location: TestLambdaDeclaration.test_basic
    PyObjectContainer* x_63;

    x_63 = function_container___lambda___13;

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_32, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(x_63, NULL, 0, NULL, NULL)), PY_createInteger(10)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testbasic_33_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testbasic_33(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testbasic_33(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testwithparam_35(PyObjectContainer* self_34) {
    // Source Location: TestLambdaDeclaration.test_with_param
    PyObjectContainer* x_64;

    x_64 = function_container___lambda___14;

    PyObjectContainer* temporary_46 = PY_createInteger(2);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_34, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(x_64, NULL, 1, &temporary_46, NULL)), PY_createInteger(4)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testwithparam_35_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testwithparam_35(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testwithparam_35(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testlambdaception_37(PyObjectContainer* self_36) {
    // Source Location: TestLambdaDeclaration.test_lambda_ception
    PyObjectContainer* x_65;

    x_65 = function_container___lambda___16;

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_36, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(x_65, NULL, 0, NULL, NULL)), NULL, 0, NULL, NULL)), PY_createInteger(10)}, NULL));



    return PY_NONE;
}

PyObjectContainer* testlambdaception_37_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testlambdaception_37(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testlambdaception_37(self);
    }

    if (info) free(new_args);
    return result;
}

