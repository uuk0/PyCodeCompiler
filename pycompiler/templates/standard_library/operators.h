//
// Created by baulu on 04.08.2023.
//

#ifndef TEMPLATES_OPERATORS_H
#define TEMPLATES_OPERATORS_H

#include "pyinclude.h"

PyObjectContainer* PY_STD_operator_add(PyObjectContainer* lhs, PyObjectContainer* rhs);
PyObjectContainer* PY_STD_operator_sub(PyObjectContainer* lhs, PyObjectContainer* rhs);
PyObjectContainer* PY_STD_operator_mul(PyObjectContainer* lhs, PyObjectContainer* rhs);
PyObjectContainer* PY_STD_operator_truediv(PyObjectContainer* lhs, PyObjectContainer* rhs);
PyObjectContainer* PY_STD_operator_floordiv(PyObjectContainer* lhs, PyObjectContainer* rhs);
PyObjectContainer* PY_STD_operator_modulo(PyObjectContainer* lhs, PyObjectContainer* rhs);

#endif //TEMPLATES_OPERATORS_H
