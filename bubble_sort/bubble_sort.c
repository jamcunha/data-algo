#include "bubble_sort.h"
#include "../utils/utils.h"

void bubble_sort(int *array, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = size - 1; j > i; j--) {
            if (array[j] < array[j - 1]) {
                swap(&array[j], &array[j - 1]);
            }
        }
    }
}
