/**
 * @file: memory.h
 *
 * Overflow-checked allocation helpers.
 */
#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include "type.h"

/**
 * Allocate memory for an array.
 *
 * @param count Number of elements.
 * @param esz   Size of each element in bytes.
 * @return Pointer to allocated memory, or NULL on overflow or failure.
 */
static inline void *mmalloc(
    usz count,
    usz esz
) {
    if(esz != 0 && count > SIZE_MAX / esz) return NULL;

    return malloc(count * esz);
}

/**
 * Resize an array allocation.
 *
 * @param ptr   Existing allocation, or NULL.
 * @param count Number of elements.
 * @param esz   Size of each element in bytes.
 * @return Pointer to the resized memory, or NULL on overflow or failure.
 */
static inline void *mmrealloc(
    void *ptr,
    usz count,
    usz esz
) {
    if(esz != 0 && count > SIZE_MAX / esz) return NULL;

    return realloc(ptr, count * esz);
}

/**
 * Allocate and zero an array.
 *
 * @param count Number of elements.
 * @param esz   Size of each element in bytes.
 * @return Pointer to zeroed memory, or NULL on overflow or failure.
 */
static inline void *mmcalloc(
    usz count,
    usz esz
) {
    if(esz != 0 && count > SIZE_MAX / esz) return NULL;

    return calloc(count, esz);
}

#endif
