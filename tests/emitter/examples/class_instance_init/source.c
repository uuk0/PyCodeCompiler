#include "pyinclude.h"

// code compiled from python to c via PyCodeCompiler

#include <assert.h>


int _initialise();
void PY_CLASS_INIT_PY_CLASS_test_2();
PyObjectContainer* init_1(PyObjectContainer* self_0);
PyObjectContainer* init_1_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args);

// Global Variables
PyClassContainer* PY_CLASS_test_2;



// implementations

int _initialise() {
    PyObjectContainer* obj;


    PY_CLASS_INIT_PY_CLASS_test_2();

    PyObjectContainer* _obj_instance__0 = PY_createClassInstance(PY_CLASS_test_2);
    PyObjectContainer* _constructor__1 = PY_getObjectAttributeByNameOrStatic(_obj_instance__0, "__init__");

    assert(_constructor__1 != NULL);
    PY_invokeBoxedMethod(_constructor__1, NULL, 0, NULL);
    DECREF(_constructor__1);
    obj = _obj_instance__0;
}

void PY_CLASS_INIT_PY_CLASS_test_2() {
    // Create Class PY_CLASS_test_2 ('test' in source code)
    PY_CLASS_test_2 = PY_createClassContainer("test");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_test_2, 0);
    PY_setClassAttributeByNameOrCreate(PY_CLASS_test_2, "__init__", PY_createBoxForFunction(init_1_safeWrap));
}

PyObjectContainer* init_1(PyObjectContainer* self_0) {
    PyObjectContainer* value_3;

    value_3 = PY_createInteger(0);
}

PyObjectContainer* init_1_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args) {
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

