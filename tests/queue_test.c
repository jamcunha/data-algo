#include <criterion/criterion.h>
#include "../data-structures/queue/queue.h"

static queue_t* queue;

static void test_setup(void) {
    queue = queue_create();
}

static void test_teardown(void) {
    queue_destroy(queue);
}

Test(queue, queue_init, .init = test_setup, .fini = test_teardown) {
    cr_assert_not_null(queue, "queue_init() failed");
    cr_assert_eq(queue->head, 0, "queue_init() failed");
    cr_assert_eq(queue->tail, 0, "queue_init() failed");
    cr_assert_eq(queue->capacity, QUEUE_INIT_CAPACITY, "queue_init() failed");
    cr_assert_not_null(queue->data, "queue_init() failed");
}

Test(queue, queue_push, .init = test_setup, .fini = test_teardown) {
    for (int i = 0; i < 10; i++) {
        queue_enqueue(queue, i);
    }

    cr_assert_eq(queue->tail, 10, "queue_enqueue() failed");
    for (int i = 0; i < 10; i++) {
        cr_assert_eq(queue->data[i], i, "queue_enqueue() failed");
    }
}

Test(queue, queue_push_resize, .init = test_setup, .fini = test_teardown) {
    for (int i = 0; i < 10; i++) {
        queue_enqueue(queue, i);
    }

    queue_enqueue(queue, 10);
    cr_assert_eq(queue->tail, 11, "queue_enqueue() failed");
    cr_assert_eq(queue->capacity, QUEUE_INIT_CAPACITY * 2, "queue_enqueue() failed");
    for (int i = 0; i < 11; i++) {
        cr_assert_eq(queue->data[i], i, "queue_enqueue() failed");
    }
}

Test(queue, queue_pop, .init = test_setup, .fini = test_teardown) {
    for (int i = 0; i < 10; i++) {
        queue_enqueue(queue, i);
    }

    for (int i = 0; i < 10; i++) {
        cr_assert_eq(queue_dequeue(queue), i, "queue_dequeue() failed");
        cr_assert_eq(queue->head, i + 1, "queue_dequeue() failed");
    }

    cr_assert_eq(queue->head, 10, "queue_dequeue() failed");
}
