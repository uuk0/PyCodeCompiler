#include <stdlib.h>

#include "pyinclude.h"
#include "standard_library/config.h"

#include "standard_library/init.h"
#include "standard_library/exceptions.h"

#ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
#include "standard_library/importhelper.h"
#endif

#include "test_class_conventions.h"

#ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
PyObjectContainer* PY_MODULE_INSTANCE_test_class_conventions;
#endif

// code compiled from python to c via PyCodeCompiler

#include "standard_library/modules/unittest.h"
#include <assert.h>



// Global Variables
PyObjectContainer* function_container___call___0;
PyObjectContainer* function_container___init___1;
PyObjectContainer* function_container___call___2;
PyObjectContainer* function_container_test_basic_3;
PyObjectContainer* function_container_test_attribute_4;
PyObjectContainer* function_container_get_5;
PyObjectContainer* function_container_test_basic_6;
PyObjectContainer* function_container_get_7;
PyObjectContainer* function_container_target_8;
PyObjectContainer* function_container_test_basic_9;
PyClassContainer* PY_CLASS_TestClassCallable_13;
PyClassContainer* PY_CLASS_TestClassInClass_20;
PyClassContainer* PY_CLASS_TestClassInFunction_27;



// implementations

PyObjectContainer* PY_MODULE_test_class_conventions_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_MODULE_INSTANCE_test_class_conventions = PY_createModuleObject("test_class_conventions");
    #endif
    PyObjectContainer* PY_CLASS_A_28;
    PyObjectContainer* PY_CLASS_B_29;
    PyObjectContainer* PY_CLASS_Test_30;
    PyObjectContainer* PY_CLASS_X_31;
    PyObjectContainer* TestClassCallable_13;
    PyObjectContainer* TestClassInClass_20;
    PyObjectContainer* TestClassInFunction_27;
    PyObjectContainer* unittest_32;
    function_container___call___0 = PY_createBoxForFunction(call_1_safeWrap);
    function_container___init___1 = PY_createBoxForFunction(init_5_safeWrap);
    function_container___call___2 = PY_createBoxForFunction(call_7_safeWrap);
    function_container_test_basic_3 = PY_createBoxForFunction(testbasic_10_safeWrap);
    function_container_test_attribute_4 = PY_createBoxForFunction(testattribute_12_safeWrap);
    function_container_get_5 = PY_createBoxForFunction(get_15_safeWrap);
    function_container_test_basic_6 = PY_createBoxForFunction(testbasic_19_safeWrap);
    function_container_get_7 = PY_createBoxForFunction(get_22_safeWrap);
    function_container_target_8 = PY_createBoxForFunction(target_24_safeWrap);
    function_container_test_basic_9 = PY_createBoxForFunction(testbasic_26_safeWrap);
    PY_CHECK_EXCEPTION(PY_MODULE_unittest_init());
    unittest_32 = PY_MODULE_INSTANCE_unittest;



    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_class_conventions, "__call__", (function_container___call___0 = PY_createBoxForFunction(call_1_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_class_conventions, "__init__", (function_container___init___1 = PY_createBoxForFunction(init_5_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_class_conventions, "__call__", (function_container___call___2 = PY_createBoxForFunction(call_7_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_class_conventions, "test_basic", (function_container_test_basic_3 = PY_createBoxForFunction(testbasic_10_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_class_conventions, "test_attribute", (function_container_test_attribute_4 = PY_createBoxForFunction(testattribute_12_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestClassCallable_13(&PY_CLASS_TestClassCallable_13);

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_class_conventions, "get", (function_container_get_5 = PY_createBoxForFunction(get_15_safeWrap)));
    #endif


    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_class_conventions, "test_basic", (function_container_test_basic_6 = PY_createBoxForFunction(testbasic_19_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestClassInClass_20(&PY_CLASS_TestClassInClass_20);

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_class_conventions, "get", (function_container_get_7 = PY_createBoxForFunction(get_22_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_class_conventions, "target", (function_container_target_8 = PY_createBoxForFunction(target_24_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_class_conventions, "test_basic", (function_container_test_basic_9 = PY_createBoxForFunction(testbasic_26_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestClassInFunction_27(&PY_CLASS_TestClassInFunction_27);

    if (PY_unpackBoolean(PY_CHECK_EXCEPTION(PY_CHECK_EXCEPTION(PY_STD_string_eq_fast (PY_createString("__main__") , PY_createString("__main__")))))) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(PY_MODULE_INSTANCE_unittest, "main"), NULL, 0, NULL, NULL));
    }
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_exposeModuleObject(PY_MODULE_INSTANCE_test_class_conventions);
    #endif
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_Test_2(PyClassContainer** cls) {
    // Create Class PY_CLASS_Test_2 ('Test' in source code)
    *cls = PY_createClassContainer("Test");
    PY_ClassContainer_AllocateParentArray(*cls, 1);

    // Create Parent Objects for class 'Test'
    (*cls)->parents[0] = PY_TYPE_OBJECT;

    // Attributes
    PY_setClassAttributeByNameOrCreate(*cls, "__call__", PY_createBoxForFunction(call_1_safeWrap));


    return PY_NONE;
}

PyObjectContainer* call_1(PyObjectContainer* self_0) {
    // Source Location: Test.__call__

    return PY_createInteger(10);


    return PY_NONE;
}

PyObjectContainer* call_1_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = call_1(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = call_1(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_Test_8(PyClassContainer** cls) {
    // Create Class PY_CLASS_Test_8 ('Test' in source code)
    *cls = PY_createClassContainer("Test");
    PY_ClassContainer_AllocateParentArray(*cls, 1);

    // Create Parent Objects for class 'Test'
    (*cls)->parents[0] = PY_TYPE_OBJECT;
    PY_ClassContainer_DeclareObjectAttribute(*cls, "value");

    // Attributes
    PY_setClassAttributeByNameOrCreate(*cls, "__init__", PY_createBoxForFunction(init_5_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "__call__", PY_createBoxForFunction(call_7_safeWrap));



    return PY_NONE;
}

PyObjectContainer* init_5(PyObjectContainer* self_3 , PyObjectContainer* value_4) {
    // Source Location: Test.__init__

    PyObjectContainer* temp_10 = value_4;
    PY_setObjectAttributeByName(self_3, "value", temp_10);


    return PY_NONE;
}

PyObjectContainer* init_5_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 2);
        result = init_5(new_args[0], new_args[1]);
    }
    else {
        assert(argc == 1);
        result = init_5(self , new_args[0]);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* call_7(PyObjectContainer* self_6) {
    // Source Location: Test.__call__

    return PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_6, "value");


    return PY_NONE;
}

PyObjectContainer* call_7_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = call_7(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = call_7(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestClassCallable_13(PyClassContainer** cls) {
    // Create Class PY_CLASS_TestClassCallable_13 ('TestClassCallable' in source code)
    *cls = PY_createClassContainer("TestClassCallable");
    PY_ClassContainer_AllocateParentArray(*cls, 1);

    // Create Parent Objects for class 'TestClassCallable'
    (*cls)->parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_11 = PY_getClassAttributeByName((*cls)->parents[0], "__init_subclass__");
    if (init_subclass_11 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_11, PY_createClassWrapper(*cls), 0, NULL, NULL));
    }
    PY_ClassContainer_EnsureObjectAttributesDeclaredFor(*cls, (*cls)->parents[0]);

    // Attributes
    PY_setClassAttributeByNameOrCreate(*cls, "test_basic", PY_createBoxForFunction(testbasic_10_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_attribute", PY_createBoxForFunction(testattribute_12_safeWrap));



    return PY_NONE;
}

PyObjectContainer* testbasic_10(PyObjectContainer* self_9) {
    // Source Location: TestClassCallable.test_basic
    PyObjectContainer* Test_2;
    PyObjectContainer* a_33;

    Test_2 = PY_createClass("Test", PY_CLASS_INIT_PY_CLASS_Test_2);
    a_33 = PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(Test_2, NULL, 0, NULL, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_9, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(a_33, NULL, 0, NULL, NULL)), PY_createInteger(10)}, NULL));


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

PyObjectContainer* testattribute_12(PyObjectContainer* self_11) {
    // Source Location: TestClassCallable.test_attribute
    PyObjectContainer* Test_8;
    PyObjectContainer* a_34;

    Test_8 = PY_createClass("Test", PY_CLASS_INIT_PY_CLASS_Test_8);
    PyObjectContainer* temporary_13 = PY_createInteger(20);
    a_34 = PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(Test_8, NULL, 1, &temporary_13, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_11, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(a_34, NULL, 0, NULL, NULL)), PY_createInteger(20)}, NULL));



    return PY_NONE;
}

PyObjectContainer* testattribute_12_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testattribute_12(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testattribute_12(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_B_16(PyClassContainer** cls) {
    // Create Class PY_CLASS_B_16 ('B' in source code)
    *cls = PY_createClassContainer("B");
    PY_ClassContainer_AllocateParentArray(*cls, 1);

    // Create Parent Objects for class 'B'
    (*cls)->parents[0] = PY_TYPE_OBJECT;

    // Attributes
    PY_setClassAttributeByNameOrCreate(*cls, "get", PY_createBoxForFunction(get_15_safeWrap));


    return PY_NONE;
}

PyObjectContainer* get_15(PyObjectContainer* self_14) {
    // Source Location: B.get

    return PY_createInteger(10);


    return PY_NONE;
}

PyObjectContainer* get_15_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = get_15(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = get_15(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_A_17(PyClassContainer** cls) {
    PyObjectContainer* B_16;

    // Create Class PY_CLASS_A_17 ('A' in source code)
    *cls = PY_createClassContainer("A");
    PY_ClassContainer_AllocateParentArray(*cls, 1);

    // Create Parent Objects for class 'A'
    (*cls)->parents[0] = PY_TYPE_OBJECT;

    // Attributes

    B_16 = PY_createClass("B", PY_CLASS_INIT_PY_CLASS_B_16);
    PY_setClassAttributeByNameOrCreate(*cls, "B", B_16);
    return PY_NONE;
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestClassInClass_20(PyClassContainer** cls) {
    // Create Class PY_CLASS_TestClassInClass_20 ('TestClassInClass' in source code)
    *cls = PY_createClassContainer("TestClassInClass");
    PY_ClassContainer_AllocateParentArray(*cls, 1);

    // Create Parent Objects for class 'TestClassInClass'
    (*cls)->parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_15 = PY_getClassAttributeByName((*cls)->parents[0], "__init_subclass__");
    if (init_subclass_15 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_15, PY_createClassWrapper(*cls), 0, NULL, NULL));
    }
    PY_ClassContainer_EnsureObjectAttributesDeclaredFor(*cls, (*cls)->parents[0]);

    // Attributes
    PY_setClassAttributeByNameOrCreate(*cls, "test_basic", PY_createBoxForFunction(testbasic_19_safeWrap));


    return PY_NONE;
}

PyObjectContainer* testbasic_19(PyObjectContainer* self_18) {
    // Source Location: TestClassInClass.test_basic
    PyObjectContainer* A_17;
    PyObjectContainer* a_35;
    PyObjectContainer* b_36;
    PyObjectContainer* x_37;

    A_17 = PY_createClass("A", PY_CLASS_INIT_PY_CLASS_A_17);
    x_37 = PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(A_17, "B"), NULL, 0, NULL, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_18, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(x_37, "get"), NULL, 0, NULL, NULL)), PY_createInteger(10)}, NULL));


    a_35 = PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(A_17, NULL, 0, NULL, NULL));

    b_36 = PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(a_35, "B"), NULL, 0, NULL, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_18, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(b_36, "get"), NULL, 0, NULL, NULL)), PY_createInteger(10)}, NULL));



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

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_X_23(PyClassContainer** cls) {
    // Create Class PY_CLASS_X_23 ('X' in source code)
    *cls = PY_createClassContainer("X");
    PY_ClassContainer_AllocateParentArray(*cls, 1);

    // Create Parent Objects for class 'X'
    (*cls)->parents[0] = PY_TYPE_OBJECT;

    // Attributes
    PY_setClassAttributeByNameOrCreate(*cls, "get", PY_createBoxForFunction(get_22_safeWrap));


    return PY_NONE;
}

PyObjectContainer* get_22(PyObjectContainer* self_21) {
    // Source Location: X.get

    return PY_createInteger(20);


    return PY_NONE;
}

PyObjectContainer* get_22_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = get_22(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = get_22(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* target_24(void) {
    // Source Location: TestClassInFunction.target
    PyObjectContainer* X_23;

    X_23 = PY_createClass("X", PY_CLASS_INIT_PY_CLASS_X_23);
    return X_23;


    return PY_NONE;
}

PyObjectContainer* target_24_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return target_24();
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestClassInFunction_27(PyClassContainer** cls) {
    // Create Class PY_CLASS_TestClassInFunction_27 ('TestClassInFunction' in source code)
    *cls = PY_createClassContainer("TestClassInFunction");
    PY_ClassContainer_AllocateParentArray(*cls, 1);

    // Create Parent Objects for class 'TestClassInFunction'
    (*cls)->parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_18 = PY_getClassAttributeByName((*cls)->parents[0], "__init_subclass__");
    if (init_subclass_18 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_18, PY_createClassWrapper(*cls), 0, NULL, NULL));
    }
    PY_ClassContainer_EnsureObjectAttributesDeclaredFor(*cls, (*cls)->parents[0]);

    // Attributes
    PY_setClassAttributeByNameOrCreate(*cls, "test_basic", PY_createBoxForFunction(testbasic_26_safeWrap));


    return PY_NONE;
}

PyObjectContainer* testbasic_26(PyObjectContainer* self_25) {
    // Source Location: TestClassInFunction.test_basic
    PyObjectContainer* obj_38;
    PyObjectContainer* target_24;

    target_24 = function_container_target_8;
    obj_38 = PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(target_24, NULL, 0, NULL, NULL)), NULL, 0, NULL, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(self_25, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(obj_38, "get"), NULL, 0, NULL, NULL)), PY_createInteger(20)}, NULL));



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

