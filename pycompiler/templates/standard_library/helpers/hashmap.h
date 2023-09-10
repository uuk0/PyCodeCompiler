//
// Created by baulu on 05.09.2023.
//

#ifndef PYCCOMPILER_HASHMAP_H
#define PYCCOMPILER_HASHMAP_H

#include <stdint.h>
#include <stdbool.h>

extern bool HASHMAP_MARKER_UNSET;

typedef int64_t HASH_METHOD(void* obj);
typedef bool HASH_COMPARE_ELEMENT(void* lhs, void* rhs);

struct HashMapContainer
{
    uint64_t alloc_size;
    uint64_t used_size;
    void** key_memory;
    void** value_memory;
    HASH_METHOD* hash_method;
    HASH_COMPARE_ELEMENT* compare_keys;
};
typedef struct HashMapContainer HashMapContainer;

HashMapContainer* HASHMAP_create(HASH_METHOD* hash_method, HASH_COMPARE_ELEMENT* compare_keys);
HashMapContainer* HASHMAP_create_with_size(HASH_METHOD* hash_method, HASH_COMPARE_ELEMENT* compare_keys, uint64_t initial_size);

void HASHMAP_resize(HashMapContainer* container, uint64_t size);

void HASHMAP_insert(HashMapContainer* container, void* key, void* value);
void* HASHMAP_lookup(HashMapContainer* container, void* key);
bool HASHMAP_has_key(HashMapContainer* container, void* key);
void* HASHMAP_remove(HashMapContainer* container, void* key);
void HASHMAP_clear(HashMapContainer* container);

int64_t HASH_string(void* string);
bool HASH_COMPARE_string(void* lhs, void* rhs);

#endif //PYCCOMPILER_HASHMAP_H
