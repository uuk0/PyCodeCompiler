//
// Created by baulu on 04.08.2023.
//

#include <assert.h>
#include "operators.h"
#include "string.h"
#include "exceptions.h"
#include "config.h"
#include <math.h>

#ifdef PY_ENABLE_GENERATORS
#include "generator.h"
#endif

static inline PyObjectContainer* PY_STD_operator_apply(PyObjectContainer* lhs, PyObjectContainer* rhs, char* lopname, char* ropname)
{
    PyObjectContainer* lop = PY_getObjectAttributeByNameOrStatic(lhs, lopname);

    if (lop == NULL)
    {
        PY_THROW_EXCEPTION_IF_WITH_MESSAGE_AND_OBJ(lop == NULL && ropname == NULL, NULL, "expected supporting operator, got %s\n", lhs);
        PyObjectContainer* rop = PY_getObjectAttributeByNameOrStatic(lhs, ropname);
        PY_THROW_EXCEPTION_IF_WITH_MESSAGE_AND_OBJ(rop == NULL, NULL, "expected supporting operator (or rhs inverse), got %s\n", lhs);
        return PY_invokeBoxedMethod(rop, rhs, 1, &lhs, NULL);
    }
    return PY_invokeBoxedMethod(lop, lhs, 1, &rhs, NULL);
}

static inline PyObjectContainer* PY_STD_operator_apply_or_default(PyObjectContainer* lhs, PyObjectContainer* rhs, char* lopname, char* ropname, PyObjectContainer* default_value)
{
    PyObjectContainer* lop = PY_getObjectAttributeByNameOrStatic(lhs, lopname);

    if (lop == NULL)
    {
        if (ropname == NULL)
        {
            return default_value;
        }

        PyObjectContainer* rop = PY_getObjectAttributeByNameOrStatic(lhs, ropname);

        if (rop == NULL)
        {
            return default_value;
        }

        return PY_invokeBoxedMethod(rop, rhs, 1, &lhs, NULL);
    }

    return PY_invokeBoxedMethod(lop, lhs, 1, &rhs, NULL);
}

PyObjectContainer* PY_STD_operator_add(PyObjectContainer* lhs, PyObjectContainer* rhs)
{
    if (lhs->type == PY_TYPE_INT)
    {
        if (rhs->type == PY_TYPE_FLOAT)
        {
            return PY_createFloat((float) PY_unpackInteger(lhs) + PY_unpackFloat(rhs));
        }

        PY_THROW_EXCEPTION_IF(rhs->type != PY_TYPE_INT, NULL);
        return PY_createInteger(PY_unpackInteger(lhs) + PY_unpackInteger(rhs));
    }
    else if (lhs->type == PY_TYPE_FLOAT)
    {
        if (rhs->type == PY_TYPE_INT)
        {
            return PY_createFloat(PY_unpackFloat(lhs) + (double) PY_unpackInteger(rhs));
        }

        PY_THROW_EXCEPTION_IF(rhs->type != PY_TYPE_FLOAT, NULL);
        return PY_createFloat(PY_unpackFloat(lhs) + PY_unpackFloat(rhs));
    }

    return PY_STD_operator_apply(lhs, rhs, "__add__", "__radd__");
}


PyObjectContainer* PY_STD_operator_sub(PyObjectContainer* lhs, PyObjectContainer* rhs)
{
    if (lhs->type == PY_TYPE_INT)
    {
        if (rhs->type == PY_TYPE_FLOAT)
        {
            return PY_createFloat((float) PY_unpackInteger(lhs) - PY_unpackFloat(rhs));
        }

        PY_THROW_EXCEPTION_IF(rhs->type != PY_TYPE_INT, NULL);
        return PY_createInteger(PY_unpackInteger(lhs) - PY_unpackInteger(rhs));
    }
    else if (lhs->type == PY_TYPE_FLOAT)
    {
        if (rhs->type == PY_TYPE_INT)
        {
            return PY_createFloat(PY_unpackFloat(lhs) - (double) PY_unpackInteger(rhs));
        }

        PY_THROW_EXCEPTION_IF(rhs->type != PY_TYPE_FLOAT, NULL);
        return PY_createFloat(PY_unpackFloat(lhs) - PY_unpackFloat(rhs));
    }

    return PY_STD_operator_apply(lhs, rhs, "__sub__", "__rsub__");
}

PyObjectContainer* PY_STD_operator_mul(PyObjectContainer* lhs, PyObjectContainer* rhs)
{
    if (lhs->type == PY_TYPE_INT)
    {
        if (rhs->type == PY_TYPE_FLOAT)
        {
            return PY_createFloat((float) PY_unpackInteger(lhs) * PY_unpackFloat(rhs));
        }

        PY_THROW_EXCEPTION_IF(rhs->type != PY_TYPE_INT, NULL);
        return PY_createInteger(PY_unpackInteger(lhs) * PY_unpackInteger(rhs));
    }
    else if (lhs->type == PY_TYPE_FLOAT)
    {
        if (rhs->type == PY_TYPE_INT)
        {
            return PY_createFloat(PY_unpackFloat(lhs) * (double) PY_unpackInteger(rhs));
        }

        PY_THROW_EXCEPTION_IF(rhs->type != PY_TYPE_FLOAT, NULL);
        return PY_createFloat(PY_unpackFloat(lhs) * PY_unpackFloat(rhs));
    }

    return PY_STD_operator_apply(lhs, rhs, "__mul__", "__rmul__");
}

PyObjectContainer* PY_STD_operator_truediv(PyObjectContainer* lhs, PyObjectContainer* rhs)
{
    if (lhs->type == PY_TYPE_INT)
    {
        if (rhs->type == PY_TYPE_FLOAT)
        {
            assert(PY_unpackFloat(rhs) != 0);
            return PY_createFloat((float) PY_unpackInteger(lhs) / PY_unpackFloat(rhs));
        }

        PY_THROW_EXCEPTION_IF(rhs->type != PY_TYPE_INT, NULL);
        PY_THROW_EXCEPTION_IF(PY_unpackInteger(rhs) != 0, NULL);

        return PY_createFloat(((double)PY_unpackInteger(lhs)) / ((double)PY_unpackInteger(rhs)));
    }
    else if (lhs->type == PY_TYPE_FLOAT)
    {
        if (rhs->type == PY_TYPE_INT)
        {
            return PY_createFloat(PY_unpackFloat(lhs) / (double) PY_unpackInteger(rhs));
        }

        PY_THROW_EXCEPTION_IF(rhs->type != PY_TYPE_FLOAT, NULL);
        PY_THROW_EXCEPTION_IF(PY_unpackFloat(rhs) != 0, NULL);
        return PY_createFloat(PY_unpackFloat(lhs) / PY_unpackFloat(rhs));
    }

    return PY_STD_operator_apply(lhs, rhs, "__truediv__", "__rtruediv__");
}

PyObjectContainer* PY_STD_operator_floordiv(PyObjectContainer* lhs, PyObjectContainer* rhs)
{
    if (lhs->type == PY_TYPE_INT)
    {
        if (rhs->type == PY_TYPE_FLOAT)
        {
            PY_THROW_EXCEPTION_IF_WITH_MESSAGE(PY_unpackFloat(rhs) == 0, NULL, "rhs is 0");
            return PY_createInteger((int64_t)((double)PY_unpackInteger(lhs) / PY_unpackFloat(rhs)));
        }

        PY_THROW_EXCEPTION_IF_WITH_MESSAGE(rhs->type != PY_TYPE_INT, NULL, "rhs not int (or float)");
        PY_THROW_EXCEPTION_IF_WITH_MESSAGE(PY_unpackInteger(rhs) == 0, NULL, "rhs is 0");
        return PY_createInteger(PY_unpackInteger(lhs) / PY_unpackInteger(rhs));
    }
    else if (lhs->type == PY_TYPE_FLOAT)
    {
        if (rhs->type == PY_TYPE_INT)
        {
            PY_THROW_EXCEPTION_IF_WITH_MESSAGE(PY_unpackInteger(rhs) == 0, NULL, "rhs is 0");
            return PY_createInteger((int64_t)(PY_unpackFloat(lhs) / (double) PY_unpackInteger(rhs)));
        }

        PY_THROW_EXCEPTION_IF_WITH_MESSAGE(rhs->type != PY_TYPE_FLOAT, NULL, "rhs is not float (or int)");
        PY_THROW_EXCEPTION_IF_WITH_MESSAGE(PY_unpackFloat(rhs) == 0, NULL, "rhs is 0");
        return PY_createInteger((int64_t)(PY_unpackFloat(lhs) + PY_unpackFloat(rhs)));
    }

    return PY_STD_operator_apply(lhs, rhs, "__floordiv__", "__rfloordiv__");
}

PyObjectContainer* PY_STD_operator_modulo(PyObjectContainer* lhs, PyObjectContainer* rhs)
{
    if (lhs->type == PY_TYPE_INT)
    {
        // todo: float
        PY_THROW_EXCEPTION_IF(rhs->type != PY_TYPE_INT, NULL);
        PY_THROW_EXCEPTION_IF(PY_unpackInteger(rhs) == 0, NULL);

        return PY_createInteger(PY_unpackInteger(lhs) & PY_unpackInteger(rhs));
    }

    return PY_STD_operator_apply(lhs, rhs, "__mod__", "__rmod__");
}

PyObjectContainer* PY_STD_operator_pow(PyObjectContainer* lhs, PyObjectContainer* rhs)
{
    long double lhs_v;
    long double rhs_v;

    if (lhs->type == PY_TYPE_INT) {
        lhs_v = (long double) PY_unpackInteger(lhs);
    }
    else if (lhs->type == PY_TYPE_FLOAT)
    {
        lhs_v = PY_unpackFloat(lhs);
    }
    else
    {
        return PY_STD_operator_apply(lhs, rhs, "__pow__", "__rpow__");
    }

    if (rhs->type == PY_TYPE_INT)
    {
        rhs_v = (long double) PY_unpackInteger(rhs);
    }
    else if (rhs->type == PY_TYPE_FLOAT)
    {
        rhs_v = PY_unpackFloat(rhs);
    }
    else
    {
        return PY_STD_operator_apply(lhs, rhs, "__pow__", "__rpow__");
    }

    // 0 ** 0 is undefined, so throw an exception
    PY_THROW_EXCEPTION_IF(lhs_v == 0 && rhs_v == 0, NULL);

    long double value = powl(lhs_v, rhs_v);

    return lhs->type == PY_TYPE_INT && rhs->type == PY_TYPE_INT ? PY_createInteger((int64_t)value) : PY_createFloat((double)value);
}

PyObjectContainer* PY_STD_operator_matrix_multiply(PyObjectContainer* lhs, PyObjectContainer* rhs)
{
    return PY_STD_operator_apply(lhs, rhs, "__matmul__", "__rmatmul__");
}

PyObjectContainer* PY_STD_operator_bin_or(PyObjectContainer* lhs, PyObjectContainer* rhs)
{
    if (lhs->type == PY_TYPE_INT)
    {
        PY_THROW_EXCEPTION_IF(rhs->type != PY_TYPE_INT, NULL);
        PY_THROW_EXCEPTION_IF(PY_unpackInteger(rhs) == 0, NULL);

        return PY_createInteger(PY_unpackInteger(lhs) | PY_unpackInteger(rhs));
    }

    return PY_STD_operator_apply(lhs, rhs, "__or__", "__ror__");
}

PyObjectContainer* PY_STD_operator_bin_and(PyObjectContainer* lhs, PyObjectContainer* rhs)
{
    if (lhs->type == PY_TYPE_INT)
    {
        PY_THROW_EXCEPTION_IF(rhs->type != PY_TYPE_INT, NULL);
        PY_THROW_EXCEPTION_IF(PY_unpackInteger(rhs) == 0, NULL);

        return PY_createInteger(PY_unpackInteger(lhs) & PY_unpackInteger(rhs));
    }

    return PY_STD_operator_apply(lhs, rhs, "__and__", "__rand__");
}

PyObjectContainer* PY_STD_operator_bin_xor(PyObjectContainer* lhs, PyObjectContainer* rhs)
{
    if (lhs->type == PY_TYPE_INT)
    {
        PY_THROW_EXCEPTION_IF(rhs->type != PY_TYPE_INT, NULL);
        PY_THROW_EXCEPTION_IF(PY_unpackInteger(rhs) == 0, NULL);

        return PY_createInteger(PY_unpackInteger(lhs) ^ PY_unpackInteger(rhs));
    }

    return PY_STD_operator_apply(lhs, rhs, "__xor__", "__rxor__");
}

PyObjectContainer* PY_STD_operator_equals(PyObjectContainer* lhs, PyObjectContainer* rhs)
{
    assert(lhs != NULL && "LHS must not be NULL");
    assert(rhs != NULL && "RHS must not be NULL");

    if (lhs->type == PY_TYPE_INT)
    {
        if (rhs->type == PY_TYPE_FLOAT)
        {
            double rhs_v = PY_unpackFloat(rhs);
            return PY_createBoolean(rhs_v == (int64_t)rhs_v && PY_unpackInteger(lhs) == (int64_t)rhs_v);
        }
        else if (rhs->type != PY_TYPE_INT)
        {
            return PY_FALSE;
        }

        return PY_createBoolean(PY_unpackInteger(lhs) == PY_unpackInteger(rhs));
    }
    else if (lhs->type == PY_TYPE_FLOAT)
    {
        if (rhs->type == PY_TYPE_INT)
        {
            double lhs_v = PY_unpackFloat(lhs);
            return PY_createBoolean(lhs_v == (int64_t)lhs_v && PY_unpackInteger(rhs) == (int64_t)lhs_v);
        }
        else if (rhs->type != PY_TYPE_FLOAT)
        {
            return PY_FALSE;
        }

        return PY_createBoolean(PY_unpackFloat(lhs) == PY_unpackFloat(rhs));
    }
    else if (lhs == PY_NONE)
    {
        return PY_createBoolean(rhs == PY_NONE);
    }
    else if (lhs == PY_FALSE)
    {
        return PY_createBoolean(rhs == PY_FALSE);
    }
    else if (lhs == PY_TRUE)
    {
        return PY_createBoolean(rhs == PY_TRUE);
    }
    else if (lhs->type == PY_TYPE_STRING)
    {
        return PY_STD_string_eq_fast(lhs, rhs);
    }

    // when both do not provide __eq__, the value should be PY_FALSE, as they cannot be compared
    return PY_STD_operator_apply_or_default(lhs, rhs, "__eq__", "__eq__", PY_FALSE);
}

PyObjectContainer* PY_STD_operator_not_equals(PyObjectContainer* lhs, PyObjectContainer* rhs)
{
    PyObjectContainer* equal = PY_STD_operator_equals(lhs, rhs);
    PY_CHECK_EXCEPTION(equal);

    return equal == PY_FALSE ? PY_TRUE : PY_FALSE;
}

PyObjectContainer* PY_STD_operator_contains(PyObjectContainer* lhs, PyObjectContainer* rhs)
{
    return PY_STD_operator_apply(lhs, rhs, "__contains__", NULL);
}

PyObjectContainer* PY_STD_operator_not_contains(PyObjectContainer* lhs, PyObjectContainer* rhs)
{
    return PY_STD_operator_apply(lhs, rhs, "__contains__", NULL) == PY_TRUE ? PY_FALSE : PY_TRUE;
}

PyObjectContainer* PY_STD_operator_is(PyObjectContainer* lhs, PyObjectContainer* rhs)
{
    return PY_createBoolean(lhs == rhs);
}

PyObjectContainer* PY_STD_operator_is_not(PyObjectContainer* lhs, PyObjectContainer* rhs)
{
    return PY_createBoolean(lhs != rhs);
}

PyObjectContainer* PY_STD_operator_len(PyObjectContainer* value)
{
    PyObjectContainer* len = PY_getObjectAttributeByNameOrStatic(value, "__len__");
    PY_THROW_EXCEPTION_IF_WITH_MESSAGE_AND_OBJ(len == NULL, NULL, "expected <supports __len__>, got %s\n", value);
    return PY_invokeBoxedMethod(len, value, 0, NULL, NULL);
}

PyObjectContainer* PY_STD_operator_next(PyObjectContainer* value)
{
    PyObjectContainer* next = PY_getObjectAttributeByNameOrStatic(value, "__next__");
    PY_THROW_EXCEPTION_IF_WITH_MESSAGE_AND_OBJ(next == NULL, NULL, "expected <supports __next__>, got %s\n", value);
    return PY_invokeBoxedMethod(next, value, 0, NULL, NULL);
}

PyObjectContainer* PY_STD_operator_next_with_default(PyObjectContainer* value, PyObjectContainer* default_value)
{
    PyObjectContainer* next = PY_getObjectAttributeByNameOrStatic(value, "__next__");
    PY_THROW_EXCEPTION_IF_WITH_MESSAGE_AND_OBJ(next == NULL, NULL, "expected <supports __next__>, got %s\n", value);
    return PY_invokeBoxedMethod(next, value, 1, &default_value, NULL);
}

#ifdef PY_ENABLE_GENERATORS
PyObjectContainer* PY_STD_operator_iter(PyObjectContainer* value)
{
    PyObjectContainer* iterator = PY_getObjectAttributeByNameOrStatic(value, "__iter__");
    PY_THROW_EXCEPTION_IF_WITH_MESSAGE_AND_OBJ(iterator == NULL, NULL, "expected <supports __iter__>, got %s\n", value);
    PyObjectContainer* result = PY_invokeBoxedMethod(iterator, value, 0, NULL, NULL);
    PY_THROW_EXCEPTION_IF_WITH_MESSAGE_AND_OBJ(result->type != PY_TYPE_PY_IMPL || result->py_type != PY_TYPE_GENERATOR, NULL, "invalid result for __iter__, expected <generator>, got %s\n", result);
    return result;
}
#endif

