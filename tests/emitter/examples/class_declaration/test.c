#include <assert.h>
#include <string.h>
#include "pyinclude.h"
#include "source.h"


int main()
{
    PY_MODULE_source_init();
    assert(PY_CLASS_test_2 != NULL);
    assert(strcmp(PY_CLASS_test_2->class_name, "test") == 0);
}

