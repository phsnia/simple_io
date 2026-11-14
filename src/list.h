#ifdef T
#include <stdlib.h>
#include "templates.h"

struct TEMPLATE(node, T) {
    T value;
    struct TEMPLATE(node, T) *next;
};

static inline void TEMPLATE(node_push, T)(struct TEMPLATE(node, T) **head, T value) {
    struct TEMPLATE(node, T) *n = malloc(sizeof *n);
    if (!n)
        return;

    n->value = value;
    n->next  = *head;
    *head    = n;
}

static inline void TEMPLATE(node_free, T)(struct TEMPLATE(node, T) **head) {
    struct TEMPLATE(node, T) *p = *head;

    while (p) {
        struct TEMPLATE(node, T) *next = p->next;
        free(p);
        p = next;
    }

    *head = NULL;
}

#endif
