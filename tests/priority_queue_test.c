#include <criterion/criterion.h>
#include "../data-structures/priority_queue/priority_queue.h"

Test(priority_queue, test) {
    pq_t* pq = pq_create(10, true); // min priority queue

    cr_assert(pq_is_empty(pq), "Priority queue should be empty");

    pq_insert(pq, 5, 1);
    pq_insert(pq, 2, 2);
    pq_insert(pq, 4, 3);
    pq_insert(pq, 6, 4);
    pq_insert(pq, 1, 5);
    pq_insert(pq, 3, 6);
    pq_insert(pq, 2, 7);

    int tmp;
    cr_assert_eq((tmp = pq_peek(pq)), 5, "Priority queue should have 5 at the top, got %d", tmp);
    cr_assert(pq_pop(pq), "Priority queue should have removed the minimum key");
    cr_assert_eq((tmp = pq_peek(pq)), 2, "Priority queue should have 2 at the top, got %d", tmp);

    pq_update_key(pq, 6, 0);
    cr_assert_eq((tmp = pq_peek(pq)), 6, "Priority queue should have 6 at the top, got %d", tmp);

    int size = pq->size;
    for (int i = 0; i < size; i++) {
        pq_pop(pq);
    }

    cr_assert(pq_is_empty(pq), "Priority queue should be empty");
    cr_assert(!pq_pop(pq), "Priority queue should not have removed any key");

    pq_destroy(pq);
}
