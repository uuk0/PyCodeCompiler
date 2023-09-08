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
PyClassContainer* PY_CLASS_test_2;
PyObjectContainer* obj;



// implementations

void PY_MODULE_source_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_MODULE_INSTANCE_source = PY_createModuleObject("source");
    #endif
    PyObjectContainer* obj;
    PyObjectContainer* test;
    PY_CLASS_INIT_PY_CLASS_test_2();
    PyObjectContainer* obj_instance_0 = PY_createClassInstance(PY_CLASS_test_2);
    PY_CHECK_EXCEPTION(init_1(obj_instance_0));

    obj = obj_instance_0;
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_exposeModuleObject(PY_MODULE_INSTANCE_source);
    #endif
}

void PY_CLASS_INIT_PY_CLASS_test_2(void) {
    // Create Class PY_CLASS_test_2 ('test' in source code)
    PY_CLASS_test_2 = PY_createClassContainer("test");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_test_2, 1);

    // Create Parent Objects for class 'test'
    PY_CLASS_test_2 -> parents[0] = PY_TYPE_OBJECT;

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_test_2, "__init__", PY_createBoxForFunction(init_1_safeWrap));
}

PyObjectContainer* init_1(PyObjectContainer* self_0) {
    PyObjectContainer* value_3;

    value_3 = PY_createInteger(0);



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

