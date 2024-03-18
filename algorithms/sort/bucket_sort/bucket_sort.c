#include "bucket_sort.h"

#include <stdlib.h>

static const int BUCKET_SIZE = 5;

struct bucket_node {
    int data;
    struct bucket_node* next;
};

static struct bucket_node* insertion_sort(struct bucket_node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    struct bucket_node* sorted = NULL;
    struct bucket_node* current = head;
    while (current != NULL) {
        struct bucket_node* next = current->next;
        if (sorted == NULL || sorted->data >= current->data) {
            current->next = sorted;
            sorted = current;
        } else {
            struct bucket_node* search = sorted;
            while (search->next != NULL && search->next->data < current->data) {
                search = search->next;
            }
            current->next = search->next;
            search->next = current;
        }
        current = next;
    }

    return sorted;
}

void bucket_sort(int* arr, int n) {
    if (arr == NULL || n <= 0) {
        return;
    }

    int max = arr[0];
    int min = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
        if (arr[i] < min) {
            min = arr[i];
        }
    }

    int bucket_count = (max - min) / BUCKET_SIZE + 1;
    struct bucket_node** buckets = calloc(bucket_count, sizeof(struct bucket_node*));

    for (int i = 0; i < n; i++) {
        int index = (arr[i] - min) / BUCKET_SIZE;
        struct bucket_node* node = malloc(sizeof(struct bucket_node));

        node->data = arr[i];
        node->next = NULL;

        if (buckets[index] == NULL) {
            buckets[index] = node;
        } else {
            struct bucket_node* current = buckets[index];
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = node;
        }
    }

    int index = 0;
    for (int i = 0; i < bucket_count; i++) {
        if (buckets[i] != NULL) {
            buckets[i] = insertion_sort(buckets[i]);
            struct bucket_node* current = buckets[i];
            while (current != NULL) {
                arr[index++] = current->data;
                current = current->next;
            }
        }
    }

    free(buckets);
}
