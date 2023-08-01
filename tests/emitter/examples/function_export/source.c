#include "pyinclude.h"

// code compiled from python to c via PyCodeCompiler

#include <assert.h>


int _initialise();
PyObjectContainer* test();
PyObjectContainer* test_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args);


// implementations

int _initialise() {
}

PyObjectContainer* test() {
    return PY_createInteger(10);
}

PyObjectContainer* test_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args) {
    assert(argc == 0);
    return test();
}

