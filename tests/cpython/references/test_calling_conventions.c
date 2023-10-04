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
PyObjectContainer* function_container___lambda___17;
PyObjectContainer* function_container_test_basic_18;
PyObjectContainer* function_container_test_with_param_19;
PyObjectContainer* function_container_test_lambda_ception_20;
PyObjectContainer* function_container_test_lambda_capture_21;
PyObjectContainer* default_keyword_a_22;
PyObjectContainer** keyword_name_table_23;
PyClassContainer* PY_CLASS_TestFunctionInception_17;
PyClassContainer* PY_CLASS_TestCallStar_20;
PyClassContainer* PY_CLASS_TestKeyword_23;
PyObjectContainer** keyword_name_var_36;
PyClassContainer* PY_CLASS_TestStarStar_26;
PyClassContainer* PY_CLASS_TestLambdaDeclaration_41;



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
    PyObjectContainer* TestLambdaDeclaration_41;
    PyObjectContainer* TestStarStar_26;
    PyObjectContainer* simpletarget_1;
    PyObjectContainer* simpletargetkeyword_3;
    PyObjectContainer* unittest_58;
    PY_CHECK_EXCEPTION(PY_MODULE_unittest_init());
    unittest_58 = PY_MODULE_INSTANCE_unittest;



    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "simple_target", (function_container_simple_target_0 = PY_createBoxForFunction(simpletarget_1_safeWrap)));
    #endif

    default_keyword_a_22 = PY_createInteger(10);
    keyword_name_table_23 = (PyObjectContainer*[]){PY_createString("a")};
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "simple_target_keyword", (function_container_simple_target_keyword_1 = PY_createBoxForFunction(simpletargetkeyword_3_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "target", (function_container_target_2 = PY_createBoxForFunction(target_4_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "target", (function_container_target_3 = PY_createBoxForFunction(target_43_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "target", (function_container_target_4 = PY_createBoxForFunction(target_49_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "target", (function_container_target_5 = PY_createBoxForFunction(target_53_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_basic", (function_container_test_basic_6 = PY_createBoxForFunction(testbasic_10_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_local_capture", (function_container_test_local_capture_7 = PY_createBoxForFunction(testlocalcapture_44_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_local_capture_two_vars", (function_container_test_local_capture_two_vars_8 = PY_createBoxForFunction(testlocalcapturetwovars_50_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_local_capture_with_arg", (function_container_test_local_capture_with_arg_9 = PY_createBoxForFunction(testlocalcapturewitharg_54_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestFunctionInception_17();

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_simple", (function_container_test_simple_10 = PY_createBoxForFunction(testsimple_19_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestCallStar_20();

    keyword_name_var_36 = (PyObjectContainer*[]) {PY_createString("a")};
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
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "__lambda__", (function_container___lambda___17 = PY_createBoxForFunction(lambda_56_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_basic", (function_container_test_basic_18 = PY_createBoxForFunction(testbasic_34_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_with_param", (function_container_test_with_param_19 = PY_createBoxForFunction(testwithparam_36_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_lambda_ception", (function_container_test_lambda_ception_20 = PY_createBoxForFunction(testlambdaception_38_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_calling_conventions, "test_lambda_capture", (function_container_test_lambda_capture_21 = PY_createBoxForFunction(testlambdacapture_57_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestLambdaDeclaration_41();

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
    PyObjectContainer** new_args = PY_ARGS_unpackArgTableForUnsafeCall(0, args, info, &argc, 1, keyword_name_table_23, (PyObjectContainer*[]) {default_keyword_a_22});
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

PyObjectContainer* target_43(PyObjectContainer* self_arg_local_59) {
    // Local capturing resolving
    // extern
    assert(self_arg_local_59 != NULL);
    assert(self_arg_local_59->type == PY_TYPE_PY_IMPL);
    assert(self_arg_local_59->py_type == PY_TYPE_lambda);
    PyObjectContainer** locals = PY_getObjectAttributeByName(self_arg_local_59, "locals")->raw_value;

    // Source Location: TestFunctionInception.target

    return locals[0];


    return PY_NONE;
}

PyObjectContainer* target_43_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self != NULL);
    assert(argc == 0);
    return target_43(self);
}

PyObjectContainer* target_49(PyObjectContainer* self_arg_local_60) {
    // Local capturing resolving
    // extern add
    assert(self_arg_local_60 != NULL);
    assert(self_arg_local_60->type == PY_TYPE_PY_IMPL);
    assert(self_arg_local_60->py_type == PY_TYPE_lambda);
    PyObjectContainer** locals = PY_getObjectAttributeByName(self_arg_local_60, "locals")->raw_value;

    // Source Location: TestFunctionInception.target

    return PY_STD_operator_add(locals[0], locals[1]);


    return PY_NONE;
}

PyObjectContainer* target_49_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self != NULL);
    assert(argc == 0);
    return target_49(self);
}

PyObjectContainer* target_53(PyObjectContainer* self_arg_local_61 , PyObjectContainer* add_52) {
    // Local capturing resolving
    // extern
    assert(self_arg_local_61 != NULL);
    assert(self_arg_local_61->type == PY_TYPE_PY_IMPL);
    assert(self_arg_local_61->py_type == PY_TYPE_lambda);
    PyObjectContainer** locals = PY_getObjectAttributeByName(self_arg_local_61, "locals")->raw_value;

    // Source Location: TestFunctionInception.target

    return PY_STD_operator_add(locals[0], add_52);


    return PY_NONE;
}

PyObjectContainer* target_53_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self != NULL);
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    assert(argc == 1);
    result = target_53(self, new_args[0]);
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestFunctionInception_17(void) {
    // Create Class PY_CLASS_TestFunctionInception_17 ('TestFunctionInception' in source code)
    PY_CLASS_TestFunctionInception_17 = PY_createClassContainer("TestFunctionInception");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_TestFunctionInception_17, 1);

    // Create Parent Objects for class 'TestFunctionInception'
    PY_CLASS_TestFunctionInception_17 -> parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_24 = PY_getClassAttributeByName(PY_CLASS_TestFunctionInception_17->parents[0], "__init_subclass__");
    if (init_subclass_24 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_24, PY_createClassWrapper(PY_CLASS_TestFunctionInception_17), 0, NULL, NULL));
    }

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestFunctionInception_17, "test_basic", PY_createBoxForFunction(testbasic_10_safeWrap));
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestFunctionInception_17, "test_local_capture", PY_createBoxForFunction(testlocalcapture_44_safeWrap));
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestFunctionInception_17, "test_local_capture_two_vars", PY_createBoxForFunction(testlocalcapturetwovars_50_safeWrap));
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestFunctionInception_17, "test_local_capture_with_arg", PY_createBoxForFunction(testlocalcapturewitharg_54_safeWrap));
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

PyObjectContainer* testlocalcapture_44(PyObjectContainer* self_42) {
    // Source Location: TestFunctionInception.test_local_capture
    PyObjectContainer* extern_62;
    PyObjectContainer* target_43;

    extern_62 = PY_createInteger(10);


    target_43 = PY_CREATE_lambda_WRAPPER(function_container_target_3, PY_CREATE_lambda_locals(1, extern_62));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_42, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(target_43, NULL, 0, NULL, NULL)), PY_createInteger(10)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testlocalcapture_44_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testlocalcapture_44(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testlocalcapture_44(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testlocalcapturetwovars_50(PyObjectContainer* self_48) {
    // Source Location: TestFunctionInception.test_local_capture_two_vars
    PyObjectContainer* add_63;
    PyObjectContainer* extern_64;
    PyObjectContainer* target_49;

    extern_64 = PY_createInteger(10);

    add_63 = PY_createInteger(2);


    target_49 = PY_CREATE_lambda_WRAPPER(function_container_target_4, PY_CREATE_lambda_locals(2, extern_64, add_63));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_48, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(target_49, NULL, 0, NULL, NULL)), PY_createInteger(12)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testlocalcapturetwovars_50_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testlocalcapturetwovars_50(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testlocalcapturetwovars_50(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testlocalcapturewitharg_54(PyObjectContainer* self_51) {
    // Source Location: TestFunctionInception.test_local_capture_with_arg
    PyObjectContainer* extern_65;
    PyObjectContainer* target_53;

    extern_65 = PY_createInteger(10);


    target_53 = PY_CREATE_lambda_WRAPPER(function_container_target_5, PY_CREATE_lambda_locals(1, extern_65));
    PyObjectContainer* temporary_29 = PY_createInteger(2);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_51, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(target_53, NULL, 1, &temporary_29, NULL)), PY_createInteger(12)}, NULL));



    return PY_NONE;
}

PyObjectContainer* testlocalcapturewitharg_54_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testlocalcapturewitharg_54(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testlocalcapturewitharg_54(self);
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
    PyObjectContainer* init_subclass_30 = PY_getClassAttributeByName(PY_CLASS_TestCallStar_20->parents[0], "__init_subclass__");
    if (init_subclass_30 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_30, PY_createClassWrapper(PY_CLASS_TestCallStar_20), 0, NULL, NULL));
    }

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestCallStar_20, "test_simple", PY_createBoxForFunction(testsimple_19_safeWrap));
}

PyObjectContainer* testsimple_19(PyObjectContainer* self_18) {
    // Source Location: TestCallStar.test_simple
    PyObjectContainer* f_66;

    f_66 = function_container_simple_target_0;

    PyObjectContainer* temporary_32 = PY_STD_list_CREATE(1, PY_createInteger(10));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_18, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_66, NULL, 1, &temporary_32, PY_ARGS_createCallInfo(0, 1, (uint64_t[]) {CALL_STRUCTURE_STAR, 0, 0, 0, 0, 0, 0, 0}, NULL))), PY_createInteger(10)}, NULL));



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
    PyObjectContainer* init_subclass_33 = PY_getClassAttributeByName(PY_CLASS_TestKeyword_23->parents[0], "__init_subclass__");
    if (init_subclass_33 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_33, PY_createClassWrapper(PY_CLASS_TestKeyword_23), 0, NULL, NULL));
    }

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestKeyword_23, "test_simple", PY_createBoxForFunction(testsimple_22_safeWrap));
}

PyObjectContainer* testsimple_22(PyObjectContainer* self_21) {
    // Source Location: TestKeyword.test_simple
    PyObjectContainer* f_67;

    f_67 = function_container_simple_target_keyword_1;

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_21, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_67, NULL, 0, NULL, NULL)), PY_createInteger(10)}, NULL));

    PyObjectContainer* temporary_37 = PY_createInteger(20);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_21, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_67, NULL, 1, &temporary_37, PY_ARGS_createCallInfo(0, 1, (uint64_t[]) {CALL_STRUCTURE_KEYWORD, 0, 0, 0, 0, 0, 0, 0}, keyword_name_var_36))), PY_createInteger(20)}, NULL));

    PyObjectContainer* temporary_39 = PY_createInteger(20);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_21, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_67, NULL, 1, &temporary_39, NULL)), PY_createInteger(20)}, NULL));



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
    PyObjectContainer* init_subclass_40 = PY_getClassAttributeByName(PY_CLASS_TestStarStar_26->parents[0], "__init_subclass__");
    if (init_subclass_40 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_40, PY_createClassWrapper(PY_CLASS_TestStarStar_26), 0, NULL, NULL));
    }

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestStarStar_26, "test_simple", PY_createBoxForFunction(testsimple_25_safeWrap));
}

PyObjectContainer* testsimple_25(PyObjectContainer* self_24) {
    // Source Location: TestStarStar.test_simple
    PyObjectContainer* f_68;

    f_68 = function_container_simple_target_keyword_1;

    PyObjectContainer* temporary_42 = PY_STD_dict_CREATE(0);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_24, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_68, NULL, 1, &temporary_42, PY_ARGS_createCallInfo(0, 1, (uint64_t[]) {CALL_STRUCTURE_STAR_STAR, 0, 0, 0, 0, 0, 0, 0}, NULL))), PY_createInteger(10)}, NULL));

    PyObjectContainer* temporary_44 = PY_STD_dict_CREATE(1, PY_createString("a"), PY_createInteger(20));
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_24, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_68, NULL, 1, &temporary_44, PY_ARGS_createCallInfo(0, 1, (uint64_t[]) {CALL_STRUCTURE_STAR_STAR, 0, 0, 0, 0, 0, 0, 0}, NULL))), PY_createInteger(20)}, NULL));



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

PyObjectContainer* lambda_56(PyObjectContainer* self_arg_local_69) {
    // Local capturing resolving
    // y
    assert(self_arg_local_69 != NULL);
    assert(self_arg_local_69->type == PY_TYPE_PY_IMPL);
    assert(self_arg_local_69->py_type == PY_TYPE_lambda);
    PyObjectContainer** locals = PY_getObjectAttributeByName(self_arg_local_69, "locals")->raw_value;

    // Source Location: TestLambdaDeclaration.__lambda__
    return locals[0];
}

PyObjectContainer* lambda_56_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self != NULL);
    assert(argc == 0);
    return lambda_56(self);
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestLambdaDeclaration_41(void) {
    // Create Class PY_CLASS_TestLambdaDeclaration_41 ('TestLambdaDeclaration' in source code)
    PY_CLASS_TestLambdaDeclaration_41 = PY_createClassContainer("TestLambdaDeclaration");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_TestLambdaDeclaration_41, 1);

    // Create Parent Objects for class 'TestLambdaDeclaration'
    PY_CLASS_TestLambdaDeclaration_41 -> parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_45 = PY_getClassAttributeByName(PY_CLASS_TestLambdaDeclaration_41->parents[0], "__init_subclass__");
    if (init_subclass_45 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_45, PY_createClassWrapper(PY_CLASS_TestLambdaDeclaration_41), 0, NULL, NULL));
    }

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestLambdaDeclaration_41, "test_basic", PY_createBoxForFunction(testbasic_34_safeWrap));
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestLambdaDeclaration_41, "test_with_param", PY_createBoxForFunction(testwithparam_36_safeWrap));
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestLambdaDeclaration_41, "test_lambda_ception", PY_createBoxForFunction(testlambdaception_38_safeWrap));
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestLambdaDeclaration_41, "test_lambda_capture", PY_createBoxForFunction(testlambdacapture_57_safeWrap));
}

PyObjectContainer* testbasic_34(PyObjectContainer* self_33) {
    // Source Location: TestLambdaDeclaration.test_basic
    PyObjectContainer* x_70;

    x_70 = function_container___lambda___13;

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_33, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(x_70, NULL, 0, NULL, NULL)), PY_createInteger(10)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testbasic_34_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testbasic_34(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testbasic_34(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testwithparam_36(PyObjectContainer* self_35) {
    // Source Location: TestLambdaDeclaration.test_with_param
    PyObjectContainer* x_71;

    x_71 = function_container___lambda___14;

    PyObjectContainer* temporary_48 = PY_createInteger(2);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_35, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(x_71, NULL, 1, &temporary_48, NULL)), PY_createInteger(4)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testwithparam_36_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testwithparam_36(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testwithparam_36(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testlambdaception_38(PyObjectContainer* self_37) {
    // Source Location: TestLambdaDeclaration.test_lambda_ception
    PyObjectContainer* x_72;

    x_72 = function_container___lambda___16;

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_37, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(x_72, NULL, 0, NULL, NULL)), NULL, 0, NULL, NULL)), PY_createInteger(10)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testlambdaception_38_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testlambdaception_38(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testlambdaception_38(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testlambdacapture_57(PyObjectContainer* self_55) {
    // Source Location: TestLambdaDeclaration.test_lambda_capture
    PyObjectContainer* x_73;
    PyObjectContainer* y_74;

    y_74 = PY_createInteger(10);

    x_73 = PY_CREATE_lambda_WRAPPER(function_container___lambda___17, PY_CREATE_lambda_locals(1, y_74));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_55, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(x_73, NULL, 0, NULL, NULL)), PY_createInteger(10)}, NULL));



    return PY_NONE;
}

PyObjectContainer* testlambdacapture_57_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testlambdacapture_57(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testlambdacapture_57(self);
    }

    if (info) free(new_args);
    return result;
}

