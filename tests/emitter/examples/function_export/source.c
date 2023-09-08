#include <stdlib.h>

#include "pyinclude.h"
#include "standard_library/init.h"
#include "standard_library/exceptions.h"
#include "standard_library/importhelper.h"

#include "source.h"

PyObjectContainer* PY_MODULE_INSTANCE_source;

// code compiled from python to c via PyCodeCompiler

#include <assert.h>




// implementations

void PY_MODULE_source_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    PY_MODULE_INSTANCE_source = PY_createModuleObject("source");

    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "test", PY_createBoxForFunction(test_0_safeWrap));
    PY_exposeModuleObject(PY_MODULE_INSTANCE_source);
}

PyObjectContainer* test_0(void) {
    return PY_createInteger(10);
}

PyObjectContainer* test_0_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return test_0();
}

