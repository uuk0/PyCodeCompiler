//
// Created by baulu on 28.09.2023.
//

#ifndef PYCCOMPILER_PARAMETERS_H
#define PYCCOMPILER_PARAMETERS_H

#include <stdint.h>

struct PyObjectContainer;
struct PyClassContainer;

#define CALL_STRUCTURE_NORMAL 0    // the item at the given index is a normal arg; only allowed before the first CALL_STRUCTURE_KEYWORD and CALL_STRUCTURE_STAR_STAR
#define CALL_STRUCTURE_STAR 1      // a parameter references with *x
#define CALL_STRUCTURE_KEYWORD 2   // a keyword
#define CALL_STRUCTURE_STAR_STAR 3 // a keyword unpack

struct CallStructureInfo
{
    uint8_t offset;
    uint8_t count;
    uint64_t bitmask[8];   // possible 255 args, each 2 bit -> 512 bit -> 8
    char** keyword_names;  // only valid when one CALL_STRUCTURE_KEYWORD is provided
};
typedef struct CallStructureInfo CallStructureInfo;

struct PyObjectContainer** PY_ARGS_unpackPositionalArgs(struct PyObjectContainer** args, CallStructureInfo* info, uint8_t* count_ref);
struct PyObjectContainer* PY_ARGS_getKeywordParameter(struct PyObjectContainer** args, CallStructureInfo* info, char* name);
struct PyObjectContainer* PY_ARGS_getKeywordParameterOrDefault(struct PyObjectContainer** args, CallStructureInfo* info, char* name, struct PyObjectContainer* default_value);
struct PyObjectContainer** PY_ARGS_unpackArgTableForUnsafeCall(uint8_t positional_count, struct PyObjectContainer** args, CallStructureInfo* info, uint8_t* count_ref, uint8_t keyword_count, char** keywords, struct PyObjectContainer** defaults);

#endif //PYCCOMPILER_PARAMETERS_H
