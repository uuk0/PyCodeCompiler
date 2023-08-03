#include "pyinclude.h"
#include "standard_library/init.h"

// code compiled from python to c via PyCodeCompiler

#include <assert.h>


int _initialise();
PyObjectContainer* test_0();
PyObjectContainer* test_0_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info);


// implementations

int _initialise() {
    PY_STD_INIT();
}

PyObjectContainer* test_0() {
    PyObjectContainer* t_1;

    t_1 = PY_STD_tuple_CREATE(3, PY_createInteger(10), PY_createInteger(20), PY_STD_tuple_CREATE(2, PY_createInteger(20), PY_createInteger(30)));
}

PyObjectContainer* test_0_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return test_0();
}

