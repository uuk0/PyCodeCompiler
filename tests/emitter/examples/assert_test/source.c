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
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "test_2", PY_createBoxForFunction(test2_1_safeWrap));
    PY_exposeModuleObject(PY_MODULE_INSTANCE_source);
}

PyObjectContainer* test_0(void) {
    PyObjectContainer* assert_target_0 = PY_CHECK_EXCEPTION(PY_createInteger(1));
    assert(PY_getTruthValueOf(assert_target_0) && PY_createString("hello world!"));



    return PY_NONE;
}

PyObjectContainer* test_0_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return test_0();
}

PyObjectContainer* test2_1(void) {
    PyObjectContainer* assert_target_1 = PY_CHECK_EXCEPTION(PY_createInteger(0));
    assert(PY_getTruthValueOf(assert_target_1) && PY_createString("exception!"));
    return PY_NONE;
}

PyObjectContainer* test2_1_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return test2_1();
}

