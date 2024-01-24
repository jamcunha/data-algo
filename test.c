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
    bubble_sort(arr, n);
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
