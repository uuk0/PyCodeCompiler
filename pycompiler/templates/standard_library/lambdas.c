//
// Created by baulu on 03.10.2023.
//

#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include "lambdas.h"
#include "exceptions.h"

PyClassContainer* PY_TYPE_lambda;

PyObjectContainer** PY_CREATE_lambda_locals(uint8_t argc, ...) {
    PyObjectContainer** array = malloc(argc * sizeof(PyObjectContainer*));
    if (array == NULL) {
        perror("malloc lambda locals");
        exit(EXIT_FAILURE);
    }

    va_list ap;
    va_start(ap, argc);
    for(int i = 0; i < argc; i++){
        PyObjectContainer* value = va_arg(ap, PyObjectContainer*);
        array[i] = value;
    }
    va_end(ap);
    return array;
}

PyObjectContainer* PY_CREATE_lambda_WRAPPER(PyObjectContainer* call_fwd, PyObjectContainer** locals) {
    PyObjectContainer* obj = PY_createClassInstance(PY_TYPE_lambda);
    PY_setObjectAttributeByName(obj, "target", call_fwd);
    PyObjectContainer* local_object = createEmptyContainer(PY_TYPE_SPECIAL);
    local_object->raw_value = locals;
    PY_setObjectAttributeByName(obj, "locals", local_object);
    return obj;
}

PyObjectContainer* PY_STD_invoke_lambda(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info) {
    PY_THROW_EXCEPTION_IF(self == NULL, NULL);
    return PY_invokeBoxedMethod(PY_getObjectAttributeByName(self, "target"), self, argc, args, info);
}

PyObjectContainer* PY_STD_invoke_lambda_CONTAINER;

PyObjectContainer* PY_STD_lambda_helper_init(void) {
    PY_TYPE_lambda = PY_createClassContainer("<lambda>");
    PY_setClassAttributeByNameOrCreate(PY_TYPE_lambda, "__call__", PY_STD_invoke_lambda_CONTAINER = PY_createBoxForFunction(PY_STD_invoke_lambda));
    PY_ClassContainer_DeclareObjectAttribute(PY_TYPE_lambda, "target");
    PY_ClassContainer_DeclareObjectAttribute(PY_TYPE_lambda, "locals");
    return PY_NONE;
}
