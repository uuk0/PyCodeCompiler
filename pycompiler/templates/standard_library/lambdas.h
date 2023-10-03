//
// Created by baulu on 03.10.2023.
//

#ifndef PYCCOMPILER_LAMBDAS_H
#define PYCCOMPILER_LAMBDAS_H
#include "pyinclude.h"

extern PyClassContainer* PY_TYPE_lambda;
extern PyObjectContainer* PY_STD_invoke_lambda_CONTAINER;

PyObjectContainer** PY_CREATE_lambda_locals(uint8_t count, ...);
PyObjectContainer* PY_CREATE_lambda_WRAPPER(PyObjectContainer* call_fwd, PyObjectContainer** locals);
PyObjectContainer* PY_STD_invoke_lambda(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info);
PyObjectContainer* PY_STD_lambda_helper_init(void);

#endif //PYCCOMPILER_LAMBDAS_H
