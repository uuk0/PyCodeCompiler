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
PyClassContainer* PY_CLASS_test_4;



// implementations

void PY_MODULE_source_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_MODULE_INSTANCE_source = PY_createModuleObject("source");
    #endif
    PY_CLASS_INIT_PY_CLASS_test_4();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_exposeModuleObject(PY_MODULE_INSTANCE_source);
    #endif
}

void PY_CLASS_INIT_PY_CLASS_test_4(void) {
    // Create Class PY_CLASS_test_4 ('test' in source code)
    PY_CLASS_test_4 = PY_createClassContainer("test");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_test_4, 1);

    // Create Parent Objects for class 'test'
    PY_CLASS_test_4 -> parents[0] = PY_TYPE_OBJECT;

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_test_4, "target", PY_createBoxForFunction(target_1_safeWrap));
    PY_setClassAttributeByNameOrCreate(PY_CLASS_test_4, "test_target", PY_createBoxForFunction(testtarget_3_safeWrap));
}

PyObjectContainer* target_1(PyObjectContainer* self_0) {
    return PY_createInteger(10);


    return PY_NONE;
}

PyObjectContainer* target_1_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    if (self == NULL)
    {
        assert(argc == 1);
        return target_1(args[0]);
    }
    else
    {
        assert(argc == 0);
        return target_1(self);
    }
}

PyObjectContainer* testtarget_3(PyObjectContainer* self_2) {
    return PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_2, "target"), NULL, 0, NULL, NULL));
}

PyObjectContainer* testtarget_3_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    if (self == NULL)
    {
        assert(argc == 1);
        return testtarget_3(args[0]);
    }
    else
    {
        assert(argc == 0);
        return testtarget_3(self);
    }
}

