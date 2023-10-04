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
PyObjectContainer* function_container_test_basic_0;
PyObjectContainer* function_container___call___1;
PyObjectContainer* function_container_test_attribute_2;
PyObjectContainer* function_container___init___3;
PyObjectContainer* function_container___call___4;
PyObjectContainer* function_container_test_basic_5;
PyObjectContainer* function_container_get_6;
PyClassContainer* PY_CLASS_TestClassCallable_13;
PyClassContainer* PY_CLASS_Test_3;
PyClassContainer* PY_CLASS_Test_11;
PyClassContainer* PY_CLASS_TestClassInClass_20;
PyClassContainer* PY_CLASS_A_18;
PyClassContainer* PY_CLASS_B_17;



// implementations

PyObjectContainer* PY_MODULE_test_class_conventions_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_MODULE_INSTANCE_test_class_conventions = PY_createModuleObject("test_class_conventions");
    #endif
    PyObjectContainer* TestClassCallable_13;
    PyObjectContainer* TestClassInClass_20;
    PyObjectContainer* unittest_21;
    PY_CHECK_EXCEPTION(PY_MODULE_unittest_init());
    unittest_21 = PY_MODULE_INSTANCE_unittest;



    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_class_conventions, "__call__", (function_container___call___1 = PY_createBoxForFunction(call_2_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_Test_3();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_class_conventions, "test_basic", (function_container_test_basic_0 = PY_createBoxForFunction(testbasic_4_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_class_conventions, "__init__", (function_container___init___3 = PY_createBoxForFunction(init_8_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_class_conventions, "__call__", (function_container___call___4 = PY_createBoxForFunction(call_10_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_Test_11();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_class_conventions, "test_attribute", (function_container_test_attribute_2 = PY_createBoxForFunction(testattribute_12_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestClassCallable_13();

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_class_conventions, "get", (function_container_get_6 = PY_createBoxForFunction(get_16_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_B_17();
    PY_CLASS_INIT_PY_CLASS_A_18();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_class_conventions, "test_basic", (function_container_test_basic_5 = PY_createBoxForFunction(testbasic_19_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestClassInClass_20();

    if (PY_unpackBoolean(PY_CHECK_EXCEPTION(PY_CHECK_EXCEPTION(PY_STD_string_eq_fast (PY_createString("__main__") , PY_createString("__main__")))))) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "main"), NULL, 0, NULL, NULL));
    }
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_exposeModuleObject(PY_MODULE_INSTANCE_test_class_conventions);
    #endif
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestClassCallable_13(void) {
    // Create Class PY_CLASS_TestClassCallable_13 ('TestClassCallable' in source code)
    PY_CLASS_TestClassCallable_13 = PY_createClassContainer("TestClassCallable");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_TestClassCallable_13, 1);

    // Create Parent Objects for class 'TestClassCallable'
    PY_CLASS_TestClassCallable_13 -> parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_7 = PY_getClassAttributeByName(PY_CLASS_TestClassCallable_13->parents[0], "__init_subclass__");
    if (init_subclass_7 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_7, PY_createClassWrapper(PY_CLASS_TestClassCallable_13), 0, NULL, NULL));
    }
    PY_ClassContainer_EnsureObjectAttributesDeclaredFor(PY_CLASS_TestClassCallable_13, PY_CLASS_TestClassCallable_13 -> parents[0]);

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestClassCallable_13, "test_basic", PY_createBoxForFunction(testbasic_4_safeWrap));
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestClassCallable_13, "test_attribute", PY_createBoxForFunction(testattribute_12_safeWrap));
}

PyObjectContainer* testbasic_4(PyObjectContainer* self_0) {
    // Source Location: TestClassCallable.test_basic
    PyObjectContainer* Test_3;
    PyObjectContainer* a_22;



    PyObjectContainer* obj_instance_8 = PY_createClassInstance(PY_CLASS_Test_3);
    PyObjectContainer* constructor_9 = PY_getObjectAttributeByNameOrStatic(obj_instance_8, "__init__");

    PY_THROW_EXCEPTION_IF(constructor_9 == NULL, NULL);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(constructor_9, NULL, 0, NULL, NULL));
    DECREF(constructor_9);
    a_22 = obj_instance_8;

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_0, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(a_22, NULL, 0, NULL, NULL)), PY_createInteger(10)}, NULL));


    return PY_NONE;
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_Test_3(void) {
    // Create Class PY_CLASS_Test_3 ('Test' in source code)
    PY_CLASS_Test_3 = PY_createClassContainer("Test");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_Test_3, 1);

    // Create Parent Objects for class 'Test'
    PY_CLASS_Test_3 -> parents[0] = PY_TYPE_OBJECT;

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_Test_3, "__call__", PY_createBoxForFunction(call_2_safeWrap));
}

PyObjectContainer* call_2(PyObjectContainer* self_1) {
    // Source Location: TestClassCallable.Test.__call__

    return PY_createInteger(10);


    return PY_NONE;
}

PyObjectContainer* call_2_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = call_2(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = call_2(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testbasic_4_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testbasic_4(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testbasic_4(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testattribute_12(PyObjectContainer* self_5) {
    // Source Location: TestClassCallable.test_attribute
    PyObjectContainer* Test_11;
    PyObjectContainer* a_23;


    PyObjectContainer* obj_instance_12 = PY_createClassInstance(PY_CLASS_Test_11);
    PY_CHECK_EXCEPTION(init_8(obj_instance_12 , PY_createInteger(20)));

    a_23 = obj_instance_12;

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_5, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(a_23, NULL, 0, NULL, NULL)), PY_createInteger(20)}, NULL));



    return PY_NONE;
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_Test_11(void) {
    // Create Class PY_CLASS_Test_11 ('Test' in source code)
    PY_CLASS_Test_11 = PY_createClassContainer("Test");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_Test_11, 1);

    // Create Parent Objects for class 'Test'
    PY_CLASS_Test_11 -> parents[0] = PY_TYPE_OBJECT;
    PY_ClassContainer_DeclareObjectAttribute(PY_CLASS_Test_11, "value");

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_Test_11, "__init__", PY_createBoxForFunction(init_8_safeWrap));
    PY_setClassAttributeByNameOrCreate(PY_CLASS_Test_11, "__call__", PY_createBoxForFunction(call_10_safeWrap));
}

PyObjectContainer* init_8(PyObjectContainer* self_6 , PyObjectContainer* value_7) {
    // Source Location: TestClassCallable.Test.__init__

    PyObjectContainer* temp_11 = value_7;
    PY_setObjectAttributeByName(self_6, "value", temp_11);


    return PY_NONE;
}

PyObjectContainer* init_8_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 2);
        result = init_8(new_args[0], new_args[1]);
    }
    else {
        assert(argc == 1);
        result = init_8(self , new_args[0]);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* call_10(PyObjectContainer* self_9) {
    // Source Location: TestClassCallable.Test.__call__

    return PY_getObjectAttributeByNameOrStatic(self_9, "value");


    return PY_NONE;
}

PyObjectContainer* call_10_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = call_10(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = call_10(self);
    }

    if (info) free(new_args);
    return result;
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

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestClassInClass_20(void) {
    // Create Class PY_CLASS_TestClassInClass_20 ('TestClassInClass' in source code)
    PY_CLASS_TestClassInClass_20 = PY_createClassContainer("TestClassInClass");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_TestClassInClass_20, 1);

    // Create Parent Objects for class 'TestClassInClass'
    PY_CLASS_TestClassInClass_20 -> parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_15 = PY_getClassAttributeByName(PY_CLASS_TestClassInClass_20->parents[0], "__init_subclass__");
    if (init_subclass_15 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_15, PY_createClassWrapper(PY_CLASS_TestClassInClass_20), 0, NULL, NULL));
    }
    PY_ClassContainer_EnsureObjectAttributesDeclaredFor(PY_CLASS_TestClassInClass_20, PY_CLASS_TestClassInClass_20 -> parents[0]);

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestClassInClass_20, "test_basic", PY_createBoxForFunction(testbasic_19_safeWrap));
}

PyObjectContainer* testbasic_19(PyObjectContainer* self_14) {
    // Source Location: TestClassInClass.test_basic
    PyObjectContainer* A_18;
    PyObjectContainer* x_24;


    x_24 = PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(PY_createClassWrapper(PY_CLASS_A_18), "B"), NULL, 0, NULL, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_14, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(x_24, "get"), NULL, 0, NULL, NULL)), PY_createInteger(10)}, NULL));



    return PY_NONE;
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_A_18(void) {
    // Create Class PY_CLASS_A_18 ('A' in source code)
    PY_CLASS_A_18 = PY_createClassContainer("A");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_A_18, 1);

    // Create Parent Objects for class 'A'
    PY_CLASS_A_18 -> parents[0] = PY_TYPE_OBJECT;

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_A_18, "B", PY_createClassWrapper(PY_CLASS_B_17));
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_B_17(void) {
    // Create Class PY_CLASS_B_17 ('B' in source code)
    PY_CLASS_B_17 = PY_createClassContainer("B");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_B_17, 1);

    // Create Parent Objects for class 'B'
    PY_CLASS_B_17 -> parents[0] = PY_TYPE_OBJECT;

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_B_17, "get", PY_createBoxForFunction(get_16_safeWrap));
}

PyObjectContainer* get_16(PyObjectContainer* self_15) {
    // Source Location: TestClassInClass.A.B.get

    return PY_createInteger(10);


    return PY_NONE;
}

PyObjectContainer* get_16_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = get_16(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = get_16(self);
    }

    if (info) free(new_args);
    return result;
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

