#include "selection_sort.h"

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp; 
}

void selection_sort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i; j < n; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        swap(&arr[i], &arr[min]);
    }
}
