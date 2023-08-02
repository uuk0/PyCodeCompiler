#include <assert.h>
#include <string.h>
#include "pyinclude.h"


int _initialise();
extern PyClassContainer* PY_CLASS_test_0;


int main()
{
    _initialise();
    assert(PY_CLASS_test_0 != NULL);
    assert(strcmp(PY_CLASS_test_0->class_name, "test") == 0);
}

