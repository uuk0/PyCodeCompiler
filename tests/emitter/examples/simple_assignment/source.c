#include <stdlib.h>

#include "pyinclude.h"
#include "standard_library/init.h"
#include "standard_library/exceptions.h"
#include "standard_library/importhelper.h"

// code compiled from python to c via PyCodeCompiler

void PY_MODULE_source_init();

// Global Variables
PyObjectContainer* test;



// implementations

void PY_MODULE_source_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    PyObjectContainer* test;test = PY_createInteger(10);
}

