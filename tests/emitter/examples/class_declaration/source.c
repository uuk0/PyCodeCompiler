#include "pyinclude.h"

// code compiled from python to c via PyCodeCompiler

int _initialise();

// Global Variables
PyClassContainer* PY_CLASS_test;



// implementations

int _initialise() {
    // Create Class PY_CLASS_test (test in source code)
    PY_CLASS_test = PY_createClassContainer("test");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_test, 0);
}

