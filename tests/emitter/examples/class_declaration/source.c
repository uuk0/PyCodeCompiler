#include "pyinclude.h"

// code compiled from python to c via PyCodeCompiler

int _initialise();
void PY_CLASS_INIT_PY_CLASS_test_0();

// Global Variables
PyClassContainer* PY_CLASS_test_0;



// implementations

int _initialise() {
    PY_CLASS_INIT_PY_CLASS_test_0();
}

void PY_CLASS_INIT_PY_CLASS_test_0() {
    PyObjectContainer* attr;

    // Create Class PY_CLASS_test_0 ('test' in source code)
    PY_CLASS_test_0 = PY_createClassContainer("test");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_test_0, 0);

    attr = PY_createInteger(10);
}

