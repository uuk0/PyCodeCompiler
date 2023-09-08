#include <stdlib.h>

#include "pyinclude.h"
#include "standard_library/init.h"
#include "standard_library/exceptions.h"
#include "standard_library/importhelper.h"

#include "source.h"

PyObjectContainer* PY_MODULE_INSTANCE_source;

// code compiled from python to c via PyCodeCompiler


// Global Variables
PyObjectContainer* test;



// implementations

void PY_MODULE_source_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    PY_MODULE_INSTANCE_source = PY_createModuleObject("source");
    PyObjectContainer* test;
    test = PY_createInteger(10);
    PY_exposeModuleObject(PY_MODULE_INSTANCE_source);
}

