#include <criterion/criterion.h>
#include "../data-structures/heap/heap.h"

bool min_heap(int a, int b) {
    return a < b;
}

bool max_heap(int a, int b) {
    return a > b;
}

Test(min_heap, create_min_heap) {
    int arr[] = { 5, 2, 4, 6, 1, 3 };
    int n = sizeof(arr) / sizeof(arr[0]);
    heap_t* heap = heap_create_from_array(arr, n, min_heap);

    int tmp;
    cr_assert_eq((tmp = heap_peek(heap)), 1, "Heap should have 1 at index 0, got %d", tmp);
    heap_destroy(heap);
}

Test(min_heap, min_heap_correct) {
    int arr[] = { 5, 2, 4, 6, 1, 3 };
    int n = sizeof(arr) / sizeof(arr[0]);
    heap_t* heap = heap_create_from_array(arr, n, min_heap);

    for (int i = 0; i < heap->size; i++) {
        int left = heap_left(i);
        int right = heap_right(i);

        if (left < heap->size) {
            cr_assert(heap->data[i] <= heap->data[left], "Heap property violated");
        }

        if (right < heap->size) {
            cr_assert(heap->data[i] <= heap->data[right], "Heap property violated");
        }
    }

    heap_destroy(heap);
}

Test(min_heap, operations) {
    heap_t* heap = heap_create(10, min_heap);

    cr_assert(heap_is_empty(heap), "Heap should be empty");

    heap_insert(heap, 5);
    heap_insert(heap, 2);
    heap_insert(heap, 4);
    heap_insert(heap, 6);
    heap_insert(heap, 1);
    heap_insert(heap, 3);

    int tmp;
    cr_assert_eq((tmp = heap_peek(heap)), 1, "Heap should have 1 at index 0, got %d", tmp);
    cr_assert(heap_pop(heap), "Heap should have removed the minimum value");
    cr_assert_eq((tmp = heap_peek(heap)), 2, "Heap should have 2 at index 0, got %d", tmp);

    heap_destroy(heap);
}

Test(max_heap, create_max_heap) {
    int arr[] = { 5, 2, 4, 6, 1, 3 };
    int n = sizeof(arr) / sizeof(arr[0]);
    heap_t* heap = heap_create_from_array(arr, n, max_heap);

    int tmp;
    cr_assert_eq((tmp = heap_peek(heap)), 6, "Heap should have 6 at index 0, got %d", tmp);
    heap_destroy(heap);
}

Test(max_heap, max_heap_correct) {
    int arr[] = { 5, 2, 4, 6, 1, 3 };
    int n = sizeof(arr) / sizeof(arr[0]);
    heap_t* heap = heap_create_from_array(arr, n, max_heap);

    for (int i = 0; i < heap->size; i++) {
        int left = heap_left(i);
        int right = heap_right(i);

        if (left < heap->size) {
            cr_assert(heap->data[i] >= heap->data[left], "Heap property violated");
        }

        if (right < heap->size) {
            cr_assert(heap->data[i] >= heap->data[right], "Heap property violated");
        }
    }

    heap_destroy(heap);
}

Test(max_heap, operations) {
    heap_t* heap = heap_create(10, max_heap);

    cr_assert(heap_is_empty(heap), "Heap should be empty");

    heap_insert(heap, 5);
    heap_insert(heap, 2);
    heap_insert(heap, 4);
    heap_insert(heap, 6);
    heap_insert(heap, 1);
    heap_insert(heap, 3);

    int tmp;
    cr_assert_eq((tmp = heap_peek(heap)), 6, "Heap should have 6 at index 0, got %d", tmp);

    cr_assert(heap_pop(heap), "Heap should have removed the maximum value");
    cr_assert_eq((tmp = heap_peek(heap)), 5, "Heap should have 5 at index 0, got %d", tmp);

    heap_destroy(heap);
}
