#include "pyinclude.h"

// code compiled from python to c via PyCodeCompiler

#include <assert.h>


int _initialise();
PyObjectContainer* test_0();
PyObjectContainer* test_0_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args);


// implementations

int _initialise() {
}

PyObjectContainer* test_0() {
    return PY_createInteger(10);
}

PyObjectContainer* test_0_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args) {
    if (self == NULL)
    {
        assert(argc == 0);
        return test_0();
    }
    else
    {
        assert(argc == -1);
        return test_0(self);
    }
}

