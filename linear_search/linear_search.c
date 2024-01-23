#include "linear_search.h"

int linear_search(int *array, int size, int key) {
    for (int i = 0; i < size; i++) {
        if (array[i] == key) {
            return i;
        }
    }

    return -1;
}
