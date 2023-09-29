//
// Created by baulu on 28.09.2023.
//

#include <memory.h>
#include <assert.h>
#include <string.h>
#include "parameters.h"
#include "pyinclude.h"
#include "list.h"
#include "dict.h"
#include "standard_library/helpers/hashmap.h"

CallStructureInfo* PY_ARGS_createCallInfo(uint8_t offset, uint8_t count, uint64_t bitmask[8], char** keyword_names)
{
    CallStructureInfo* mem = malloc(sizeof(CallStructureInfo));
    mem->offset = offset;
    mem->count = count;
    memcpy(mem->bitmask, bitmask, 8 * sizeof(uint64_t));
    mem->keyword_names = keyword_names;
    return mem;
}

PyObjectContainer** PY_ARGS_unpackPositionalArgs(PyObjectContainer** args, CallStructureInfo* info, uint8_t* count_ref) {
    if (info == NULL) {
        return args;
    }

    PyObjectContainer** new_args = NULL;
    if (info->offset != 0) {  // are the starting args to be copied?
        // todo: who frees this data?
        new_args = malloc(sizeof(PyObjectContainer*) * info->offset);
        memcpy(new_args, args, sizeof(PyObjectContainer*) * info->offset);
        *count_ref = info->offset;
    }
    else {
        *count_ref = 0;
    }

    int j = 0;
    uint8_t table_index = 0;
    uint64_t bitmask = CALL_STRUCTURE_KEYWORD;
    uint64_t flag = info->bitmask[0];

    for (int i = 0; i < info->count; i++) {
        if (flag & bitmask) {  // is it a keyword?
            break;
        }

        // Is it to be unpacked
        if (flag & (bitmask >> 1)) {
            PyObjectContainer* list = PY_createClassInstance(PY_TYPE_LIST);
            PY_STD_list_init_fast_arg_1(list, args[info->offset + i]);
            assert(list->raw_value != NULL && "this should not be able to happen!");
            PY_STD_list_container* list_container = list->raw_value;
            new_args = realloc(new_args, ((*count_ref) + list_container->curr_size) * sizeof(PyObjectContainer*));
            memcpy(new_args + *count_ref, list_container->array, list_container->curr_size * sizeof(PyObjectContainer*));
            *count_ref += list_container->curr_size;
            DECREF(list);
        }
        else {
            new_args = realloc(new_args, ((*count_ref) + 1) * sizeof(PyObjectContainer*));
            new_args[*count_ref] = args[info->offset + i];
            (*count_ref)++;
        }

        j++;
        bitmask <<= 2;
        if (j == 32) {
            j = 0;
            table_index++;
            flag = info->bitmask[table_index];
            bitmask = 0b10;
        }
    }

    return new_args;
}

PyObjectContainer* PY_ARGS_getKeywordParameter(PyObjectContainer** args, CallStructureInfo* info, char* name) {
    if (info == NULL) {
        return NULL;
    }

    int j = 0;
    uint8_t table_index = 0;
    uint64_t bitmask = CALL_STRUCTURE_KEYWORD;
    uint64_t flag = info->bitmask[0];

    for (int i = 0; i < info->count; i++) {
        if (!(flag & bitmask)) continue;

        if (flag & (bitmask >> 1)) {
            PyObjectContainer* dict = args[info->offset + i];
            assert(dict->type == PY_TYPE_PY_IMPL && dict->py_type == PY_TYPE_DICT);
            HashMapContainer* map = dict->raw_value;
            if (HASHMAP_has_key(map, name)) {
                return HASHMAP_lookup(map, name);
            }
        }
        else {
            if (strcmp(info->keyword_names[i], name) == 0) {
                return args[info->offset + i];
            }
        }

        j++;
        bitmask <<= 2;
        if (j == 32) {
            j = 0;
            table_index++;
            flag = info->bitmask[table_index];
            bitmask = 0b10;
        }
    }

    return NULL;
}

PyObjectContainer* PY_ARGS_getKeywordParameterOrDefault(PyObjectContainer** args, CallStructureInfo* info, char* name, PyObjectContainer* default_value) {
    PyObjectContainer* value = PY_ARGS_getKeywordParameter(args, info, name);
    return value == NULL ? default_value : value;
}

PyObjectContainer** PY_ARGS_unpackArgTableForUnsafeCall(uint8_t positional_count, PyObjectContainer** args, CallStructureInfo* info, uint8_t* count_ref, uint8_t keyword_count, char** keywords, PyObjectContainer** defaults) {
    PyObjectContainer** new_args = malloc((positional_count + keyword_count) * sizeof(PyObjectContainer*));
    memcpy(new_args, args, *count_ref * sizeof(PyObjectContainer*));
    uint8_t rem = keyword_count;
    if (*count_ref > positional_count) rem -= *count_ref - positional_count;

    if (info == NULL) {
        memcpy(new_args + *count_ref, defaults + (keyword_count - rem), rem * sizeof(PyObjectContainer*));
        return new_args;
    }

    for (int i = (keyword_count - rem); i < rem; i++) {
        char* key = keywords[i];
        PyObjectContainer* value = PY_ARGS_getKeywordParameterOrDefault(args, info, key, defaults[i]);
        new_args[positional_count + keyword_count - rem + i] = value;
    }

    return new_args;
}
