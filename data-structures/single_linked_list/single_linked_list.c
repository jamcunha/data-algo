#include "single_linked_list.h"

#include <stdlib.h>

static sll_node_t* sll_create_node(int data) {
    sll_node_t* node = (sll_node_t*)malloc(sizeof(sll_node_t));
    if (node == NULL) {
        return NULL;
    }

    *node = (sll_node_t){data, NULL};
    return node;
}

sll_t* sll_create(void) {
    sll_t* list = (sll_t*)malloc(sizeof(sll_t));
    if (list == NULL) {
        return NULL;
    }

    *list = (sll_t){.head = NULL, .tail = NULL, .size = 0};
    return list;
}

void sll_prepend(sll_t* list, int data) {
    sll_node_t* node = sll_create_node(data);
    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        node->next = list->head;
        list->head = node;
    }

    list->size++;
}

void sll_insert(sll_t* list, int data) {
    sll_node_t* node = sll_create_node(data);
    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }

    list->size++;
}

void sll_delete(sll_t* list, int data) {
    sll_node_t* node = list->head;

    // empty list
    if (node == NULL) return;

    // first position
    if (node->data == data) {
        list->head = node->next;
        list->size--; free(node);

        if (list->head == NULL) {
            list->tail = NULL;
        }

        return;
    }

    sll_node_t* prev = node;
    node = node->next;
    while (node != NULL && node->data != data) {
        prev = node; node = node->next;
    }

    // not found
    if (node == NULL) return;

    prev->next = node->next;
    free(node);
    list->size--;
}

void sll_delete_node(sll_t* list, sll_node_t* node) {
    sll_node_t* start = list->head;
    if (start == node) {
        list->head = start->next;
        list->size--; free(start);

        if (list->head == NULL) {
            list->tail = NULL;
        }

        return;
    }

    sll_node_t* prev = start;
    start = start->next;
    while (start != NULL && start != node) {
        prev = start; start = start->next;
    }

    if (start == NULL) return;

    prev->next = start->next;
    free(start);
    list->size--;
}

sll_node_t* sll_get(sll_t* list, int index) {
    sll_node_t* node = list->head;
    for (int i = 0; i < index && node != NULL; i++) {
        node = node->next;
    }

    return node;
}

sll_node_t* sll_find(sll_t* list, int data) {
    sll_node_t* node = list->head;
    while (node != NULL && node->data != data) {
        node = node->next;
    }

    return node;
}

void sll_destroy(sll_t* list) {
    sll_node_t* start = list->head;
    while (start != NULL) {
        sll_node_t* temp = start->next;
        free(start);
        start = temp;
    }

    free(list);
}
