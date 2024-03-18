#include "merge_sort.h"

void merge(int *arr, int l, int m, int r) {
    int left_size = m - l + 1;
    int right_size = r - m;

    int left[left_size];
    int right[right_size];

    for (int i = 0; i < left_size; i++) {
        left[i] = arr[l + i];
    }

    for (int i = 0; i < right_size; i++) {
        right[i] = arr[m + 1 + i];
    }

    int i = 0, j = 0, k = l;

    // While both arrays have elements
    // Compare the elements of both arrays
    // and put the smaller one in the original array
    while (i < left_size && j < right_size) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }

    // If there are elements left in the left array
    while (i < left_size) {
        arr[k++] = left[i++];
    }

    // If there are elements left in the right array
    while (j < right_size) {
        arr[k++] = right[j++];
    }
}

void merge_sort(int *arr, int n) {
    if (n <= 1) {
        return;
    }

    int mid = n / 2;

    merge_sort(arr, mid);
    merge_sort(arr + mid, n - mid);

    merge(arr, 0, mid - 1, n - 1);
}
