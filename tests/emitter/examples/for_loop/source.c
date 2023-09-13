#include <stdlib.h>

#include "pyinclude.h"
#include "standard_library/config.h"

#include "standard_library/init.h"
#include "standard_library/exceptions.h"

#ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
#include "standard_library/importhelper.h"
#endif

#include "source.h"

#ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
PyObjectContainer* PY_MODULE_INSTANCE_source;
#endif

// code compiled from python to c via PyCodeCompiler

#include <assert.h>



// Global Variables
PyObjectContainer* value_1;
PyObjectContainer* value_3;



// implementations

PyObjectContainer* PY_MODULE_source_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_MODULE_INSTANCE_source = PY_createModuleObject("source");
    #endif


    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "test", PY_createBoxForFunction(test_0_safeWrap));
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "test_2", PY_createBoxForFunction(test2_1_safeWrap));
    PY_exposeModuleObject(PY_MODULE_INSTANCE_source);
    #endif
}

PyObjectContainer* test_0(void) {
    PyObjectContainer* l_2;
    PyObjectContainer* s_3;
    PyObjectContainer* x_4;

    l_2 = PY_STD_list_CREATE(3, PY_createInteger(1), PY_createInteger(2), PY_createInteger(3));

    s_3 = PY_createInteger(0);


    PyObjectContainer* iterator_0 = PY_CHECK_EXCEPTION(PY_STD_operator_iter(l_2));
    PyObjectContainer* value_1 = PY_STD_NEXT_FORWARD_arg_1(iterator_0, NULL);
    while (value_1 != NULL) {
        PY_CHECK_EXCEPTION(value_1);
        x_4 = value_1;
        s_3 = PY_STD_operator_add(s_3, x_4);


        value_1 = PY_STD_NEXT_FORWARD_arg_1(iterator_0, NULL);
    }
    return s_3;



    return PY_NONE;
}

PyObjectContainer* test_0_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return test_0();
}

PyObjectContainer* test2_1(void) {
    PyObjectContainer* l_5;
    PyObjectContainer* s_6;
    PyObjectContainer* x_7;
    PyObjectContainer* y_8;

    l_5 = PY_STD_list_CREATE(3, PY_STD_tuple_CREATE(2, PY_createInteger(1), PY_createInteger(3)), PY_STD_tuple_CREATE(2, PY_createInteger(7), PY_createInteger(9)), PY_STD_tuple_CREATE(2, PY_createInteger(2), PY_createInteger(3)));

    s_6 = PY_createInteger(0);


    PyObjectContainer* iterator_2 = PY_CHECK_EXCEPTION(PY_STD_operator_iter(l_5));
    PyObjectContainer* value_3 = PY_STD_NEXT_FORWARD_arg_1(iterator_2, NULL);
    while (value_3 != NULL) {
        PY_CHECK_EXCEPTION(value_3);
        PyObjectContainer* temporary_tuple_4 = value_3;
        assert(PY_unpackInteger(PY_STD_operator_len(temporary_tuple_4)) == 2);
        x_7 = PY_GetSubscriptionValue(temporary_tuple_4, PY_createInteger(0));
        y_8 = PY_GetSubscriptionValue(temporary_tuple_4, PY_createInteger(1));
        ;
        s_6 = PY_STD_operator_floordiv(x_7, y_8);


        value_3 = PY_STD_NEXT_FORWARD_arg_1(iterator_2, NULL);
    }
    return s_6;
}

PyObjectContainer* test2_1_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return test2_1();
}

