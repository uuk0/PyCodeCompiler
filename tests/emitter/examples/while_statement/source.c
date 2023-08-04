#include "pyinclude.h"
#include "standard_library/init.h"

// code compiled from python to c via PyCodeCompiler

int _initialise();


// implementations

int _initialise() {
    PY_STD_INIT();
    PyObjectContainer* test;
    test = PY_createInteger(10);

    while (PY_getTruthValueOf(test)) {
        test = test;
    }
    while (PY_getTruthValueOf(test)) {
        test = PY_STD_operator_sub(test, PY_createInteger(1));
    }

    test = PY_createInteger(20);
    while_exit_label_0:
    "marker";
}

