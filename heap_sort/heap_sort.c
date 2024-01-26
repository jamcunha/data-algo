#include "heap_sort.h"

#include "../utils/utils.h"

void heap_sort_heapify(int* array, int size, int index) {
    int left = index * 2 + 1;
    int right = index * 2 + 2;

    int largest = index;

    if (left < size && array[left] > array[index]) {
        largest = left;
    }

    if (right < size && array[right] > array[largest]) {
        largest = right;
    }

    if (largest != index) {
        swap(&array[index], &array[largest]);
        heap_sort_heapify(array, size, largest);
    }
}

void heap_sort_build_heap(int* array, int size) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        heap_sort_heapify(array, size, i);
    }
}

void heap_sort(int* array, int size) {
    heap_sort_build_heap(array, size);

    for (int i = size - 1; i >= 0; i--) {
        swap(&array[0], &array[i]);
        heap_sort_heapify(array, i, 0);
    }
}
