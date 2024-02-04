#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdbool.h>

// Priority queue helper macros
#define pq_parent(i) ((i - 1) / 2)
#define pq_left(i) ((i) * 2 + 1)
#define pq_right(i) ((i) * 2 + 2)

typedef struct pq_node {
    int data;
    int key;
} pq_node_t;

typedef struct pq {
    pq_node_t*  nodes;
    int         size;
    int         capacity;

    // priority queue can be min or max
    bool        (*compare)(int, int);
} pq_t;

pq_t* pq_create(int capacity, bool is_min);

void pq_destroy(pq_t* pq);

void pq_heapify_up(pq_t* pq, int index);

void pq_heapify_down(pq_t* pq, int index);

// decrease key if min priority queue, increase key otherwise
void pq_update_key(pq_t* pq, int value, int key);

bool pq_insert(pq_t* pq, int value, int key);

bool pq_pop(pq_t* pq);

int pq_peek(pq_t* pq);

bool pq_is_empty(pq_t* pq);

#endif // PRIORITY_QUEUE_H
