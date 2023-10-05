#include <stdlib.h>

#include "pyinclude.h"
#include "standard_library/config.h"

#include "standard_library/init.h"
#include "standard_library/exceptions.h"

#ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
#include "standard_library/importhelper.h"
#endif

#include "source.h"

#ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
PyObjectContainer* PY_MODULE_INSTANCE_source;
#endif

// code compiled from python to c via PyCodeCompiler

#include <assert.h>



// Global Variables
PyObjectContainer* function_container___init___0;
PyObjectContainer* function_container___call___1;
PyObjectContainer* function_container_test_2;
PyClassContainer* PY_CLASS_Test_4;



// implementations

PyObjectContainer* PY_MODULE_source_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_MODULE_INSTANCE_source = PY_createModuleObject("source");
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "__init__", (function_container___init___0 = PY_createBoxForFunction(init_1_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "__call__", (function_container___call___1 = PY_createBoxForFunction(call_3_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_Test_4(&PY_CLASS_Test_4);

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "test", (function_container_test_2 = PY_createBoxForFunction(test_5_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_exposeModuleObject(PY_MODULE_INSTANCE_source);
    #endif
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_Test_4(PyClassContainer** cls) {
    // Create Class PY_CLASS_Test_4 ('Test' in source code)
    *cls = PY_createClassContainer("Test");
    PY_ClassContainer_AllocateParentArray(*cls, 1);

    // Create Parent Objects for class 'Test'
    (*cls)->parents[0] = PY_TYPE_OBJECT;

    // Attributes
    PY_setClassAttributeByNameOrCreate(*cls, "__init__", PY_createBoxForFunction(init_1_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "__call__", PY_createBoxForFunction(call_3_safeWrap));



    return PY_NONE;
}

PyObjectContainer* init_1(PyObjectContainer* self_0) {
    // Source Location: Test.__init__

    return PY_NONE;


    return PY_NONE;
}

PyObjectContainer* init_1_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = init_1(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = init_1(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* call_3(PyObjectContainer* self_2) {
    // Source Location: Test.__call__

    return PY_createInteger(10);



    return PY_NONE;
}

PyObjectContainer* call_3_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = call_3(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = call_3(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* test_5(void) {
    // Source Location: .test
    PyObjectContainer* obj_6;

    PyObjectContainer* obj_instance_3 = PY_createClassInstance(PY_CLASS_Test_4);
    PY_CHECK_EXCEPTION(init_1(obj_instance_3));

    obj_6 = obj_instance_3;

    return PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(obj_6, NULL, 0, NULL, NULL));
}

PyObjectContainer* test_5_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return test_5();
}

