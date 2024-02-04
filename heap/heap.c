#include "heap.h"

#include <stdlib.h>
#include "../utils/utils.h"

heap_t* heap_create(int capacity, bool (*compare)(int, int)) {
    heap_t* heap = malloc(sizeof(heap_t));
    if (heap == NULL) {
        return NULL;
    }

    heap->capacity = capacity;
    heap->compare = compare;
    heap->size = 0;
    heap->data = malloc(sizeof(int) * capacity);
    if (heap->data == NULL) {
        free(heap);
        return NULL;
    }

    return heap;
}

heap_t* heap_create_from_array(int* array, int size, bool (*compare)(int, int)) {
    heap_t* heap = heap_create(size, compare);
    if (heap == NULL) {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        if (!heap_insert(heap, array[i])) {
            heap_destroy(heap);
            return NULL;
        }
    }

    return heap;
}

void heap_destroy(heap_t* heap) {
    free(heap->data);
    free(heap);
}

void heapify_down(heap_t* heap, int index) {
    if (heap->size == 0) {
        return;
    }

    int left = heap_left(index);
    int right = heap_right(index);

    int smallestOrLargest = index;
    
    if (left < heap->size && heap->compare(heap->data[left], heap->data[index])) {
        smallestOrLargest = left;
    }

    if (right < heap->size && heap->compare(heap->data[right], heap->data[smallestOrLargest])) {
        smallestOrLargest = right;
    }

    if (smallestOrLargest != index) {
        swap(&heap->data[index], &heap->data[smallestOrLargest]);
        heapify_down(heap, smallestOrLargest);
    }
}

void heapify_up(heap_t* heap, int index) {
    if (heap->size == 0) {
        return;
    }

    int parent = heap_parent(index);

    if (index != 0 && heap->compare(heap->data[index], heap->data[parent])) {
        swap(&heap->data[index], &heap->data[parent]);
        heapify_up(heap, parent);
    }
}

bool heap_insert(heap_t* heap, int value) {
    if (heap->size == heap->capacity) {
        return false;
    }

    heap->data[heap->size] = value;
    heap->size++;

    heapify_up(heap, heap->size - 1);
    return true;
}

bool heap_pop(heap_t* heap) {
    if (heap->size == 0) {
        return false;
    }

    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;

    heapify_down(heap, 0);
    return true;
}

int heap_peek(heap_t* heap) {
    return heap->data[0];
}

bool heap_is_empty(heap_t* heap) {
    return heap->size == 0;
}
