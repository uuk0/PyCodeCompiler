#include "pyinclude.h"
#include "standard_library/init.h"

// code compiled from python to c via PyCodeCompiler

#include <assert.h>


int _initialise();
PyObjectContainer* test_0();
PyObjectContainer* test_0_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args);


// implementations

int _initialise() {
    PY_STD_INIT();
}

PyObjectContainer* test_0() {
    PyObjectContainer* obj_1;


    PyObjectContainer* obj_instance_0 = PY_createClassInstance(PY_TYPE_LIST);
    PyObjectContainer* constructor_1 = PY_getObjectAttributeByNameOrStatic(obj_instance_0, "__init__");

    assert(constructor_1 != NULL);
    PY_invokeBoxedMethod(constructor_1, NULL, 0, NULL);
    DECREF(constructor_1);
    obj_1 = obj_instance_0;

    PyObjectContainer* temporary_2 = PY_getObjectAttributeByNameOrStatic(obj_1, "append");
    PyObjectContainer* args_3[1];
    args_3[0] = PY_createInteger(10);
    PY_invokeBoxedMethod(temporary_2, NULL, 1, args_3);

    PyObjectContainer* temporary_4 = PY_getObjectAttributeByNameOrStatic(obj_1, "append");
    PyObjectContainer* args_5[1];
    args_5[0] = PY_createInteger(20);
    PY_invokeBoxedMethod(temporary_4, NULL, 1, args_5);

    PyObjectContainer* temporary_6 = PY_getObjectAttributeByNameOrStatic(obj_1, "index");
    PyObjectContainer* args_7[1];
    args_7[0] = PY_createInteger(10);
    PY_invokeBoxedMethod(temporary_6, NULL, 1, args_7);

    PyObjectContainer* temporary_8 = PY_getObjectAttributeByNameOrStatic(obj_1, "remove");
    PyObjectContainer* args_9[1];
    args_9[0] = PY_createInteger(10);
    PY_invokeBoxedMethod(temporary_8, NULL, 1, args_9);

    PyObjectContainer* temporary_10 = PY_getObjectAttributeByNameOrStatic(obj_1, "append");
    PyObjectContainer* args_11[1];
    args_11[0] = PY_createInteger(30);
    PY_invokeBoxedMethod(temporary_10, NULL, 1, args_11);

    PY_SetSubscriptionValue(obj_1, PY_createInteger(0), PY_createInteger(25));

    PY_SetSubscriptionValue(obj_1, PY_createInteger(1), PY_GetSubscriptionValue(obj_1, PY_createInteger(1)));
}

PyObjectContainer* test_0_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args) {
    assert(self == NULL);
    assert(argc == 0);
    return test_0();
}

