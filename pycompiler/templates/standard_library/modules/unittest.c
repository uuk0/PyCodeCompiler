//
// Created by baulu on 08.09.2023.
//

#include <stdlib.h>
#include <assert.h>
#include "unittest.h"
#include "pyinclude.h"
#include "standard_library/importhelper.h"
#include "standard_library/list.h"
#include "standard_library/string.h"
#include "standard_library/exceptions.h"
#include "standard_library/operators.h"

PyObjectContainer* PY_MODULE_INSTANCE_unittest;
PyClassContainer* PY_MODULE_unittest_TestCase;
PyObjectContainer* PY_MODULE_unittest_TestCase_REGISTERED;

PyObjectContainer* PY_MODULE_unittest_main(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 0);
    return PY_MODULE_unittest_main_fast();
}

PyObjectContainer* PY_MODULE_unittest_main_fast(void)
{
    PY_STD_list_container* container = PY_MODULE_unittest_TestCase_REGISTERED->raw_value;

    for (int i = 0; i < container->curr_size; i++)
    {
        PyObjectContainer* cls = container->array[i];
        PyClassContainer* cls_instance = PY_unwrapClassContainer(cls);
        PyObjectContainer* obj = PY_createClassInstance(cls_instance);

        if (cls_instance->static_attribute_names == NULL) return NULL;

        int j = 0;
        while (cls_instance->static_attribute_names[j] != NULL) {
            if (PY_STD_string_startswith_impl(cls_instance->static_attribute_names[j], "test"))
            {
                PyObjectContainer* method = PY_getObjectAttributeByNameOrStatic(obj, cls_instance->static_attribute_names[j]);
                if (method != NULL)
                {
                    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(method, obj, 0, NULL, NULL));
                }
                j++;
            }
        }
    }

    return PY_NONE;
}

PyObjectContainer* PY_MODULE_unittest_TestCase_initsubclass(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 0);
    return PY_MODULE_unittest_TestCase_initsubclass_fast(self);
}

PyObjectContainer* PY_MODULE_unittest_TestCase_initsubclass_fast(PyObjectContainer* cls)
{
    PY_STD_list_append_fast(PY_MODULE_unittest_TestCase_REGISTERED, cls);
    return PY_NONE;
}

PyObjectContainer* PY_MODULE_unittest_TestCase_assertTrue(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 1);
    return PY_MODULE_unittest_TestCase_assertTrue_fast(self, args[0]);
}

PyObjectContainer* PY_MODULE_unittest_TestCase_assertTrue_fast(PyObjectContainer* self, PyObjectContainer* value)
{
    if (!PY_getTruthValueOf(value))
    {
        PY_THROW_EXCEPTION_WITH_MESSAGE(NULL, "test failed");
    }
    return PY_NONE;
}

PyObjectContainer* PY_MODULE_unittest_init(void)
{
    INVOKE_SINGLE();

    PY_MODULE_unittest_TestCase_REGISTERED = PY_STD_list_CREATE(0);

    PY_MODULE_INSTANCE_unittest = PY_createModuleObject("unittest");

    PY_MODULE_unittest_TestCase = PY_createClassContainer("TestCase");
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_unittest, "TestCase", PY_createClassWrapper(PY_MODULE_unittest_TestCase));

    PY_setClassAttributeByNameOrCreate(PY_MODULE_unittest_TestCase, "__init_subclass__", PY_createBoxForFunction(PY_MODULE_unittest_TestCase_initsubclass));
    PY_setClassAttributeByNameOrCreate(PY_MODULE_unittest_TestCase, "assertTrue", PY_createBoxForFunction(PY_MODULE_unittest_TestCase_assertTrue));

    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_unittest, "main", PY_createBoxForFunction(PY_MODULE_unittest_main));

    PY_exposeModuleObject(PY_MODULE_INSTANCE_unittest);

    return PY_NONE;
}
