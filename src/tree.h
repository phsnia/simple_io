#ifdef T
#include <stdlib.h>
#include <string.h>
#include "templates.h"
#include "memory.h"

struct TEMPLATE(TNode, T) {
    T data;
    struct TEMPLATE(TNode, T)* left;
    struct TEMPLATE(TNode, T)* right;
};

static inline void TEMPLATE(tnode_init, T) (
    struct TEMPLATE(TNode, T) **self,
    T data
) {
    if(!self) return;

    struct TEMPLATE(TNode, T)* nn = mmalloc(1, sizeof(*nn));
    if(!nn) { *self = NULL; return; }

    nn->data = data;
    nn->left = NULL;
    nn->right = NULL;
    *self = nn;
}

static inline void TEMPLATE(tnode_insert, T) (
    struct TEMPLATE(TNode, T) *self,
    T data,
    const char *direction
) {
    if(!self || !direction) return;

    int left  = strcmp(direction, "LEFT")  == 0 || strcmp(direction, "L") == 0;
    int right = strcmp(direction, "RIGHT") == 0 || strcmp(direction, "R") == 0;

    if(!left && !right) return;

    struct TEMPLATE(TNode, T) **slot = left ? &self->left : &self->right;
    if(*slot) return;

    struct TEMPLATE(TNode, T)* nn = mmalloc(1, sizeof(*nn));
    if(!nn) return;

    nn->data = data;
    nn->left = NULL;
    nn->right = NULL;
    *slot = nn;
}

static inline void TEMPLATE(tnode_in_order, T) (
    struct TEMPLATE(TNode, T) *node,
    void (*consumer)(T)
) {
    if(!node || !consumer) return;

    TEMPLATE(tnode_in_order, T)(node->left, consumer);
    consumer(node->data);
    TEMPLATE(tnode_in_order, T)(node->right, consumer);
}

static inline void TEMPLATE(tnode_free, T) (
    struct TEMPLATE(TNode, T) **self
) {
    if(!self || !*self) return;

    struct TEMPLATE(TNode, T)* nn = *self;

    TEMPLATE(tnode_free, T)(&nn->left);
    TEMPLATE(tnode_free, T)(&nn->right);

    free(nn);
    *self = NULL;
}

#endif
