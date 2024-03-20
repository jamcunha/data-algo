#include <criterion/criterion.h>
#include "../algorithms/sort/quick_sort/quick_sort.h"


Test(quick_sort, test) {
    int arr[] = { 5, 2, 4, 6, 1, 3 };
    int expected[] = { 1, 2, 3, 4, 5, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);
    quick_sort(arr, 0, n - 1);
    cr_assert_arr_eq(arr, expected, n, "Array should be sorted");
}
