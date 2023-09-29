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
PyObjectContainer* function_container_simple_target_1;
PyObjectContainer* function_container_test_simple_2;



// implementations

PyObjectContainer* PY_MODULE_source_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_MODULE_INSTANCE_source = PY_createModuleObject("source");
    #endif



    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "test", (function_container_test_0 = PY_createBoxForFunction(test_0_safeWrap)));
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "simple_target", (function_container_simple_target_1 = PY_createBoxForFunction(simpletarget_2_safeWrap)));
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "test_simple", (function_container_test_simple_2 = PY_createBoxForFunction(testsimple_4_safeWrap)));
    PY_exposeModuleObject(PY_MODULE_INSTANCE_source);
    #endif
}

PyObjectContainer* test_0(void) {
    PY_CHECK_EXCEPTION(testsimple_4 (function_container_simple_target_1));



    return PY_NONE;
}

PyObjectContainer* test_0_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return test_0();
}

PyObjectContainer* simpletarget_2(PyObjectContainer* a_1) {
    return a_1;



    return PY_NONE;
}

PyObjectContainer* simpletarget_2_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = simpletarget_2(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = simpletarget_2(self);
    }

    if (info) free(new_args);
    return result;
}

PyObjectContainer* testsimple_4(PyObjectContainer* f_3) {
    PyObjectContainer* temporary_4 = PY_STD_list_CREATE(1, PY_createInteger(10));
    PyObjectContainer* assert_target_3 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(f_3, NULL, 1, &temporary_4, PY_ARGS_createCallInfo(0, 1, (uint64_t[]) {CALL_STRUCTURE_STAR, 0, 0, 0, 0, 0, 0, 0}, NULL))), PY_createInteger(10)));
    assert(PY_getTruthValueOf(assert_target_3));
    return PY_NONE;
}

PyObjectContainer* testsimple_4_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
    PyObjectContainer* result;

    if (self == NULL) {
        assert(argc == 1);
        result = testsimple_4(new_args[0]);
    }
    else {
        assert(argc == 0);
        result = testsimple_4(self);
    }

    if (info) free(new_args);
    return result;
}

