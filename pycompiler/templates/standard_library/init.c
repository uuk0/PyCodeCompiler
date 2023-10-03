//
// Created by baulu on 03.08.2023.
//

#include <stdbool.h>
#include "init.h"
#include "list.h"
#include "operators.h"
#include "exceptions.h"
#include "generator.h"
#include "config.h"


static bool STD_IS_INITIALISED = false;

void PY_STD_INIT()
{
    if (STD_IS_INITIALISED)
    {
        return;
    }

    STD_IS_INITIALISED = true;

    initialize();

    PY_STD_initIntType();

    PY_STD_initListType();
    PY_STD_initTupleType();
    PY_STD_initDictType();
    PY_STD_initStringType();
    PY_STD_initExceptionType();
    PY_CHECK_EXCEPTION_AND_EXIT(PY_STD_lambda_helper_init());

#ifdef PY_ENABLE_GENERATORS
    PY_STD_initGeneratorType();
#endif

#ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
    PY_STD_init_import_helper();
#endif
}
