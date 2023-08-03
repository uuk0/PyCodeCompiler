#include <assert.h>
#include <string.h>
#include "pyinclude.h"


int _initialise();
extern PyClassContainer* PY_CLASS_test_2;


int main()
{
    _initialise();
    assert(PY_CLASS_test_2 != NULL);
    assert(strcmp(PY_CLASS_test_2->class_name, "test") == 0);
}

