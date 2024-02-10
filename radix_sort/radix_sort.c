#include "radix_sort.h"

#include <stdlib.h>

static void count_sort(int* arr, int n, int exp, int* output) {
    int count[10] = { 0 };

    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
}

// radix sort based on counting sort
void radix_sort(int *arr, int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    int* output = (int*)malloc(n * sizeof(int));

    for (int exp = 1; max / exp > 0; exp *= 10) {
        count_sort(arr, n, exp, output);
        int* temp = arr;
        arr = output;
        output = temp;
    }

    if (output != arr) {
        for (int i = 0; i < n; i++) {
            output[i] = arr[i];
        }

        free(arr); // free the original array
    }
}
