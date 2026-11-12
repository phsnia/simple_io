#include "deque.hpp"

/**
 * @file: memory.cc
 */

/**
 * Allocate memory for an array.
 *
 * @param count Number of elements.
 * @param element_size Size of each element.
 * @return Pointer to allocated memory, or NULL on failure.
 */
static inline void mmalloc(
    usz count, 
    usz esz
) {
    if(esz != 0 && count > SIZE_MAX / esz) 
        return NULL;

    return malloc(count * esz);
}

/**
 * @param ptr Existing memory pointer
 */
static inline void *mmrealloc(
    void *ptr, 
    usz count, 
    usz esz
) {
    if (esz != 0 && count > SIZE_MAX / esz) 
        return NULL;

    return realloc(ptr, count * esz);
}