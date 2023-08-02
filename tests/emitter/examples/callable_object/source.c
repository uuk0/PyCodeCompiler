#include "pyinclude.h"
#include "pystandardlib.h"

// code compiled from python to c via PyCodeCompiler

#include <assert.h>


int _initialise();
void PY_CLASS_INIT_PY_CLASS_Test_4();
PyObjectContainer* init_1(PyObjectContainer* self_0);
PyObjectContainer* init_1_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args);
PyObjectContainer* call_3(PyObjectContainer* self_2);
PyObjectContainer* call_3_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args);
PyObjectContainer* test_5();
PyObjectContainer* test_5_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args);

// Global Variables
PyClassContainer* PY_CLASS_Test_4;



// implementations

int _initialise() {
    PY_STD_INIT();
    PY_CLASS_INIT_PY_CLASS_Test_4();
}

void PY_CLASS_INIT_PY_CLASS_Test_4() {
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

PyObjectContainer* call_3(PyObjectContainer* self_2) {
    return PY_createInteger(10);
}

PyObjectContainer* call_3_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args) {
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

PyObjectContainer* test_5() {
    PyObjectContainer* obj_6;


    PyObjectContainer* obj_instance_0 = PY_createClassInstance(PY_CLASS_Test_4);
    PyObjectContainer* constructor_1 = PY_getObjectAttributeByNameOrStatic(obj_instance_0, "__init__");

    assert(constructor_1 != NULL);
    PY_invokeBoxedMethod(constructor_1, NULL, 0, NULL);
    DECREF(constructor_1);
    obj_6 = obj_instance_0;

    return PY_invokeBoxedMethod(obj_6, NULL, 0, NULL);
}

PyObjectContainer* test_5_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args) {
    assert(self == NULL);
    assert(argc == 0);
    return test_5();
}

