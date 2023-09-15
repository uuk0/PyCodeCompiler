//
// Created by baulu on 08.09.2023.
//

#ifndef PYCCOMPILER_UNITTEST_H
#define PYCCOMPILER_UNITTEST_H

#include "pyinclude.h"

extern PyObjectContainer* PY_MODULE_INSTANCE_unittest;

extern PyClassContainer* PY_MODULE_unittest_TestCase;

PyObjectContainer* PY_MODULE_unittest_main(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_MODULE_unittest_main_fast(void);

PyObjectContainer* PY_MODULE_unittest_TestCase_initsubclass(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_MODULE_unittest_TestCase_initsubclass_fast(PyObjectContainer* cls);

PyObjectContainer* PY_MODULE_unittest_TestCase_assertTrue(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_MODULE_unittest_TestCase_assertTrue_fast(PyObjectContainer* self, PyObjectContainer* value);

PyObjectContainer* PY_MODULE_unittest_TestCase_assertFalse(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_MODULE_unittest_TestCase_assertFalse_fast(PyObjectContainer* self, PyObjectContainer* value);

PyObjectContainer* PY_MODULE_unittest_TestCase_assertEqual(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_MODULE_unittest_TestCase_assertEqual_fast(PyObjectContainer* self, PyObjectContainer* value, PyObjectContainer* other);

PyObjectContainer* PY_MODULE_unittest_TestCase_assertNotEqual(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_MODULE_unittest_TestCase_assertNotEqual_fast(PyObjectContainer* self, PyObjectContainer* value, PyObjectContainer* other);

PyObjectContainer* PY_MODULE_unittest_init(void);

#endif //PYCCOMPILER_UNITTEST_H
