#include <stdio.h>

#define T int
#include "deque.h"
#undef T

#define T int
#include "map.h"
#undef T

static void deque_demo(void) {
    deque(int) *q = NULL;
    deque_init_int(&q);

    if (!q) {
        printf("deque_init failed\n");
        return;
    }

    deque_push_back_int(q, 10);
    deque_push_back_int(q, 20);
    deque_push_back_int(q, 30);
    deque_push_front_int(q, 5);
    deque_push_front_int(q, 1);

    int v;

    printf("pop_front:");
    while (q->size) {
        deque_pop_front_int(q, &v);
        printf(" %d", v);
    }
    printf("\n");

    for (int i = 0; i < 4; i++)
        deque_push_back_int(q, i);

    printf("pop_back:");
    while (q->size) {
        deque_pop_back_int(q, &v);
        printf(" %d", v);
    }
    printf("\n");

    printf("size=%zu capacity=%zu\n", q->size, q->capacity);

    deque_free_int(&q);
    printf("freed=%p\n", (void *)q);
}

static void map_demo(void) {
    map(int) *m = NULL;
    map_init_int(&m);

    if (!m) {
        printf("map_init failed\n");
        return;
    }

    map_set_int(m, 1, 100);
    printf("put 1 -> 100");
    map_set_int(m, 2, 200);
    printf("put 2 -> 200");
    map_set_int(m, 3, 300);
    printf("put 3 -> 300");
    map_set_int(m, 2, 222);
    printf("put 2 -> 222");

    int v;

    if (map_get_int(m, 2, &v))
        printf("map[2] = %d\n", v);

    if (map_get_int(m, 99, &v))
        printf("map[99] = %d\n", v);
    else
        printf("map[99] missing\n");

    printf("size=%zu nbuckets=%zu\n", m->size, m->nbuckets);

    map_free_int(&m);
    printf("map freed=%p\n", (void *)m);
}

int main(void) {
    deque_demo();
    map_demo();
    return 0;
}
