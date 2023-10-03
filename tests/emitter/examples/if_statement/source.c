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
PyObjectContainer* function_container_test2_1;



// implementations

PyObjectContainer* PY_MODULE_source_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_MODULE_INSTANCE_source = PY_createModuleObject("source");
    #endif
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "test", (function_container_test_0 = PY_createBoxForFunction(test_1_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "test2", (function_container_test2_1 = PY_createBoxForFunction(test2_3_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_exposeModuleObject(PY_MODULE_INSTANCE_source);
    #endif
}

PyObjectContainer* test_1(PyObjectContainer* x_0) {
    // Source Location: .test

    if (PY_unpackBoolean(PY_CHECK_EXCEPTION(PY_STD_operator_equals(x_0, PY_createInteger(0))))) {
        return PY_createInteger(1);
    }
    else if (PY_unpackBoolean(PY_CHECK_EXCEPTION(PY_STD_operator_equals(x_0, PY_createInteger(1))))) {
        return PY_createInteger(2);
    }
    else {
        return PY_createInteger(3);
    }
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

PyObjectContainer* test2_3(PyObjectContainer* x_2) {
    // Source Location: .test2

    return (PY_STD_operator_equals(x_2, PY_createInteger(3)) ? PY_createInteger(1) : PY_createInteger(2));
}

PyObjectContainer* test2_3_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = test2_3(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = test2_3(self);
    }

    if (info) free(new_args);
    return result;
}

