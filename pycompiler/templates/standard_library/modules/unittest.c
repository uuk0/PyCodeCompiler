//
// Created by baulu on 08.09.2023.
//

#include "unittest.h"
#include "pyinclude.h"
#include "standard_library/importhelper.h"

PyObjectContainer* PY_MODULE_INSTANCE_unittest;

PyObjectContainer* PY_MODULE_unittest_init(void)
{
    INVOKE_SINGLE();

    PY_MODULE_INSTANCE_unittest = PY_createModuleObject("unittest");

    PY_exposeModuleObject(PY_MODULE_INSTANCE_unittest);
}
