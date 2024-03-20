#include <criterion/criterion.h>
#include "../algorithms/sort/insertion_sort/insertion_sort.h"

Test(insertion_sort, test) {
    int arr[] = { 5, 2, 4, 6, 1, 3 };
    int expected[] = { 1, 2, 3, 4, 5, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);
    insertion_sort(arr, n);
    cr_assert_arr_eq(arr, expected, n, "Array should be sorted");
}
