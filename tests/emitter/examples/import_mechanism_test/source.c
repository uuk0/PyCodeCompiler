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

#include "standard_library/modules/typing.h"
#include "test_module.h"
#include <assert.h>



// Global Variables
PyObjectContainer* function_container_test_0;



// implementations

PyObjectContainer* PY_MODULE_source_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_MODULE_INSTANCE_source = PY_createModuleObject("source");
    #endif
    PyObjectContainer* test_0;
    PyObjectContainer* test_module_1;
    PyObjectContainer* typing_2;
    function_container_test_0 = PY_createBoxForFunction(test_0_safeWrap);
    PY_CHECK_EXCEPTION(PY_MODULE_typing_init());
    typing_2 = PY_MODULE_INSTANCE_typing;

    PY_CHECK_EXCEPTION(PY_MODULE_test_module_init());
    test_module_1 = PY_MODULE_INSTANCE_test_module;



    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "test", (function_container_test_0 = PY_createBoxForFunction(test_0_safeWrap)));
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_exposeModuleObject(PY_MODULE_INSTANCE_source);
    #endif
}

PyObjectContainer* test_0(void) {
    // Source Location: .test

    PyObjectContainer* assert_target_1 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(PY_MODULE_INSTANCE_typing, "TYPE_CHECKING"), PY_FALSE));
    assert(PY_getTruthValueOf(assert_target_1));

    PyObjectContainer* assert_target_2 = PY_CHECK_EXCEPTION(PY_STD_operator_equals(PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic_ThrowOnNull(PY_MODULE_INSTANCE_test_module, "test_target"), NULL, 0, NULL, NULL)), PY_createInteger(10)));
    assert(PY_getTruthValueOf(assert_target_2));
    return PY_NONE;
}

PyObjectContainer* test_0_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return test_0();
}

