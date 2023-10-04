#include <stdlib.h>

#include "pyinclude.h"
#include "standard_library/config.h"

#include "standard_library/init.h"
#include "standard_library/exceptions.h"

#ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
#include "standard_library/importhelper.h"
#endif

#include "test_unittest.h"

#ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
PyObjectContainer* PY_MODULE_INSTANCE_test_unittest;
#endif

// code compiled from python to c via PyCodeCompiler

#include "standard_library/modules/unittest.h"
#include <assert.h>



// Global Variables
PyObjectContainer* function_container_test_basic_0;
PyClassContainer* PY_CLASS_TestSimple_2;



// implementations

PyObjectContainer* PY_MODULE_test_unittest_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_MODULE_INSTANCE_test_unittest = PY_createModuleObject("test_unittest");
    #endif
    PyObjectContainer* TestSimple_2;
    PyObjectContainer* unittest_3;
    PY_CHECK_EXCEPTION(PY_MODULE_unittest_init());
    unittest_3 = PY_MODULE_INSTANCE_unittest;



    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_unittest, "test_basic", (function_container_test_basic_0 = PY_createBoxForFunction(testbasic_1_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestSimple_2();

    if (PY_unpackBoolean(PY_CHECK_EXCEPTION(PY_CHECK_EXCEPTION(PY_STD_string_eq_fast (PY_createString("__main__") , PY_createString("__main__")))))) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "main"), NULL, 0, NULL, NULL));
    }
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_exposeModuleObject(PY_MODULE_INSTANCE_test_unittest);
    #endif
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestSimple_2(void) {
    // Create Class PY_CLASS_TestSimple_2 ('TestSimple' in source code)
    PY_CLASS_TestSimple_2 = PY_createClassContainer("TestSimple");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_TestSimple_2, 1);

    // Create Parent Objects for class 'TestSimple'
    PY_CLASS_TestSimple_2 -> parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_1 = PY_getClassAttributeByName(PY_CLASS_TestSimple_2->parents[0], "__init_subclass__");
    if (init_subclass_1 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_1, PY_createClassWrapper(PY_CLASS_TestSimple_2), 0, NULL, NULL));
    }
    PY_ClassContainer_EnsureObjectAttributesDeclaredFor(PY_CLASS_TestSimple_2, PY_CLASS_TestSimple_2 -> parents[0]);

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestSimple_2, "test_basic", PY_createBoxForFunction(testbasic_1_safeWrap));
}

PyObjectContainer* testbasic_1(PyObjectContainer* self_0) {
    // Source Location: TestSimple.test_basic

    PyObjectContainer* temporary_2 = PY_TRUE;
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_0, "assertTrue"), NULL, 1, &temporary_2, NULL));

    PyObjectContainer* temporary_3 = PY_FALSE;
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_0, "assertFalse"), NULL, 1, &temporary_3, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_0, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {PY_createInteger(10), PY_createInteger(10)}, NULL));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_0, "assertNotEqual"), NULL, 2, (PyObjectContainer*[]) {PY_createInteger(10), PY_createInteger(20)}, NULL));



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

