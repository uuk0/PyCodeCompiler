#include "pyinclude.h"

// code compiled from python to c via PyCodeCompiler

int _initialise();
PyObjectContainer* test();


// implementations

int _initialise() {
}

PyObjectContainer* test() {
    return PY_createInteger(10);
}

