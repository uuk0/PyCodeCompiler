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
PyObjectContainer* PY_STD_operator_pow(PyObjectContainer* lhs, PyObjectContainer* rhs);
PyObjectContainer* PY_STD_operator_matrix_multiply(PyObjectContainer* lhs, PyObjectContainer* rhs);
PyObjectContainer* PY_STD_operator_bin_or(PyObjectContainer* lhs, PyObjectContainer* rhs);
PyObjectContainer* PY_STD_operator_bin_and(PyObjectContainer* lhs, PyObjectContainer* rhs);
PyObjectContainer* PY_STD_operator_bin_xor(PyObjectContainer* lhs, PyObjectContainer* rhs);
PyObjectContainer* PY_STD_operator_equals(PyObjectContainer* lhs, PyObjectContainer* rhs);
PyObjectContainer* PY_STD_operator_not_equals(PyObjectContainer* lhs, PyObjectContainer* rhs);

PyObjectContainer* PY_STD_operator_len(PyObjectContainer* value);

#endif //TEMPLATES_OPERATORS_H
