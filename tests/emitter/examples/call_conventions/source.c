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




// implementations

PyObjectContainer* PY_MODULE_source_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_MODULE_INSTANCE_source = PY_createModuleObject("source");
    #endif



    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "test", PY_createBoxForFunction(test_0_safeWrap));
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "simple_target", PY_createBoxForFunction(simpletarget_2_safeWrap));
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "test_simple", PY_createBoxForFunction(testsimple_3_safeWrap));
    PY_exposeModuleObject(PY_MODULE_INSTANCE_source);
    #endif
}

PyObjectContainer* test_0(void) {
    PY_CHECK_EXCEPTION(testsimple_3 ());



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

PyObjectContainer* testsimple_3(void) {
    PyObjectContainer* assert_target_0 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(simpletarget_2 (PY_STD_list_CREATE(1, PY_createInteger(10)))), PY_createInteger(10)));
    assert(PY_getTruthValueOf(assert_target_0));
    return PY_NONE;
}

PyObjectContainer* testsimple_3_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return testsimple_3();
}

