//
// Created by baulu on 05.09.2023.
//

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "hashmap.h"


bool HASHMAP_MARKER_UNSET = false;


HashMapContainer* HASHMAP_create(HASH_METHOD* hash_method, HASH_COMPARE_ELEMENT* compare_keys)
{
    return HASHMAP_create_with_size(hash_method, compare_keys, 8);
}

HashMapContainer* HASHMAP_create_with_size(HASH_METHOD* hash_method, HASH_COMPARE_ELEMENT* compare_keys, uint64_t initial_size)
{
    HashMapContainer* container = malloc(sizeof(HashMapContainer));
    assert(container != NULL);
    container->hash_method = hash_method;
    container->compare_keys = compare_keys;
    container->alloc_size = initial_size;
    container->used_size = 0;
    container->key_memory = calloc(initial_size, sizeof(void*));
    container->value_memory = calloc(initial_size, sizeof(void*));

    return container;
}

void HASHMAP_resize(HashMapContainer* container, uint64_t size)
{
    assert(size >= container->used_size);
    uint64_t old_size = container->alloc_size;

    void** old_keys = container->key_memory;
    void** old_values = container->value_memory;

    container->alloc_size = size;
    container->used_size = 0;
    container->key_memory = calloc(size, sizeof(void*));
    container->value_memory = calloc(size, sizeof(void*));

    for (int i = 0; i < old_size; i++)
    {
        HASHMAP_insert(container, old_keys[i], old_values[i]);
    }
}

uint64_t HASHMAP_generateNewKey(uint64_t old_key, uint64_t size)
{
    return (old_key + 1) % size;
}

void HASHMAP_insert(HashMapContainer* container, void* key, void* value)
{
    int64_t hash = container->hash_method(key);

    start:;
    uint64_t partial_hash = hash % container->alloc_size;
    void* current_key = container->key_memory[partial_hash];

    if (current_key == NULL || current_key == &HASHMAP_MARKER_UNSET)
    {
        container->key_memory[partial_hash] = key;
        container->value_memory[partial_hash] = value;
        container->used_size++;
        return;
    }

    if (container->compare_keys(current_key, key))
    {
        container->value_memory[partial_hash] = value;
        return;
    }

    if (container->alloc_size == container->used_size)
    {
        HASHMAP_resize(container, container->alloc_size * 2);

        // resized the container, so now there is enough space
        // hash is still the same, so we don't need to recalculate it here
        goto start;
    }

    while (1)
    {
        partial_hash = HASHMAP_generateNewKey(partial_hash, container->alloc_size);
        current_key = container->key_memory[partial_hash];

        // is this entry empty?
        if (current_key == NULL || current_key == &HASHMAP_MARKER_UNSET)
        {
            container->key_memory[partial_hash] = key;
            container->value_memory[partial_hash] = value;
            container->used_size++;
            return;
        }

        if (container->compare_keys(current_key, key))
        {
            container->value_memory[partial_hash] = value;
            return;
        }
    }
}

void* HASHMAP_lookup(HashMapContainer* container, void* key)
{
    int64_t hash = container->hash_method(key);
    uint64_t partial_hash = hash % container->alloc_size;
    uint64_t original_hash = partial_hash;
    void* current_key;

    while (1)
    {
        current_key = container->key_memory[partial_hash];

        if (current_key == NULL)
        {
            return NULL;
        }

        if (current_key == &HASHMAP_MARKER_UNSET)
        {
            continue;
        }

        if (container->compare_keys(current_key, key))
        {
            return container->value_memory[partial_hash];
        }

        partial_hash = HASHMAP_generateNewKey(partial_hash, container->alloc_size);

        if (partial_hash == original_hash)
        {
            return NULL;
        }
    }
}

bool HASHMAP_has_key(HashMapContainer* container, void* key)
{
    int64_t hash = container->hash_method(key);
    uint64_t partial_hash = hash % container->alloc_size;
    uint64_t original_hash = partial_hash;
    void* current_key;

    while (1)
    {
        current_key = container->key_memory[partial_hash];

        if (current_key == NULL)
        {
            return false;
        }

        if (current_key == &HASHMAP_MARKER_UNSET)
        {
            continue;
        }

        if (container->compare_keys(current_key, key))
        {
            return true;
        }

        partial_hash = HASHMAP_generateNewKey(partial_hash, container->alloc_size);

        if (partial_hash == original_hash)
        {
            return false;
        }
    }
}

void* HASHMAP_remove(HashMapContainer* container, void* key)
{
    int64_t hash = container->hash_method(key);
    uint64_t partial_hash = hash % container->alloc_size;
    uint64_t original_hash = partial_hash;
    void* current_key;

    while (1)
    {
        current_key = container->key_memory[partial_hash];

        if (current_key == NULL)
        {
            return NULL;
        }

        if (current_key == &HASHMAP_MARKER_UNSET)
        {
            continue;
        }

        if (container->compare_keys(current_key, key))
        {
            container->key_memory[partial_hash] = &HASHMAP_MARKER_UNSET;
            void* value = container->value_memory[partial_hash];
            container->value_memory[partial_hash] = NULL;
            return value;
        }

        partial_hash = HASHMAP_generateNewKey(partial_hash, container->alloc_size);

        if (partial_hash == original_hash)
        {
            return NULL;
        }
    }
}

void HASHMAP_clear(HashMapContainer* container)
{
    container->alloc_size = 8;
    container->used_size = 0;
    free(container->key_memory);
    free(container->value_memory);
    container->key_memory = calloc(container->alloc_size, sizeof(void*));
    container->value_memory = calloc(container->alloc_size, sizeof(void*));
}

int64_t HASH_string(void* raw_string)
{
    int64_t hash = -(int64_t)0xbaadf00dbaadf00d;
    char* string = raw_string;

    int i = 0;
    while (string[i] != '\0')
    {
        hash += string[i];
        i++;
    }
    return hash;
}

bool HASH_COMPARE_string(void* lhs, void* rhs)
{
    if (strcmp(lhs, rhs) == 0)
    {
        return true;
    }
    return false;
}

