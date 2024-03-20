#include <criterion/criterion.h>
#include "../algorithms/search/linear_search/linear_search.h"

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
