#include "pyinclude.h"

// code compiled from python to c via PyCodeCompiler

#include <assert.h>


int _initialise();
void PY_CLASS_INIT_PY_CLASS_test();
PyObjectContainer* target(PyObjectContainer* self);
PyObjectContainer* test_target(PyObjectContainer* self);
PyObjectContainer* test_target_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args);
PyObjectContainer* target_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args);

// Global Variables
PyClassContainer* PY_CLASS_test;



// implementations

int _initialise() {
    // Create Class PY_CLASS_test (test in source code)
    PY_CLASS_test = PY_createClassContainer("test");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_test, 0);



    // Create Parent Objects for class test
    PY_setClassAttributeByNameOrCreate(PY_CLASS_test, "target", PY_createBoxForFunction(target_safeWrap));
    PY_CLASS_INIT_PY_CLASS_test();
}

void PY_CLASS_INIT_PY_CLASS_test() {
}

PyObjectContainer* target(PyObjectContainer* self) {
    return PY_createInteger(10);
}

PyObjectContainer* test_target(PyObjectContainer* self) {
    return PY_invokeBoxedMethod(self -> target, NULL, 0, NULL);
}

PyObjectContainer* test_target_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args) {
    assert(argc == 1);
    return test_target(args[0]);
}

PyObjectContainer* target_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args) {
    assert(argc == 1);
    return target(args[0]);
}

