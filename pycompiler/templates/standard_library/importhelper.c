//
// Created by baulu on 05.09.2023.
//

#include <stdlib.h>
#include <assert.h>

#include "importhelper.h"
#include "helpers/hashmap.h"


PyClassContainer* PY_TYPE_MODULE;
HashMapContainer* KNOWN_MODULE_MAP;

PyObjectContainer* PY_getModuleObject(char* name)
{
    PyObjectContainer* module = HASHMAP_lookup(KNOWN_MODULE_MAP, name);
    return module;
}

PyObjectContainer* PY_exposeModuleObject(PyObjectContainer* module)
{
    assert(module->type == PY_TYPE_PY_IMPL);
    assert(module->py_type == PY_TYPE_MODULE);
    char* module_name = PY_unpackString(PY_getObjectAttributeByName(module, "__name__"));
    HASHMAP_insert(KNOWN_MODULE_MAP, module_name, module);
    return module;
}

PyObjectContainer* PY_createModuleObject(char* module_name)
{
    PyObjectContainer* module = PY_createClassInstance(PY_TYPE_MODULE);
    PY_setObjectAttributeByName(module, "__name__", PY_createString(module_name));
    return module;
}

void PY_STD_init_import_helper(void)
{
    PY_TYPE_MODULE = PY_createClassContainer("<module>");
    PY_TYPE_MODULE->flags |= PY_CLASS_ALLOW_DYNAMIC_ATTRIBUTES;  // allow dynamic attributes
    PY_ClassContainer_DeclareObjectAttribute(PY_TYPE_MODULE, "__name__");
    KNOWN_MODULE_MAP = HASHMAP_create(HASH_string, HASH_COMPARE_string);
}
