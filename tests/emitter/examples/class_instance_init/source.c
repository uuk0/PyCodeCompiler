#include "pyinclude.h"

// code compiled from python to c via PyCodeCompiler

#include <assert.h>


int _initialise();
void PY_CLASS_INIT_PY_CLASS_test();
PyObjectContainer* __init__(PyObjectContainer* self);
PyObjectContainer* __init___safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args);

// Global Variables
PyClassContainer* PY_CLASS_test;



// implementations

int _initialise() {
    PyObjectContainer* obj;


    PY_CLASS_INIT_PY_CLASS_test();

    PyObjectContainer* _obj_instance__0 = PY_createClassInstance(PY_CLASS_test);
    PyObjectContainer* _constructor__1 = PY_getObjectAttributeByNameOrStatic(_obj_instance__0, "__init__");

    assert(_constructor__1 != NULL);
    PY_invokeBoxedMethod(_constructor__1, NULL, 0, NULL);
    DECREF(_constructor__1);
    obj = _obj_instance__0;
}

void PY_CLASS_INIT_PY_CLASS_test() {
    // Create Class PY_CLASS_test (test in source code)
    PY_CLASS_test = PY_createClassContainer("test");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_test, 0);

    // Create Parent Objects for class test
    PY_setClassAttributeByNameOrCreate(PY_CLASS_test, "__init__", PY_createBoxForFunction(__init___safeWrap));
}

PyObjectContainer* __init__(PyObjectContainer* self) {
    PyObjectContainer* value;

    value = PY_createInteger(0);
}

PyObjectContainer* __init___safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args) {
    if (self == NULL)
    {
        assert(argc == 1);
        return __init__(args[0]);
    }
    else
    {
        assert(argc == 0);
        return __init__(self);
    }
}

