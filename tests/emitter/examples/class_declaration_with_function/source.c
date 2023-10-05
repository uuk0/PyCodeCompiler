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
PyObjectContainer* function_container_target_0;
PyObjectContainer* function_container_test_target_1;
PyClassContainer* PY_CLASS_test_4;



// implementations

PyObjectContainer* PY_MODULE_source_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_MODULE_INSTANCE_source = PY_createModuleObject("source");
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "target", (function_container_target_0 = PY_createBoxForFunction(target_1_safeWrap)));
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "test_target", (function_container_test_target_1 = PY_createBoxForFunction(testtarget_3_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_test_4(&PY_CLASS_test_4);

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_exposeModuleObject(PY_MODULE_INSTANCE_source);
    #endif
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_test_4(PyClassContainer** cls) {
    // Create Class PY_CLASS_test_4 ('test' in source code)
    *cls = PY_createClassContainer("test");
    PY_ClassContainer_AllocateParentArray(*cls, 1);

    // Create Parent Objects for class 'test'
    (*cls)->parents[0] = PY_TYPE_OBJECT;

    // Attributes
    PY_setClassAttributeByNameOrCreate(*cls, "target", PY_createBoxForFunction(target_1_safeWrap));
    PY_setClassAttributeByNameOrCreate(*cls, "test_target", PY_createBoxForFunction(testtarget_3_safeWrap));



    return PY_NONE;
}

PyObjectContainer* target_1(PyObjectContainer* self_0) {
    // Source Location: test.target

    return PY_createInteger(10);


    return PY_NONE;
}

PyObjectContainer* target_1_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = target_1(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = target_1(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testtarget_3(PyObjectContainer* self_2) {
    // Source Location: test.test_target

    return PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_2, "target"), NULL, 0, NULL, NULL));
}

PyObjectContainer* testtarget_3_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testtarget_3(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testtarget_3(self);
    }

    if (info) free(new_args);
    return result;
}

