#include <criterion/criterion.h>
#include "../algorithms/search/binary_search/binary_search.h"

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
