//
// Created by baulu on 04.08.2023.
//

#include <assert.h>
#include "operators.h"

static inline PyObjectContainer* PY_STD_operator_apply(PyObjectContainer* lhs, PyObjectContainer* rhs, char* lopname, char* ropname)
{
    PyObjectContainer* lop = PY_getObjectAttributeByNameOrStatic(lhs, lopname);

    if (lop == NULL)
    {
        PyObjectContainer* rop = PY_getObjectAttributeByNameOrStatic(lhs, ropname);

        assert(lop != NULL || rop != NULL);

        return PY_invokeBoxedMethod(rop, rhs, 1, &lhs, NULL);
    }

    return PY_invokeBoxedMethod(lop, lhs, 1, &rhs, NULL);
}

PyObjectContainer* PY_STD_operator_add(PyObjectContainer* lhs, PyObjectContainer* rhs)
{
    if (lhs->type == PY_TYPE_INT)
    {
        assert(rhs->type == PY_TYPE_INT);  // TODO: float

        return PY_createInteger(PY_unpackInteger(lhs) + PY_unpackInteger(rhs));
    }

    return PY_STD_operator_apply(lhs, rhs, "__add__", "__radd__");
}


PyObjectContainer* PY_STD_operator_sub(PyObjectContainer* lhs, PyObjectContainer* rhs)
{
    if (lhs->type == PY_TYPE_INT)
    {
        assert(rhs->type == PY_TYPE_INT);  // TODO: float

        return PY_createInteger(PY_unpackInteger(lhs) - PY_unpackInteger(rhs));
    }

    return PY_STD_operator_apply(lhs, rhs, "__sub__", "__rsub__");
}

PyObjectContainer* PY_STD_operator_mul(PyObjectContainer* lhs, PyObjectContainer* rhs)
{
    if (lhs->type == PY_TYPE_INT)
    {
        assert(rhs->type == PY_TYPE_INT);  // TODO: float

        return PY_createInteger(PY_unpackInteger(lhs) * PY_unpackInteger(rhs));
    }

    return PY_STD_operator_apply(lhs, rhs, "__mul__", "__rmul__");
}

PyObjectContainer* PY_STD_operator_truediv(PyObjectContainer* lhs, PyObjectContainer* rhs)
{
    if (lhs->type == PY_TYPE_INT)
    {
        assert(rhs->type == PY_TYPE_INT);  // TODO: float
        assert(PY_unpackInteger(rhs) != 0);

        // return PY_createFloat(((double)PY_unpackInteger(lhs)) / ((double)PY_unpackInteger(rhs)));
        assert(0 && "not implemented");
    }

    return PY_STD_operator_apply(lhs, rhs, "__truediv__", "__rtruediv__");
}

PyObjectContainer* PY_STD_operator_floordiv(PyObjectContainer* lhs, PyObjectContainer* rhs)
{
    if (lhs->type == PY_TYPE_INT)
    {
        assert(rhs->type == PY_TYPE_INT);  // TODO: float
        assert(PY_unpackInteger(rhs) != 0);

        return PY_createInteger(PY_unpackInteger(lhs) / PY_unpackInteger(rhs));
    }

    return PY_STD_operator_apply(lhs, rhs, "__floordiv__", "__rfloordiv__");
}

PyObjectContainer* PY_STD_operator_modulo(PyObjectContainer* lhs, PyObjectContainer* rhs)
{
    if (lhs->type == PY_TYPE_INT)
    {
        assert(rhs->type == PY_TYPE_INT);  // TODO: float
        assert(PY_unpackInteger(rhs) != 0);

        return PY_createInteger(PY_unpackInteger(lhs) & PY_unpackInteger(rhs));
    }

    return PY_STD_operator_apply(lhs, rhs, "__mod__", "__rmod__");
}

