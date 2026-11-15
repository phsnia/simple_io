/**
 * @file: deque.h
 *
 * Heap-allocated circular-buffer deque template.
 *
 * Usage:
 *   #define T int
 *   #include "deque.h"
 *   #undef T
 *
 *   deque(int) *q = NULL;
 *   deque_init_int(&q);
 *   deque_push_back_int(q, 42);
 *   deque_free_int(&q);
 *
 * No include guard: instantiate once per type.
 */

#ifdef T
#include <stdlib.h>
#include "type.h"
#include "templates.h"
#include "memory.h"

#ifndef DEQUE_INITIAL_CAPACITY
#define DEQUE_INITIAL_CAPACITY 8
#endif

typedef struct TEMPLATE(deque, T) {
    T   *data;
    usz  front;
    usz  size;
    usz  capacity;
} TEMPLATE(deque, T);

static inline void TEMPLATE(deque_init, T)(TEMPLATE(deque, T) **self) {
    if (!self) return;

    TEMPLATE(deque, T) *dq = mmalloc(1, sizeof *dq);
    if (!dq) {
        *self = NULL;
        return;
    }

    dq->data = NULL;
    dq->front = 0;
    dq->size = 0;
    dq->capacity = 0;
    *self = dq;
}

static inline void TEMPLATE(deque_free, T)(
    TEMPLATE(deque, T) **self
) {
    if (!self || !*self) return;

    free((*self)->data);
    free(*self);
    *self = NULL;
}

static inline Bool TEMPLATE(deque_expand, T)(
    TEMPLATE(deque, T) *self
) {
    if (!self) return FALSE;

    usz new_cap = self->capacity == 0 ? DEQUE_INITIAL_CAPACITY : self->capacity * 2;

    if (new_cap < self->capacity) return FALSE;              // overflow

    T *new_data = mmalloc(new_cap, sizeof(T));
    if (!new_data) return FALSE;

    for (usz i = 0; i < self->size; ++i) {
        new_data[i] = self->data[(self->front + i) % self->capacity];
    }

    free(self->data);
    self->data = new_data;
    self->front = 0;
    self->capacity = new_cap;

    return TRUE;
}

static inline void TEMPLATE(deque_push_back, T)(
    TEMPLATE(deque, T) *self,
    T value
) {
    if (!self) return;

    if (self->size == self->capacity) {
        if (!TEMPLATE(deque_expand, T)(self)) return;
    }

    usz rear = (self->front + self->size) % self->capacity;
    self->data[rear] = value;
    self->size++;
}

static inline void TEMPLATE(deque_pop_back, T)(
    TEMPLATE(deque, T) *self,
    T *out
) {
    if (!self || self->size == 0) return;

    usz rear = (self->front + self->size - 1) % self->capacity;

    if (out) *out = self->data[rear];

    self->size--;

    if (self->size == 0) self->front = 0;
}

static inline void TEMPLATE(deque_push_front, T)(
    TEMPLATE(deque, T) *self,
    T value
) {
    if (!self) return;

    if (self->size == self->capacity) {
        if (!TEMPLATE(deque_expand, T)(self)) return;
    }

    self->front = (self->front - 1 + self->capacity) % self->capacity;
    self->data[self->front] = value;
    self->size++;
}

static inline void TEMPLATE(deque_pop_front, T)(
    TEMPLATE(deque, T) *self,
    T *out
) {
    if (!self || self->size == 0) return;

    if (out) *out = self->data[self->front];

    self->front = (self->front + 1) % self->capacity;
    self->size--;

    if (self->size == 0) self->front = 0;
}

#endif
