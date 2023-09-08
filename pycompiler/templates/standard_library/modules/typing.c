//
// Created by baulu on 08.09.2023.
//

#include "typing.h"
#include "pyinclude.h"
#include "standard_library/importhelper.h"

PyObjectContainer* PY_MODULE_INSTANCE_typing;

void PY_STD_initModuleTyping(void)
{
    PY_MODULE_INSTANCE_typing = PY_createModuleObject("typing");
    PY_setObjectAttributeByName(PY_MODULE_INSTANCE_typing, "TYPE_CHECKING", PY_FALSE);

    PY_exposeModuleObject(PY_MODULE_INSTANCE_typing);
}
