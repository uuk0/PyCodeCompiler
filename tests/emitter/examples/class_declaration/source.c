#include "pyinclude.h"

// code compiled from python to c via PyCodeCompiler

int _initialise();
void PY_CLASS_INIT_PY_CLASS_test();

// Global Variables
PyClassContainer* PY_CLASS_test;



// implementations

int _initialise() {
    PY_CLASS_INIT_PY_CLASS_test();
}

void PY_CLASS_INIT_PY_CLASS_test() {
    // Create Class PY_CLASS_test (test in source code)
    PY_CLASS_test = PY_createClassContainer("test");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_test, 0);

    // Create Parent Objects for class test


    attr = PY_createInteger(10);
}

