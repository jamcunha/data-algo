#include "priority_queue.h"

#include <stdlib.h>

static void swap(pq_node_t* a, pq_node_t* b) {
    pq_node_t temp = *a;
    *a = *b;
    *b = temp;
}

// since we are using a single array to represent the priority queue
// we will use a linear search.
//
// a more efficient way to do this is to use a hash table to store the
// key of each element in the array. This way we can search for an
// element in O(1) time.
static int pq_search(pq_t* pq, int target) {
    for (int i = 0; i < pq->size; i++) {
        if (pq->nodes[i].data == target) {
            return i;
        }
    }

    return -1;
}

static bool min_compare(int a, int b) {
    return a < b;
}

static bool max_compare(int a, int b) {
    return a > b;
}

pq_t* pq_create(int capacity, bool is_min) {
    pq_t* pq = malloc(sizeof(pq_t));
    if (pq == NULL) {
        return NULL;
    }

    pq->capacity = capacity;
    pq->size = 0;
    pq->nodes = malloc(sizeof(pq_node_t) * capacity);
    if (pq->nodes == NULL) {
        free(pq);
        return NULL;
    }

    pq->compare = is_min ? min_compare : max_compare;

    return pq;
}

void pq_destroy(pq_t* pq) {
    free(pq->nodes);
    free(pq);
}

void pq_heapify_up(pq_t* pq, int index) {
    if (pq->size == 0) {
        return;
    }

    int parent = pq_parent(index);

    if (index != 0 && pq->compare(pq->nodes[index].key, pq->nodes[parent].key)) {
        swap(&pq->nodes[index], &pq->nodes[parent]);
        pq_heapify_up(pq, parent);
    }
}

void pq_heapify_down(pq_t* pq, int index) {
    if (pq->size == 0) {
        return;
    }

    int left = pq_left(index);
    int right = pq_right(index);

    int smallestOrLargest = index;
    
    if (left < pq->size && pq->compare(pq->nodes[left].key, pq->nodes[index].key)) {
        smallestOrLargest = left;
    }

    if (right < pq->size && pq->compare(pq->nodes[right].key, pq->nodes[smallestOrLargest].key)) {
        smallestOrLargest = right;
    }

    if (smallestOrLargest != index) {
        swap(&pq->nodes[index], &pq->nodes[smallestOrLargest]);
        pq_heapify_down(pq, smallestOrLargest);
    }
}

void pq_update_key(pq_t* pq, int value, int key) {
    int index = pq_search(pq, value);
    if (index == -1) {
        return;
    }

    pq->nodes[index].key = key;
    pq_heapify_up(pq, index);
}

bool pq_insert(pq_t* pq, int value, int key) {
    if (pq->size == pq->capacity) {
        return false;
    }

    pq_node_t node = { .data = value, .key = key };
    pq->nodes[pq->size] = node;

    pq_heapify_up(pq, pq->size);
    pq->size++;
    return true;
}

bool pq_pop(pq_t* pq) {
    if (pq->size == 0) {
        return false;
    }

    pq->nodes[0] = pq->nodes[pq->size - 1];
    pq->size--;

    if (pq->size > 0) {
        pq_heapify_down(pq, 0);
    }

    return true;
}

int pq_peek(pq_t* pq) {
    return pq->nodes[0].data;
}

bool pq_is_empty(pq_t* pq) {
    return pq->size == 0;
}
