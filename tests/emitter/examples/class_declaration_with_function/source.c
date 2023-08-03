#include "pyinclude.h"
#include "standard_library/init.h"

// code compiled from python to c via PyCodeCompiler

#include <assert.h>


int _initialise();
void PY_CLASS_INIT_PY_CLASS_test_4();
PyObjectContainer* target_1(PyObjectContainer* self_0);
PyObjectContainer* target_1_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info);
PyObjectContainer* testtarget_3(PyObjectContainer* self_2);
PyObjectContainer* testtarget_3_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info);

// Global Variables
PyClassContainer* PY_CLASS_test_4;



// implementations

int _initialise() {
    PY_STD_INIT();
    PY_CLASS_INIT_PY_CLASS_test_4();
}

void PY_CLASS_INIT_PY_CLASS_test_4() {
    // Create Class PY_CLASS_test_4 ('test' in source code)
    PY_CLASS_test_4 = PY_createClassContainer("test");
    PY_ClassContainer_AllocateParentArray(PY_CLASS_test_4, 1);

    // Create Parent Objects for class 'test'
    PY_CLASS_test_4 -> parents[0] = PY_TYPE_OBJECT;

    // Attributes
    PY_setClassAttributeByNameOrCreate(PY_CLASS_test_4, "target", PY_createBoxForFunction(target_1_safeWrap));
    PY_setClassAttributeByNameOrCreate(PY_CLASS_test_4, "test_target", PY_createBoxForFunction(testtarget_3_safeWrap));
}

PyObjectContainer* target_1(PyObjectContainer* self_0) {
    return PY_createInteger(10);
}

PyObjectContainer* target_1_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    if (self == NULL)
    {
        assert(argc == 1);
        return target_1(args[0]);
    }
    else
    {
        assert(argc == 0);
        return target_1(self);
    }
}

PyObjectContainer* testtarget_3(PyObjectContainer* self_2) {
    return PY_invokeBoxedMethod(PY_getObjectAttributeByNameOrStatic(self_2, "target"), NULL, 0, NULL, NULL);
}

PyObjectContainer* testtarget_3_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    if (self == NULL)
    {
        assert(argc == 1);
        return testtarget_3(args[0]);
    }
    else
    {
        assert(argc == 0);
        return testtarget_3(self);
    }
}

