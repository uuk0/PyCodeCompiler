#include <stdlib.h>

#include "pyinclude.h"
#include "standard_library/init.h"
#include "standard_library/exceptions.h"

// code compiled from python to c via PyCodeCompiler

#include "pymodule_typing.h"


int _initialise();


// implementations

int _initialise() {
    PY_STD_INIT();
    PY_CHECK_EXCEPTION(PY_MODULE_typing_init());
    typing = PY_MODULE_INSTANCE_typing;
}

