//
// Created by baulu on 17.11.2023.
//

#include <stdlib.h>
#include <stdio.h>
#include "pyinclude.h"

PyObject* PY_STD_create_malloced_object(PyClass* cls)
{
    PyObject* obj = malloc(sizeof(PyObject));

    if (obj == NULL)
    {
        perror("malloc");
        abort();
    }

    obj->py_class = cls;
    obj->flags = 0;
    obj->attribute_table = NULL;
    obj->ref_counter = 1;
    return obj;
}

PyObject* PY_STD_create_stacked_object(PyClass* cls, PyObject* obj)
{
    if (obj == NULL)
    {
        fprintf(stderr, "stack reference is NULL");
        abort();
    }

    obj->py_class = cls;
    obj->flags = 0;
    obj->attribute_table = NULL;
    obj->ref_counter = 1;
    return obj;
}
