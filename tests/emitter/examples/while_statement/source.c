#include "pyinclude.h"

// code compiled from python to c via PyCodeCompiler

int _initialise();


// implementations

int _initialise() {
    test = PY_createInteger(10);

    while (PY_getTruthValueOf(test)) {
        test = test;
    }
}

