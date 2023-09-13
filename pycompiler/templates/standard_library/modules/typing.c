//
// Created by baulu on 08.09.2023.
//

#include "typing.h"
#include "pyinclude.h"
#include "standard_library/importhelper.h"

PyObjectContainer* PY_MODULE_INSTANCE_typing;

PyObjectContainer* PY_MODULE_typing_init(void)
{
    INVOKE_SINGLE();

    PY_MODULE_INSTANCE_typing = PY_createModuleObject("typing");
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_typing, "TYPE_CHECKING", PY_FALSE);

    PY_exposeModuleObject(PY_MODULE_INSTANCE_typing);

    return PY_NONE;
}
