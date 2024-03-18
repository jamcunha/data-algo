#ifndef HEAP_H
#define HEAP_H

#include <stdbool.h>

// Heap helper macros
#define heap_parent(i) ((i - 1) / 2)
#define heap_left(i) ((i) * 2 + 1)
#define heap_right(i) ((i) * 2 + 2)

typedef struct heap {
    int*    data;
    int     size;
    int     capacity;
    bool    (*compare)(int, int);
} heap_t;

heap_t* heap_create(int capacity, bool (*compare)(int, int));

heap_t* heap_create_from_array(int* array, int size, bool (*compare)(int, int));

void heap_destroy(heap_t* heap);

void heapify_down(heap_t* heap, int index);

void heapify_up(heap_t* heap, int index);

bool heap_insert(heap_t* heap, int value);

bool heap_pop(heap_t* heap);

int heap_peek(heap_t* heap);

bool heap_is_empty(heap_t* heap);

#endif // HEAP_H
