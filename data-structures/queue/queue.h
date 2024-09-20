#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

#define QUEUE_INIT_CAPACITY 10

typedef struct {
    int *data;
    int head;
    int tail;
    int capacity;
} queue_t;

queue_t* queue_create(void);

bool queue_is_empty(queue_t *queue);

void queue_enqueue(queue_t *queue, int value);

int queue_dequeue(queue_t *queue);

void queue_destroy(queue_t *queue);

#endif // QUEUE_H
