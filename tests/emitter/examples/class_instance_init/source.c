#include <stdlib.h>

#include "pyinclude.h"
#include "standard_library/init.h"
#include "standard_library/exceptions.h"

// code compiled from python to c via PyCodeCompiler

#include <assert.h>


int _initialise();
void PY_CLASS_INIT_PY_CLASS_test_2();
PyObjectContainer* init_1(PyObjectContainer* self_0);
PyObjectContainer* init_1_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info);

// Global Variables
PyClassContainer* PY_CLASS_test_2;
PyObjectContainer* obj;



// implementations

int _initialise() {
    PY_STD_INIT();
    PY_CLASS_INIT_PY_CLASS_test_2();
    PyObjectContainer* obj_instance_0 = PY_createClassInstance(PY_CLASS_test_2);
    PY_CHECK_EXCEPTION(init_1(obj_instance_0));

    obj = obj_instance_0;
}

void PY_CLASS_INIT_PY_CLASS_test_2() {
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

