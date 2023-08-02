#include "pyinclude.h"

// code compiled from python to c via PyCodeCompiler

int _initialise();


// implementations

int _initialise() {
    PyObjectContainer* _tas__0 = PY_createInteger(10);
    PyObjectContainer* test = _tas__0;



    while (PY_getTruthValueOf(test)) {
        PyObjectContainer* _tas__1 = test;
        PyObjectContainer* test = _tas__1;
    }
}

