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
PyClassContainer* PY_CLASS_TestClassCallable_5;
PyClassContainer* PY_CLASS_Test_3;



// implementations

PyObjectContainer* PY_MODULE_test_class_conventions_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_MODULE_INSTANCE_test_class_conventions = PY_createModuleObject("test_class_conventions");
    #endif
    PyObjectContainer* TestClassCallable_5;
    PyObjectContainer* unittest_6;
    PY_CHECK_EXCEPTION(PY_MODULE_unittest_init());
    unittest_6 = PY_MODULE_INSTANCE_unittest;



    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_class_conventions, "__call__", (function_container___call___1 = PY_createBoxForFunction(call_2_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_Test_3();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_class_conventions, "test_basic", (function_container_test_basic_0 = PY_createBoxForFunction(testbasic_4_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestClassCallable_5();

    if (PY_unpackBoolean(PY_CHECK_EXCEPTION(PY_CHECK_EXCEPTION(PY_STD_string_eq_fast (PY_createString("__main__") , PY_createString("__main__")))))) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "main"), NULL, 0, NULL, NULL));
    }
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_exposeModuleObject(PY_MODULE_INSTANCE_test_class_conventions);
    #endif
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestClassCallable_5(void) {
    // Create Class PY_CLASS_TestClassCallable_5 ('TestClassCallable' in source code)
    PY_CLASS_TestClassCallable_5 = PY_createClassContainer("TestClassCallable");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_TestClassCallable_5, 1);

    // Create Parent Objects for class 'TestClassCallable'
    PY_CLASS_TestClassCallable_5 -> parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_2 = PY_getClassAttributeByName(PY_CLASS_TestClassCallable_5->parents[0], "__init_subclass__");
    if (init_subclass_2 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_2, PY_createClassWrapper(PY_CLASS_TestClassCallable_5), 0, NULL, NULL));
    }

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestClassCallable_5, "test_basic", PY_createBoxForFunction(testbasic_4_safeWrap));
}

PyObjectContainer* testbasic_4(PyObjectContainer* self_0) {
    // Source Location: TestClassCallable.test_basic
    PyObjectContainer* Test_3;
    PyObjectContainer* a_7;



    PyObjectContainer* obj_instance_3 = PY_createClassInstance(PY_CLASS_Test_3);
    PyObjectContainer* constructor_4 = PY_getObjectAttributeByNameOrStatic(obj_instance_3, "__init__");

    PY_THROW_EXCEPTION_IF(constructor_4 == NULL, NULL);
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(constructor_4, NULL, 0, NULL, NULL));
    DECREF(constructor_4);
    a_7 = obj_instance_3;

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_0, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(a_7, NULL, 0, NULL, NULL)), PY_createInteger(10)}, NULL));



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

