//
// Created by baulu on 05.09.2023.
//

#ifndef PYCCOMPILER_EXCEPTIONS_H
#define PYCCOMPILER_EXCEPTIONS_H

#include "pyinclude.h"
#include <stdio.h>
#include "config.h"
#include <assert.h>

extern PyClassContainer* PY_TYPE_EXCEPTION;

PyObjectContainer* PY_STD_createException(char* exc_name, char* message);
PyObjectContainer* PY_STD_wrapException(PyObjectContainer* exception);


#ifndef PY_INTERNAL_THROW_EXCEPTIONS_INPLACE

#define PY_THROW_EXCEPTION(exception) return PY_STD_wrapException(exception)
#define PY_THROW_EXCEPTION_IF(condition, exception) if (condition) { return PY_STD_wrapException(exception); }

#define PY_THROW_EXCEPTION_WITH_MESSAGE(exception, message) { printf("%s\n", message); return PY_STD_wrapException(exception); }
#define PY_THROW_EXCEPTION_IF_WITH_MESSAGE(condition, exception, message) if (condition) { printf("%s\n", message); return PY_STD_wrapException(exception); }

#else

#define PY_THROW_EXCEPTION(exception) assert(false);
#define PY_THROW_EXCEPTION_IF(condition, exception) assert(!(condition));

#define PY_THROW_EXCEPTION_WITH_MESSAGE(exception, message) { printf("%s\n", message); assert(false); }
#define PY_THROW_EXCEPTION_IF_WITH_MESSAGE(condition, exception, message) if (condition) { printf("%s\n", message); assert(false); }

#define PY_THROW_EXCEPTION_IF_WITH_MESSAGE_AND_OBJ(condition, exception, message, obj) if (condition) { printf(message, PY_getObjectRepr(obj)); assert(false); }

#endif

#define PY_CHECK_EXCEPTION(value) ( { PyObjectContainer* x = value; if (x != NULL && x->type == PY_EXCEPTION) { return x; }; x; })
#define PY_CHECK_EXCEPTION_WITH_MESSAGE(value, message) ( { PyObjectContainer* x = value; if (x != NULL && x->type == PY_EXCEPTION) { printf("%s\n", message); return x; }; x; })

#define PY_CHECK_EXCEPTION_AND_EXIT(value) ({ PyObjectContainer* x = value;  if (x != NULL && x->type == PY_EXCEPTION) { assert(0 && "exception raised"); }; x; })
#define PY_CHECK_EXCEPTION_AND_EXIT_WITH_MESSAGE(value, message) ({ PyObjectContainer* x = value; if (x != NULL && x->type == PY_EXCEPTION) { printf("%s\n", message); assert(0 && "exception raised"); }; x; })

void PY_STD_initExceptionType(void);

#endif //PYCCOMPILER_EXCEPTIONS_H
