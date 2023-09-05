#include <stdlib.h>

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
    PyObjectContainer* obj_1;


    PyObjectContainer* obj_instance_0 = PY_createClassInstance(PY_TYPE_DICT);
    PyObjectContainer* constructor_1 = PY_getObjectAttributeByNameOrStatic(obj_instance_0, "__init__");

    assert(constructor_1 != NULL);
    PY_invokeBoxedMethod(constructor_1, NULL, 0, NULL, NULL);
    DECREF(constructor_1);
    obj_1 = obj_instance_0;

    PY_STD_dict_setitem_fast (obj_1 , PY_createString("test") , PY_createInteger(10));
}

PyObjectContainer* test_0_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return test_0();
}

