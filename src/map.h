#ifdef T
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "type.h"
#include "templates.h"

#ifndef MAP_INITIAL_CAPACITY
#define MAP_INITIAL_CAPACITY 8
#endif
#ifndef MAP_LOAD_FACTOR_NUM
#define MAP_LOAD_FACTOR_NUM 3
#endif
#ifndef MAP_LOAD_FACTOR_DEN
#define MAP_LOAD_FACTOR_DEN 4
#endif

struct TEMPLATE(map_entry, T) {
    T key;
    T value;

    struct TEMPLATE(map_entry, T) *next;
};

struct TEMPLATE(map, T) {
    struct TEMPLATE(map_entry, T) **buckets;  
    usz nbuckets;
    usz size;            
};

static inline int TEMPLATE(map_eq, T)(T a, T b) {
    return memcmp(&a, &b, sizeof a) == 0;
}

static inline usz TEMPLATE(map_hash, T)(T key) {
    const unsigned char *bytes = (const unsigned char *)&key;

    uint64_t hash = UINT64_C(14695981039346656037);

    for (usz i = 0; i < sizeof(T); i++) {
        hash ^= bytes[i];
        hash *= UINT64_C(1099511628211);
    }

    return (usz)hash;
}

static inline void TEMPLATE(map_init, T) (
    struct TEMPLATE(map, T) **self
) {
    if(!self) return;

    struct TEMPLATE(map, T) *map = malloc(sizeof *map);
    if(!map) { *self = NULL; return; }

    map->nbuckets = MAP_INITIAL_CAPACITY;
    map->size = 0;

    map->buckets = calloc(
        map->nbuckets,
        sizeof(*map->buckets)
    );

    if(!map->buckets) { free(map); *self = NULL; return; }
    *self = map;
}

static inline 
struct TEMPLATE(map_entry, T) *
TEMPLATE(map_find_entry, T) (
    struct TEMPLATE(map, T) *map,
    T key
) {
    if(!map || !map->buckets) return NULL;

    usz index = TEMPLATE(map_hash, T)(key) % map->nbuckets;
    
    struct TEMPLATE(map_entry, T) *entry = map->buckets[index];

    while(entry) {
        if(TEMPLATE(map_eq, T)(entry->key, key)) {
            return entry;
        }
        entry = entry->next;
    }

    return NULL;
}

static inline void TEMPLATE(map_rehash, T) (
    struct TEMPLATE(map, T) *map,
    usz new_nbuckets
) {
    if(!map || !map->buckets) return;

    struct TEMPLATE(map_entry, T) **nbks =
        calloc(new_nbuckets, sizeof(*nbks));
    if(!nbks) return;

    for(usz i = 0; i < map->nbuckets; i++) {
        struct TEMPLATE(map_entry, T) *entry = map->buckets[i];

        while(entry) {
            struct TEMPLATE(map_entry, T) *next = 
                entry->next;
            usz index = 
                TEMPLATE(map_hash, T)(entry->key) % new_nbuckets;

            entry->next = nbks[index];
            nbks[index] = entry;
            entry = next;
        }
    }

    free(map->buckets);
    map->buckets = nbks;
    map->nbuckets = new_nbuckets;
}

static inline void TEMPLATE(map_set, T) (
    struct TEMPLATE(map, T) *map,
    T key,
    T value
) {
    if(!map || !map->buckets) return;

    struct TEMPLATE(map_entry, T) *entry =
        TEMPLATE(map_find_entry, T)(map, key);

    if(entry) { entry->value = value; return; }

    if( (map->size + 1) * MAP_LOAD_FACTOR_DEN > 
        (map->nbuckets * MAP_LOAD_FACTOR_NUM)
    ) {
        TEMPLATE(map_rehash, T)(map, map->nbuckets * 2);
    }

    entry = malloc(sizeof(*entry));
    if(!entry) return;

    entry->key = key;
    entry->value = value;

    usz index = TEMPLATE(map_hash, T)(key) % map->nbuckets;
    entry->next = map->buckets[index];
    map->buckets[index] = entry;

    map->size++;
}

static inline int TEMPLATE(map_get, T) (
    struct TEMPLATE(map, T) *map,
    T key,
    T *out
) {
    struct TEMPLATE(map_entry, T) *entry =
        TEMPLATE(map_find_entry, T)(map, key);

    if(!entry) return 0;

    if(out) *out = entry->value;
    return 1;
}

static inline void TEMPLATE(map_free, T) (
    struct TEMPLATE(map, T) **self
) {
    if(!self || !*self) return;

    struct TEMPLATE(map, T) *map = *self;

    for(usz i = 0; i < map->nbuckets; i++) {
        struct TEMPLATE(map_entry, T) *entry = map->buckets[i];

        while(entry) {
            struct TEMPLATE(map_entry, T) *next = entry->next;
            free(entry);
            entry = next;
        }
    }

    free(map->buckets);
    free(map);
    *self = NULL;
}

static inline void TEMPLATE(map_delete, T) (
    struct TEMPLATE(map, T) *map,
    T key
) {
    if(!map || !map->buckets || map->nbuckets == 0) return;

    usz index = TEMPLATE(map_hash, T)(key) % map->nbuckets;

    struct TEMPLATE(map_entry, T) **current = &map->buckets[index];

    while(*current) {
        struct TEMPLATE(map_entry, T) *entry = *current;

        if(TEMPLATE(map_eq, T)(entry->key, key)) {
            *current = entry->next;
            free(entry);
            map->size--;
            return;
        }
        current = &entry->next;
    }
}

#endif
