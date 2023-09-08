//
// Created by baulu on 06.09.2023.
//
#include "exceptions.h"

PyClassContainer* PY_TYPE_EXCEPTION;

PyObjectContainer* PY_STD_createException(char* exc_name, char* message)
{
    PyObjectContainer* obj = PY_createClassInstance(PY_TYPE_EXCEPTION);
    PY_setObjectAttributeByName(obj, "class", PY_createString(exc_name));
    PY_setObjectAttributeByName(obj, "message", PY_createString(message));
    return PY_STD_wrapException(obj);
}

PyObjectContainer* PY_STD_wrapException(PyObjectContainer* exception)
{
    PyObjectContainer* container = createEmptyContainer(PY_EXCEPTION);
    container->raw_value = exception;
    return container;
}

void PY_STD_initExceptionType(void)
{
    PY_TYPE_EXCEPTION = PY_createClassContainer("Exception");
    PY_ClassContainer_DeclareObjectAttribute(PY_TYPE_EXCEPTION, "class");
    PY_ClassContainer_DeclareObjectAttribute(PY_TYPE_EXCEPTION, "message");
}
