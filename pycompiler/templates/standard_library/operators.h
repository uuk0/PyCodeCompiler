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
PyObjectContainer* PY_STD_operator_contains(PyObjectContainer* lhs, PyObjectContainer* rhs);
PyObjectContainer* PY_STD_operator_not_contains(PyObjectContainer* lhs, PyObjectContainer* rhs);
PyObjectContainer* PY_STD_operator_is(PyObjectContainer* lhs, PyObjectContainer* rhs);
PyObjectContainer* PY_STD_operator_is_not(PyObjectContainer* lhs, PyObjectContainer* rhs);

PyObjectContainer* PY_STD_operator_not(PyObjectContainer* self);
PyObjectContainer* PY_STD_operator_negate(PyObjectContainer* self);
PyObjectContainer* PY_STD_operator_positive(PyObjectContainer* self);
PyObjectContainer* PY_STD_operator_invert(PyObjectContainer* self);

PyObjectContainer* PY_STD_operator_len(PyObjectContainer* value);
PyObjectContainer* PY_STD_operator_next(PyObjectContainer* value);
PyObjectContainer* PY_STD_operator_iter(PyObjectContainer* value);  // implementation only provided when generators are enabled!
PyObjectContainer* PY_STD_operator_next_with_default(PyObjectContainer* value, PyObjectContainer* default_value);

PyObjectContainer* PY_STD_operator_inplace_add(PyObjectContainer* lhs, PyObjectContainer* rhs);
PyObjectContainer* PY_STD_operator_inplace_sub(PyObjectContainer* lhs, PyObjectContainer* rhs);
PyObjectContainer* PY_STD_operator_inplace_mul(PyObjectContainer* lhs, PyObjectContainer* rhs);
PyObjectContainer* PY_STD_operator_inplace_truediv(PyObjectContainer* lhs, PyObjectContainer* rhs);
PyObjectContainer* PY_STD_operator_inplace_floordiv(PyObjectContainer* lhs, PyObjectContainer* rhs);
PyObjectContainer* PY_STD_operator_inplace_modulo(PyObjectContainer* lhs, PyObjectContainer* rhs);
PyObjectContainer* PY_STD_operator_inplace_pow(PyObjectContainer* lhs, PyObjectContainer* rhs);
PyObjectContainer* PY_STD_operator_inplace_matrix_multiply(PyObjectContainer* lhs, PyObjectContainer* rhs);
PyObjectContainer* PY_STD_operator_inplace_bin_or(PyObjectContainer* lhs, PyObjectContainer* rhs);
PyObjectContainer* PY_STD_operator_inplace_bin_and(PyObjectContainer* lhs, PyObjectContainer* rhs);
PyObjectContainer* PY_STD_operator_inplace_bin_xor(PyObjectContainer* lhs, PyObjectContainer* rhs);

// defined as a macro so we evaluate 'value' only when needed
#define PY_STD_operator_iter_for_yield_from(value, possible_existing) (possible_existing != NULL ? possible_existing : PY_STD_operator_iter(value))

#endif //TEMPLATES_OPERATORS_H
