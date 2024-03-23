#include "quick_sort.h"

#include <stdbool.h>

// simpler partitioning scheme
/* static int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
} */

static int hoare_partition(int *arr, int low, int high) {
    int pivot = arr[low];
    int i = low - 1;
    int j = high;

    while (true) {
        do { j--; } while (arr[j] > pivot);
        do { i++; } while (arr[i] < pivot);

        if (i < j) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        } else {
            return j;
        }
    }
}

void quick_sort(int *arr, int low, int high) {
    if (low < high) {
        int pivot = hoare_partition(arr, low, high);
        quick_sort(arr, low, pivot - 1);
        quick_sort(arr, pivot + 1, high);
    }
}
