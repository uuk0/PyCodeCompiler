//
// Created by baulu on 08.09.2023.
//

#include <assert.h>
#include "typing.h"
#include "pyinclude.h"
#include "standard_library/importhelper.h"

PyObjectContainer* PY_MODULE_INSTANCE_typing;
PyClassContainer* PY_MODULE_typing_Generic;
PyClassContainer* PY_MODULE_typing_TypeVar;

PyObjectContainer* PY_MODULE_typing_Generic_class_getitem(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info) {
    PyClassContainer* cls = PY_createClassContainer("Generic:custom");
    PY_ClassContainer_AllocateParentArray(cls, 1);
    cls->parents[0] = PY_MODULE_typing_Generic;
    return PY_createClassWrapper(cls);
}

PyObjectContainer* PY_MODULE_typing_TypeVar_init(PyObjectContainer* self, uint8_t argc, PyObjectContainer** args, CallStructureInfo* info) {
    assert(argc == 1);
    return PY_MODULE_typing_TypeVar_init_arg_1(self, args[0]);
}

PyObjectContainer* PY_MODULE_typing_TypeVar_init_arg_1(PyObjectContainer* self, PyObjectContainer* name) {
    return PY_NONE;
}

PyObjectContainer* PY_MODULE_typing_init(void)
{
    INVOKE_SINGLE();

    PY_MODULE_INSTANCE_typing = PY_createModuleObject("typing");
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_typing, "TYPE_CHECKING", PY_FALSE);

    PY_MODULE_typing_Generic = PY_createClassContainer("Generic");
    PY_ClassContainer_AllocateParentArray(PY_MODULE_typing_Generic, 1);
    PY_MODULE_typing_Generic->parents[0] = PY_TYPE_OBJECT;
    PY_setClassAttributeByNameOrCreate(PY_MODULE_typing_Generic, "__class_getitem__", PY_createBoxForFunction(PY_MODULE_typing_Generic_class_getitem));
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_typing, "Generic", PY_createClassWrapper(PY_MODULE_typing_Generic));

    PY_MODULE_typing_TypeVar = PY_createClassContainer("TypeVar");
    PY_ClassContainer_AllocateParentArray(PY_MODULE_typing_TypeVar, 1);
    PY_MODULE_typing_TypeVar->parents[0] = PY_TYPE_OBJECT;
    PY_setClassAttributeByNameOrCreate(PY_MODULE_typing_TypeVar, "__init__", PY_createBoxForFunction(PY_MODULE_typing_TypeVar_init));
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_typing, "TypeVar", PY_createClassWrapper(PY_MODULE_typing_TypeVar));

    PY_exposeModuleObject(PY_MODULE_INSTANCE_typing);

    return PY_NONE;
}
