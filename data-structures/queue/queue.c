#include "queue.h"

#include <assert.h>
#include <limits.h>
#include <stdlib.h>

queue_t* queue_create(void) {
    queue_t* queue = (queue_t*)malloc(sizeof(queue_t));
    if (queue == NULL) {
        return NULL;
    }

    queue->capacity = QUEUE_INIT_CAPACITY;
    queue->head = 0;
    queue->tail = 0;

    queue->data = (int*)malloc(sizeof(int) * queue->capacity);
    if (queue->data == NULL) {
        free(queue);
        return NULL;
    }

    return queue;
}

bool queue_is_empty(queue_t *queue) {
    assert(queue != NULL);

    return queue->head == queue->tail;
}

void queue_enqueue(queue_t *queue, int value) {
    assert(queue != NULL);

    if (queue->tail == queue->capacity) {
        assert(queue->capacity < INT_MAX / 2);

        int new_capacity = queue->capacity * 2;
        int *new_data = (int*)malloc(sizeof(int) * new_capacity);

        for (int i = 0; i < queue->tail - queue->head; i++) {
            new_data[i] = queue->data[queue->head + i];
        }

        free(queue->data);
        queue->data = new_data;
        queue->tail -= queue->head;
        queue->head = 0;
        queue->capacity = new_capacity;
    }

    queue->data[queue->tail++] = value;
}

int queue_dequeue(queue_t *queue) {
    assert(queue != NULL);
    assert(!queue_is_empty(queue));

    return queue->data[queue->head++];
}

void queue_destroy(queue_t *queue) {
    assert(queue != NULL);

    free(queue->data);
    free(queue);
}
