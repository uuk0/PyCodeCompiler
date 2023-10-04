#include <stdlib.h>

#include "pyinclude.h"
#include "standard_library/config.h"

#include "standard_library/init.h"
#include "standard_library/exceptions.h"

#ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
#include "standard_library/importhelper.h"
#endif

#include "test_itertools.h"

#ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
PyObjectContainer* PY_MODULE_INSTANCE_test_itertools;
#endif

// code compiled from python to c via PyCodeCompiler

#include "standard_library/modules/unittest.h"
#include "standard_library/modules/itertools.h"
#include <assert.h>



// Global Variables
PyObjectContainer* function_container_test_chain_empty_0;
PyObjectContainer* function_container_test_chain_rhs_empty_1;
PyObjectContainer* function_container_test_chain_basic_2;
PyClassContainer* PY_CLASS_TestItertoolsChain_6;



// implementations

PyObjectContainer* PY_MODULE_test_itertools_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_MODULE_INSTANCE_test_itertools = PY_createModuleObject("test_itertools");
    #endif
    PyObjectContainer* TestItertoolsChain_6;
    PyObjectContainer* itertools_7;
    PyObjectContainer* unittest_8;
    PY_CHECK_EXCEPTION(PY_MODULE_unittest_init());
    unittest_8 = PY_MODULE_INSTANCE_unittest;

    PY_CHECK_EXCEPTION(PY_MODULE_itertools_init());
    itertools_7 = PY_MODULE_INSTANCE_itertools;



    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_itertools, "test_chain_empty", (function_container_test_chain_empty_0 = PY_createBoxForFunction(testchainempty_1_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_itertools, "test_chain_rhs_empty", (function_container_test_chain_rhs_empty_1 = PY_createBoxForFunction(testchainrhsempty_3_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_test_itertools, "test_chain_basic", (function_container_test_chain_basic_2 = PY_createBoxForFunction(testchainbasic_5_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_TestItertoolsChain_6();

    if (PY_unpackBoolean(PY_CHECK_EXCEPTION(PY_CHECK_EXCEPTION(PY_STD_string_eq_fast (PY_createString("__main__") , PY_createString("__main__")))))) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "main"), NULL, 0, NULL, NULL));
    }
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_exposeModuleObject(PY_MODULE_INSTANCE_test_itertools);
    #endif
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_TestItertoolsChain_6(void) {
    // Create Class PY_CLASS_TestItertoolsChain_6 ('TestItertoolsChain' in source code)
    PY_CLASS_TestItertoolsChain_6 = PY_createClassContainer("TestItertoolsChain");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_TestItertoolsChain_6, 1);

    // Create Parent Objects for class 'TestItertoolsChain'
    PY_CLASS_TestItertoolsChain_6 -> parents[0] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_unittest, "TestCase")));
    PyObjectContainer* init_subclass_3 = PY_getClassAttributeByName(PY_CLASS_TestItertoolsChain_6->parents[0], "__init_subclass__");
    if (init_subclass_3 != NULL) {
        PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(init_subclass_3, PY_createClassWrapper(PY_CLASS_TestItertoolsChain_6), 0, NULL, NULL));
    }
    PY_ClassContainer_EnsureObjectAttributesDeclaredFor(PY_CLASS_TestItertoolsChain_6, PY_CLASS_TestItertoolsChain_6 -> parents[0]);

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestItertoolsChain_6, "test_chain_empty", PY_createBoxForFunction(testchainempty_1_safeWrap));
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestItertoolsChain_6, "test_chain_rhs_empty", PY_createBoxForFunction(testchainrhsempty_3_safeWrap));
    PY_setClassAttributeByNameOrCreate(PY_CLASS_TestItertoolsChain_6, "test_chain_basic", PY_createBoxForFunction(testchainbasic_5_safeWrap));
}

PyObjectContainer* testchainempty_1(PyObjectContainer* self_0) {
    // Source Location: TestItertoolsChain.test_chain_empty

    PyObjectContainer* obj_instance_5 = PY_createClassInstance(PY_TYPE_LIST);
    PY_CHECK_EXCEPTION(PY_STD_list_init_fast_arg_1(obj_instance_5 , PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_itertools, "chain"), NULL, 2, (PyObjectContainer*[]) {PY_STD_list_CREATE(0), PY_STD_list_CREATE(0)}, NULL))));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_0, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {obj_instance_5, PY_STD_list_CREATE(0)}, NULL));


    return PY_NONE;
}

PyObjectContainer* testchainempty_1_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testchainempty_1(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testchainempty_1(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testchainrhsempty_3(PyObjectContainer* self_2) {
    // Source Location: TestItertoolsChain.test_chain_rhs_empty

    PyObjectContainer* obj_instance_9 = PY_createClassInstance(PY_TYPE_LIST);
    PY_CHECK_EXCEPTION(PY_STD_list_init_fast_arg_1(obj_instance_9 , PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_itertools, "chain"), NULL, 2, (PyObjectContainer*[]) {PY_STD_list_CREATE(1, PY_createString("test")), PY_STD_list_CREATE(0)}, NULL))));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_2, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {obj_instance_9, PY_STD_list_CREATE(1, PY_createString("test"))}, NULL));


    return PY_NONE;
}

PyObjectContainer* testchainrhsempty_3_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testchainrhsempty_3(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testchainrhsempty_3(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testchainbasic_5(PyObjectContainer* self_4) {
    // Source Location: TestItertoolsChain.test_chain_basic

    PyObjectContainer* obj_instance_13 = PY_createClassInstance(PY_TYPE_LIST);
    PY_CHECK_EXCEPTION(PY_STD_list_init_fast_arg_1(obj_instance_13 , PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(PY_MODULE_INSTANCE_itertools, "chain"), NULL, 2, (PyObjectContainer*[]) {PY_STD_list_CREATE(1, PY_createString("test")), PY_STD_list_CREATE(1, PY_createInteger(2))}, NULL))));

    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_4, "assertEqual"), NULL, 2, (PyObjectContainer*[]) {obj_instance_13, PY_STD_list_CREATE(2, PY_createString("test"), PY_createInteger(2))}, NULL));



    return PY_NONE;
}

PyObjectContainer* testchainbasic_5_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testchainbasic_5(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testchainbasic_5(self);
    }

    if (info) free(new_args);
    return result;
}

