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
PyObjectContainer* function_container_test_0;
PyClassContainer* PY_CLASS_test_2;



// implementations

PyObjectContainer* PY_MODULE_source_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_MODULE_INSTANCE_source = PY_createModuleObject("source");
    #endif
    function_container_test_0 = PY_createBoxForFunction(test_1_safeWrap);
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "test", (function_container_test_0 = PY_createBoxForFunction(test_1_safeWrap)));
    #endif
    PY_CLASS_INIT_PY_CLASS_test_2(&PY_CLASS_test_2);

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_exposeModuleObject(PY_MODULE_INSTANCE_source);
    #endif
}

PyObjectContainer* PY_CLASS_INIT_PY_CLASS_test_2(PyClassContainer** cls) {
    PyObjectContainer* attr_3;

    // Create Class PY_CLASS_test_2 ('test' in source code)
    *cls = PY_createClassContainer("test");
    PY_ClassContainer_AllocateParentArray(*cls, 1);

    // Create Parent Objects for class 'test'
    (*cls)->parents[0] = PY_TYPE_OBJECT;

    // Attributes
    PY_setClassAttributeByNameOrCreate(*cls, "test", PY_createBoxForFunction(test_1_safeWrap));

    attr_3 = PY_createInteger(10);



    PY_setClassAttributeByNameOrCreate(*cls, "attr", attr_3);
    return PY_NONE;
}

PyObjectContainer* test_1(PyObjectContainer* self_0) {
    // Source Location: test.test


    return PY_NONE;
}

PyObjectContainer* test_1_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = test_1(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = test_1(self);
    }

    if (info) free(new_args);
    return result;
}

