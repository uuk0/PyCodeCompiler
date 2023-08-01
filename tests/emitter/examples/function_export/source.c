#include "pyinclude.h"

// code compiled from python to c via PyCodeCompiler

int _initialise(int argc , char* argv[]);
PyObjectContainer* test();


// implementations

int _initialise(int argc , char* argv[]){
}

PyObjectContainer* test(){
    return PY_createInteger(10);
}

