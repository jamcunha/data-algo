#include "test.h"

#include <criterion/criterion.h>

Test(insertion_sort, test1) {
    int arr[] = { 5, 2, 4, 6, 1, 3 };
    int expected[] = { 1, 2, 3, 4, 5, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);
    insertion_sort(arr, n);
    cr_assert_arr_eq(arr, expected, n, "Array should be sorted");
}
