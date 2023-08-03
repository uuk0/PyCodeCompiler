//
// Created by baulu on 03.08.2023.
//

#include <stdbool.h>
#include "init.h"
#include "list.h"


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
}
