#include "queue.h"

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
    return queue->head == queue->tail;
}

bool queue_enqueue(queue_t *queue, int value) {
    if (queue->tail == queue->capacity) {
        int new_capacity = queue->capacity * 2;
        int *new_data = (int*)malloc(sizeof(int) * new_capacity);
        if (new_data == NULL) {
            return false;
        }

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
    return true;
}

bool queue_dequeue(queue_t *queue, int *value) {
    if (queue_is_empty(queue)) {
        return false;
    }

    *value = queue->data[queue->head++];
    return true;
}

void queue_destroy(queue_t *queue) {
    if (queue == NULL) {
        return;
    }

    free(queue->data);
    free(queue);
}
