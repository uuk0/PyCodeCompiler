#include <assert.h>
#include "pyinclude.h"


int _initialise();
extern PyClassContainer* PY_CLASS_test;


int main()
{
    _initialise();
    assert(PY_CLASS_test != NULL);
    assert(strcmp(PY_CLASS_test->class_name, "test") == 0);
}

