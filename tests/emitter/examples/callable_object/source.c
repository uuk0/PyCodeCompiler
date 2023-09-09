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
PyClassContainer* PY_CLASS_Test_4;



// implementations

void PY_MODULE_source_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_MODULE_INSTANCE_source = PY_createModuleObject("source");
    #endif
    PY_CLASS_INIT_PY_CLASS_Test_4();

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "test", PY_createBoxForFunction(test_5_safeWrap));
    PY_exposeModuleObject(PY_MODULE_INSTANCE_source);
    #endif
}

void PY_CLASS_INIT_PY_CLASS_Test_4(void) {
    // Create Class PY_CLASS_Test_4 ('Test' in source code)
    PY_CLASS_Test_4 = PY_createClassContainer("Test");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_Test_4, 1);

    // Create Parent Objects for class 'Test'
    PY_CLASS_Test_4 -> parents[0] = PY_TYPE_OBJECT;

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_Test_4, "__init__", PY_createBoxForFunction(init_1_safeWrap));
    PY_setClassAttributeByNameOrCreate(PY_CLASS_Test_4, "__call__", PY_createBoxForFunction(call_3_safeWrap));
}

PyObjectContainer* init_1(PyObjectContainer* self_0) {
    return PY_NONE;


    return PY_NONE;
}

PyObjectContainer* init_1_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    if (self == NULL)
    {
        assert(argc == 1);
        return init_1(args[0]);
    }
    else
    {
        assert(argc == 0);
        return init_1(self);
    }
}

PyObjectContainer* call_3(PyObjectContainer* self_2) {
    return PY_createInteger(10);



    return PY_NONE;
}

PyObjectContainer* call_3_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    if (self == NULL)
    {
        assert(argc == 1);
        return call_3(args[0]);
    }
    else
    {
        assert(argc == 0);
        return call_3(self);
    }
}

PyObjectContainer* test_5(void) {
    PyObjectContainer* obj_6;

    PyObjectContainer* obj_instance_0 = PY_createClassInstance(PY_CLASS_Test_4);
    PY_CHECK_EXCEPTION(init_1(obj_instance_0));

    obj_6 = obj_instance_0;

    return PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(obj_6, NULL, 0, NULL, NULL));
}

PyObjectContainer* test_5_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return test_5();
}

