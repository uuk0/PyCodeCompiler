#include <stdlib.h>

#include "pyinclude.h"
#include "standard_library/init.h"

// code compiled from python to c via PyCodeCompiler

int _initialise();

// Global Variables
PyObjectContainer* test;



// implementations

int _initialise() {
    PY_STD_INIT();
    test = PY_createInteger(10);
}

