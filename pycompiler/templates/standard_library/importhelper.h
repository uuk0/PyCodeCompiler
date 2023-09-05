//
// Created by baulu on 05.09.2023.
//

#ifndef PYCCOMPILER_IMPORTHELPER_H
#define PYCCOMPILER_IMPORTHELPER_H

#include "pyinclude.h"

extern PyClassContainer* PY_TYPE_MODULE;

PyObjectContainer* PY_getModuleObject(char* name);
PyObjectContainer* PY_exposeModuleObject(PyObjectContainer* module);
PyObjectContainer* PY_createModuleObject(char* module_name);

void PY_STD_init_import_helper(void);

#endif //PYCCOMPILER_IMPORTHELPER_H
