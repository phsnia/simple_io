/**
 * @file: deque.hpp
 *
 * Dynamic circular-buffer deque, stb-style template.
 *
 * Usage:
 *   #define i_TYPE i32
 *   #define i_KEY  i32
 *   #include "deque.hpp"
 *
 * This header intentionally has no include guard so it can be instantiated
 * multiple times in the same translation unit with different i_TYPE/i_KEY.
 */

#ifndef i_TYPE
    #error "i_TYPE must be defined"
#endif

#ifndef i_KEY
    #error "i_KEY must be defined"
#endif

#include <stdlib.h>

#define DQ_CAT2(a, b) a##b
#define DQ_CAT(a, b) DQ_CAT2(a, b)
#define DQ_VALUE DQ_CAT(i_TYPE, _value)
#define DQ_FUNC(name) DQ_CAT(i_TYPE, name)
#define DQ_DEF DQ_CAT(i_TYPE, _deque)

#ifndef DQ_INITIAL_CAPACITY
#define DQ_INITIAL_CAPACITY 8
#endif

typedef i_KEY DQ_VALUE;

typedef struct DQ_DEF {
    DQ_VALUE *arr;
    usz front;
    usz size;
    usz capacity;
} DQ_DEF;

static inline DQ_DEF DQ_FUNC(_init)(void) {
    DQ_DEF dq = {NULL, 0, 0, 0};
    return dq;
}

static inline void DQ_FUNC(_free)(DQ_DEF *self) {
    if (!self) return;

    free(self->arr);
    self->arr = NULL;
    self->front = 0;
    self->size = 0;
    self->capacity = 0;
}

static inline Bool DQ_FUNC(_expand)(DQ_DEF *self) {
    if (!self) return FALSE;

    usz new_cap = self->capacity == 0 ? DQ_INITIAL_CAPACITY : self->capacity * 2;

    if (new_cap < self->capacity) return FALSE;                 // overflow
    if (new_cap > SIZE_MAX / sizeof(DQ_VALUE)) return FALSE;    // overflow

    DQ_VALUE *new_arr = (DQ_VALUE *)malloc(new_cap * sizeof(DQ_VALUE));
    if (!new_arr) return FALSE;

    for (usz i = 0; i < self->size; ++i) {
        new_arr[i] = self->arr[(self->front + i) % self->capacity];
    }

    free(self->arr);
    self->arr = new_arr;
    self->front = 0;
    self->capacity = new_cap;

    return TRUE;
}

static inline void DQ_FUNC(_push_back)(DQ_DEF *self, DQ_VALUE value) {
    if (!self) return;

    if (self->size == self->capacity) {
        if(!DQ_FUNC(_expand)(self)) {
            return;
        }
    }

    usz rear = (self->front + self->size) % self->capacity;
    self->arr[rear] = value;
    self->size++;
}

static inline void DQ_FUNC(_push_front)(DQ_DEF *self, DQ_VALUE value) {
    if (!self) return;

    if (self->size == self->capacity) {
        if(!DQ_FUNC(_expand)(self)) {
            return;
        }
    }

    usz rear = (self->front - 1 + self->capacity) % self->capacity;
    self->arr[rear] = value;
    self->size++;
}

static inline void DQ_FUNC(_pop_front)(
    DQ_DEF *self,
    DQ_VALUE *out
) {
    if (!self || self->size == 0)
        return;

    if (out) *out = self->arr[self->front];

    self->front++;

    if (self->front == self->capacity)
        self->front = 0;

    self->size--;

    if (self->size == 0)
        self->front = 0;
}

static inline void DQ_FUNC(_pop_back)(
    DQ_DEF *self,
    DQ_VALUE *out
) {
    if (!self || self->size == 0)
        return;

    usz rear = self->front + self->size - 1;

    if (rear >= self->capacity)
        rear -= self->capacity;

    if (out) *out = self->arr[rear];

    self->size--;

    if (self->size == 0)
        self->front = 0;
}

#undef DQ_CAT2
#undef DQ_CAT
#undef DQ_VALUE
#undef DQ_FUNC
#undef DQ_DEF
#undef i_TYPE
#undef i_KEY
