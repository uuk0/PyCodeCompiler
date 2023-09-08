#include <stdlib.h>

#include "pyinclude.h"
#include "standard_library/init.h"
#include "standard_library/exceptions.h"
#include "standard_library/importhelper.h"

// code compiled from python to c via PyCodeCompiler

#include <assert.h>


void PY_MODULE_source_init();
void PY_CLASS_INIT_PY_CLASS_test_2();
PyObjectContainer* test_1(PyObjectContainer* self_0);
PyObjectContainer* test_1_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info);

// Global Variables
PyClassContainer* PY_CLASS_test_2;



// implementations

void PY_MODULE_source_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    PY_CLASS_INIT_PY_CLASS_test_2();
}

void PY_CLASS_INIT_PY_CLASS_test_2(void) {
    PyObjectContainer* attr;

    // Create Class PY_CLASS_test_2 ('test' in source code)
    PY_CLASS_test_2 = PY_createClassContainer("test");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_test_2, 1);

    // Create Parent Objects for class 'test'
    PY_CLASS_test_2 -> parents[0] = PY_TYPE_OBJECT;

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_test_2, "test", PY_createBoxForFunction(test_1_safeWrap));

    attr = PY_createInteger(10);
}

PyObjectContainer* test_1(PyObjectContainer* self_0) {
    return PY_NONE;
}

PyObjectContainer* test_1_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    if (self == NULL)
    {
        assert(argc == 1);
        return test_1(args[0]);
    }
    else
    {
        assert(argc == 0);
        return test_1(self);
    }
}

