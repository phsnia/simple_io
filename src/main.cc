#include "type.hpp"

#define i_TYPE i32
#define i_KEY i32
#include "deque.hpp"

int main(void) {
    i32_deque dq = i32_init();

    for (i32 i = 0; i < 20; ++i) {
        i32_push_back(&dq, i + 1);
    }
    i32_pop_back(&dq, NULL);

    for (usz i = 0; i < dq.size; ++i) {
        printf(" %d", dq.arr[(dq.front + i) % dq.capacity]);
    }
    printf("\n");

    i32_free(&dq);
    return 0;
}
