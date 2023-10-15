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
char* current_test_name;

#define PY_TEST_FAIL() PY_THROW_EXCEPTION(NULL); // fprintf(stderr, "failed test: %s\n", current_test_name); fflush(stdout); fflush(stderr); int* x = NULL; int y = *x;

PyObjectContainer* PY_MODULE_unittest_main(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 0);
    return PY_MODULE_unittest_main_fast();
}

PyObjectContainer* PY_MODULE_unittest_main_fast(void)
{
    PY_STD_list_container* container = PY_MODULE_unittest_TestCase_REGISTERED->raw_value;
    bool has_failed = false;
    int count = 0;
    int failed = 0;

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
                fprintf(stderr, "running test %s.%s...", cls_instance->class_name, cls_instance->static_attribute_names[j]);
                fflush(stderr);

                current_test_name = cls_instance->static_attribute_names[j];
                PyObjectContainer* method = PY_getObjectAttributeByNameOrStatic(obj, cls_instance->static_attribute_names[j]);
                if (method != NULL)
                {
                    count++;
                    PyObjectContainer* result = PY_invokeBoxedMethod(method, obj, 0, NULL, NULL);

                    if (result->type == PY_EXCEPTION)
                    {
                        fprintf(stderr, "\rtest %s.%s failed: %s\n", cls_instance->class_name, cls_instance->static_attribute_names[j],
                               PY_getObjectRepr(result));
                        has_failed = true;
                        j++;
                        failed++;
                        continue;
                    }
                    fprintf(stderr, "\rtest %s.%s completed successfully!\n", cls_instance->class_name, cls_instance->static_attribute_names[j]);
                }
                j++;
                fflush(stdout);
                fflush(stderr);
            }
        }
    }

    if (has_failed)
    {
        fprintf(stderr, "%i out of %i tests failed!\n", failed, count);
        exit(EXIT_FAILURE);
    }
    fprintf(stderr, "all %i test(s) where successful\n", count);
    exit(EXIT_SUCCESS);
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

PyObjectContainer* PY_MODULE_unittest_TestCase_fail(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    PY_TEST_FAIL();
}

PyObjectContainer* PY_MODULE_unittest_TestCase_fail_fast(PyObjectContainer* self)
{
    PY_TEST_FAIL();
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
        fprintf(stderr, "\nvalue: %s (should be True-ish)\n", PY_getObjectRepr(value));
        PY_TEST_FAIL();
    }
    return PY_NONE;
}

PyObjectContainer* PY_MODULE_unittest_TestCase_assertFalse(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 1);
    return PY_MODULE_unittest_TestCase_assertFalse_fast(self, args[0]);
}

PyObjectContainer* PY_MODULE_unittest_TestCase_assertFalse_fast(PyObjectContainer* self, PyObjectContainer* value)
{
    if (PY_getTruthValueOf(value))
    {
        fprintf(stderr, "\nvalue: %s (should be False-ish)\n", PY_getObjectRepr(value));
        PY_TEST_FAIL();
    }
    return PY_NONE;
}

PyObjectContainer* PY_MODULE_unittest_TestCase_assertEqual(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 2);
    return PY_MODULE_unittest_TestCase_assertEqual_fast(self, args[0], args[1]);
}

PyObjectContainer* PY_MODULE_unittest_TestCase_assertEqual_fast(PyObjectContainer* self, PyObjectContainer* value, PyObjectContainer* other)
{
    if (!PY_getTruthValueOf(PY_STD_operator_equals(value, other)))
    {
        fprintf(stderr, "\nlhs: %s !=\n", PY_getObjectRepr(value));
        fprintf(stderr, "rhs: %s\n", PY_getObjectRepr(other));
        PY_TEST_FAIL();
    }
    return PY_NONE;
}

PyObjectContainer* PY_MODULE_unittest_TestCase_assertNotEqual(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 2);
    return PY_MODULE_unittest_TestCase_assertNotEqual_fast(self, args[0], args[1]);
}

PyObjectContainer* PY_MODULE_unittest_TestCase_assertNotEqual_fast(PyObjectContainer* self, PyObjectContainer* value, PyObjectContainer* other)
{
    if (PY_getTruthValueOf(PY_STD_operator_equals(value, other)))
    {
        fprintf(stderr, "\nlhs: %s ==\n", PY_getObjectRepr(value));
        fprintf(stderr, "rhs: %s\n", PY_getObjectRepr(other));
        PY_TEST_FAIL();
    }
    return PY_NONE;
}

PyObjectContainer* PY_MODULE_unittest_TestCase_assertIs(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 2);
    return PY_MODULE_unittest_TestCase_assertIs_fast(self, args[0], args[1]);
}

PyObjectContainer* PY_MODULE_unittest_TestCase_assertIs_fast(PyObjectContainer* self, PyObjectContainer* value, PyObjectContainer* other)
{
    if (!PY_getTruthValueOf(PY_STD_operator_is(value, other)))
    {
        fprintf(stderr, "\nlhs: %s is not \n", PY_getObjectRepr(value));
        fprintf(stderr, "rhs: %s\n", PY_getObjectRepr(other));
        PY_TEST_FAIL();
    }
    return PY_NONE;
}

PyObjectContainer* PY_MODULE_unittest_TestCase_assertIsNot(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info)
{
    assert(argc == 2);
    return PY_MODULE_unittest_TestCase_assertIsNot_fast(self, args[0], args[1]);
}

PyObjectContainer* PY_MODULE_unittest_TestCase_assertIsNot_fast(PyObjectContainer* self, PyObjectContainer* value, PyObjectContainer* other)
{
    if (PY_getTruthValueOf(PY_STD_operator_is(value, other)))
    {
        fprintf(stderr, "\nlhs: %s is \n", PY_getObjectRepr(value));
        fprintf(stderr, "rhs: %s\n", PY_getObjectRepr(other));
        PY_TEST_FAIL();
    }
    return PY_NONE;
}

PyObjectContainer* PY_MODULE_unittest_TestCase_assertIn(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info) {
    assert(argc == 2);
    return PY_MODULE_unittest_TestCase_assertIn_fast(self, args[0], args[1]);
}

PyObjectContainer* PY_MODULE_unittest_TestCase_assertIn_fast(PyObjectContainer* self, PyObjectContainer* item, PyObjectContainer* container) {
    if (!PY_getTruthValueOf(PY_STD_operator_contains(container, item)))
    {
        fprintf(stderr, "\nlhs: %s not in \n", PY_getObjectRepr(item));
        fprintf(stderr, "rhs: %s\n", PY_getObjectRepr(container));
        PY_TEST_FAIL();
    }
    return PY_NONE;
}

PyObjectContainer* PY_MODULE_unittest_TestCase_assertNotIn(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info) {
    assert(argc == 2);
    return PY_MODULE_unittest_TestCase_assertNotIn_fast(self, args[0], args[1]);
}

PyObjectContainer* PY_MODULE_unittest_TestCase_assertNotIn_fast(PyObjectContainer* self, PyObjectContainer* item, PyObjectContainer* container) {
    if (PY_getTruthValueOf(PY_STD_operator_contains(container, item)))
    {
        fprintf(stderr, "\nlhs: %s in \n", PY_getObjectRepr(item));
        fprintf(stderr, "rhs: %s\n", PY_getObjectRepr(container));
        PY_TEST_FAIL();
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
    PY_setClassAttributeByNameOrCreate(PY_MODULE_unittest_TestCase, "fail", PY_createBoxForFunction(PY_MODULE_unittest_TestCase_fail));
    PY_setClassAttributeByNameOrCreate(PY_MODULE_unittest_TestCase, "assertTrue", PY_createBoxForFunction(PY_MODULE_unittest_TestCase_assertTrue));
    PY_setClassAttributeByNameOrCreate(PY_MODULE_unittest_TestCase, "assertFalse", PY_createBoxForFunction(PY_MODULE_unittest_TestCase_assertFalse));
    PY_setClassAttributeByNameOrCreate(PY_MODULE_unittest_TestCase, "assertEqual", PY_createBoxForFunction(PY_MODULE_unittest_TestCase_assertEqual));
    PY_setClassAttributeByNameOrCreate(PY_MODULE_unittest_TestCase, "assertNotEqual", PY_createBoxForFunction(PY_MODULE_unittest_TestCase_assertNotEqual));
    PY_setClassAttributeByNameOrCreate(PY_MODULE_unittest_TestCase, "assertIs", PY_createBoxForFunction(PY_MODULE_unittest_TestCase_assertIs));
    PY_setClassAttributeByNameOrCreate(PY_MODULE_unittest_TestCase, "assertIsNot", PY_createBoxForFunction(PY_MODULE_unittest_TestCase_assertIsNot));
    PY_setClassAttributeByNameOrCreate(PY_MODULE_unittest_TestCase, "assertIn", PY_createBoxForFunction(PY_MODULE_unittest_TestCase_assertIn));
    PY_setClassAttributeByNameOrCreate(PY_MODULE_unittest_TestCase, "assertNotIn", PY_createBoxForFunction(PY_MODULE_unittest_TestCase_assertNotIn));

    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_unittest, "main", PY_createBoxForFunction(PY_MODULE_unittest_main));

    PY_exposeModuleObject(PY_MODULE_INSTANCE_unittest);

    return PY_NONE;
}
