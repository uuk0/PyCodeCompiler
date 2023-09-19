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



// implementations

PyObjectContainer* PY_MODULE_source_init(void) {
    INVOKE_SINGLE();
    PY_STD_INIT();
    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_MODULE_INSTANCE_source = PY_createModuleObject("source");
    #endif

    #ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_source, "test", PY_createBoxForFunction(test_0_safeWrap));
    PY_exposeModuleObject(PY_MODULE_INSTANCE_source);
    #endif
}

PyObjectContainer* test_0(void) {
    PyObjectContainer* i_1;
    PyObjectContainer* x_2;

    x_2 = PY_createInteger(0);

    PyObjectContainer* iterator_0 = PY_CHECK_EXCEPTION(PY_STD_operator_iter(PY_CHECK_EXCEPTION(PY_STD_range_arg_1 (PY_createInteger(4)))));
    PyObjectContainer* value_1 = PY_STD_NEXT_FORWARD_arg_1(iterator_0, NULL);
    while (value_1 != NULL) {
        PY_CHECK_EXCEPTION(value_1);
        i_1 = value_1;
        x_2 = PY_STD_operator_add(x_2, i_1);


        value_1 = PY_STD_NEXT_FORWARD_arg_1(iterator_0, NULL);
    }
    return x_2;
}

PyObjectContainer* test_0_safeWrap(PyObjectContainer* self , uint8_t argc , PyObjectContainer** args , CallStructureInfo* info) {
    assert(self == NULL);
    assert(argc == 0);
    return test_0();
}
