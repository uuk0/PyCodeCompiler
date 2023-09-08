//
// Created by baulu on 08.09.2023.
//

#include "typing.h"
#include "pyinclude.h"
#include "standard_library/importhelper.h"

void PY_STD_initModuleTyping(void)
{
    PyObjectContainer* module = PY_createModuleObject("typing");
    PY_setObjectAttributeByName(module, "TYPE_CHECKING", PY_FALSE);

    PY_exposeModuleObject(module);
}
