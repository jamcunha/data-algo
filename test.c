#include "test.h"

#include <criterion/criterion.h>

/********************************************
 *                                          *
 *            Sorting Algorithms            *
 *                                          *
 ********************************************/

/************************
 *    Insertion Sort    *
 ************************/

Test(insertion_sort, test) {
    int arr[] = { 5, 2, 4, 6, 1, 3 };
    int expected[] = { 1, 2, 3, 4, 5, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);
    insertion_sort(arr, n);
    cr_assert_arr_eq(arr, expected, n, "Array should be sorted");
}

/************************
 *    Selection Sort    *
 ************************/

Test(selection_sort, test) {
    int arr[] = { 5, 2, 4, 6, 1, 3 };
    int expected[] = { 1, 2, 3, 4, 5, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);
    selection_sort(arr, n);
    cr_assert_arr_eq(arr, expected, n, "Array should be sorted");
}

/************************
 *      Merge Sort      *
 ************************/

Test(merge_sort, test) {
    int arr[] = { 5, 2, 4, 6, 1, 3 };
    int expected[] = { 1, 2, 3, 4, 5, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);
    merge_sort(arr, n);
    cr_assert_arr_eq(arr, expected, n, "Array should be sorted");
}

/***********************
 *     Bubble Sort     *
 ***********************/

Test(bubble_sort, test) {
    int arr[] = { 5, 2, 4, 6, 1, 3 };
    int expected[] = { 1, 2, 3, 4, 5, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);
    bubble_sort(arr, n); cr_assert_arr_eq(arr, expected, n, "Array should be sorted");
}

/***********************
 *      Heap Sort      *
 ***********************/

Test(heap_sort, test) {
    int arr[] = { 5, 2, 4, 6, 1, 3 };
    int expected[] = { 1, 2, 3, 4, 5, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);
    heap_sort(arr, n);
    cr_assert_arr_eq(arr, expected, n, "Array should be sorted");
}

/***********************
 *      Quick Sort     *
 ***********************/

Test(quick_sort, test) {
    int arr[] = { 5, 2, 4, 6, 1, 3 };
    int expected[] = { 1, 2, 3, 4, 5, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);
    quick_sort(arr, 0, n - 1);
    cr_assert_arr_eq(arr, expected, n, "Array should be sorted");
}

/***********************
 *    Counting Sort    *
 ***********************/

Test(counting_sort, test) {
    int arr[] = { 5, 2, 4, 6, 1, 3 };
    int expected[] = { 1, 2, 3, 4, 5, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);
    counting_sort(arr, n);
    cr_assert_arr_eq(arr, expected, n, "Array should be sorted");
}

/***********************
 *      Radix Sort     *
 ***********************/

Test(radix_sort, test) {
    int arr[] = { 5, 2, 4, 6, 1, 3 };
    int expected[] = { 1, 2, 3, 4, 5, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);
    radix_sort(arr, n);
    cr_assert_arr_eq(arr, expected, n, "Array should be sorted");
}

/********************************************
 *                                          *
 *           Searching Algorithms           *
 *                                          *
 ********************************************/

/*************************
 *     Linear Search     *
 *************************/

Test(linear_search, passing) {
    int arr[] = { 5, 2, 4, 6, 1, 3 };
    int n = sizeof(arr) / sizeof(arr[0]);
    cr_assert_eq(linear_search(arr, n, 4), 2, "Array should contain 4 at index 2");
}

Test(linear_search, failing) {
    int arr[] = { 5, 2, 6, 1, 3 };
    int n = sizeof(arr) / sizeof(arr[0]);
    cr_assert_eq(linear_search(arr, n, 4), -1, "Array should not contain 4");
}

/*************************
 *     Binary Search     *
 *************************/

Test(binary_search, passing) {
    int arr[] = { 5, 2, 4, 6, 1, 3 };
    int n = sizeof(arr) / sizeof(arr[0]);
    cr_assert_eq(binary_search(arr, n, 4), 2, "Array should contain 4 at index 2");
}

Test(binary_search, failing) {
    int arr[] = { 5, 2, 6, 1, 3 };
    int n = sizeof(arr) / sizeof(arr[0]);
    cr_assert_eq(binary_search(arr, n, 4), -1, "Array should not contain 4");
}

/*******************************************
 *                                         *
 *             Data Structures             *
 *                                         *
 *******************************************/

/************************
 *         Heap         *
 ************************/

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

/************************
 *    Priority Queue    *
 ************************/

Test(priority_queue, test) {
    pq_t* pq = pq_create(10, true); // min priority queue

    cr_assert(pq_is_empty(pq), "Priority queue should be empty");

    pq_insert(pq, 5, 1);
    pq_insert(pq, 2, 2);
    pq_insert(pq, 4, 3);
    pq_insert(pq, 6, 4);
    pq_insert(pq, 1, 5);
    pq_insert(pq, 3, 6);
    pq_insert(pq, 2, 7);

    int tmp;
    cr_assert_eq((tmp = pq_peek(pq)), 5, "Priority queue should have 5 at the top, got %d", tmp);
    cr_assert(pq_pop(pq), "Priority queue should have removed the minimum key");
    cr_assert_eq((tmp = pq_peek(pq)), 2, "Priority queue should have 2 at the top, got %d", tmp);

    pq_update_key(pq, 6, 0);
    cr_assert_eq((tmp = pq_peek(pq)), 6, "Priority queue should have 6 at the top, got %d", tmp);

    int size = pq->size;
    for (int i = 0; i < size; i++) {
        pq_pop(pq);
    }

    cr_assert(pq_is_empty(pq), "Priority queue should be empty");
    cr_assert(!pq_pop(pq), "Priority queue should not have removed any key");

    pq_destroy(pq);
}
