#include "pyinclude.h"

// code compiled from python to c via PyCodeCompiler

int _initialise();


// implementations

int _initialise() {
    test = PY_createInteger(10);
}

