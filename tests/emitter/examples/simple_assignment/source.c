#include "pyinclude.h"

// code compiled from python to c via PyCodeCompiler

int _initialise();


// implementations

int _initialise() {
    PyObjectContainer* test;
    test = PY_createInteger(10);
}

