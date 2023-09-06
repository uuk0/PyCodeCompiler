//
// Created by baulu on 06.09.2023.
//
#include "exceptions.h"

PyObjectContainer* PY_STD_wrapException(PyObjectContainer* exception)
{
    PyObjectContainer* container = createEmptyContainer(PY_EXCEPTION);
    container->raw_value = exception;
    return container;
}
