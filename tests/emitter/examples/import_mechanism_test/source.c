#include <stdlib.h>

#include "pyinclude.h"
#include "standard_library/init.h"
#include "standard_library/exceptions.h"
#include "standard_library/importhelper.h"

// code compiled from python to c via PyCodeCompiler

#include "standard_library/modules/typing.h"


void PY_MODULE_source_init();


// implementations

void PY_MODULE_source_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    PyObjectContainer* typing;PY_MODULE_typing_init();
    typing = PY_MODULE_INSTANCE_typing;
}

