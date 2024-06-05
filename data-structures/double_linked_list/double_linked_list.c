#include "double_linked_list.h"

#include <stdlib.h>

static dll_node_t* dll_create_node(int data) {
    dll_node_t* node = (dll_node_t*)malloc(sizeof(dll_node_t));
    if (node == NULL) {
        return NULL;
    }

    *node = (dll_node_t){
        .data = data,
        .prev = NULL,
        .next = NULL
    };
    return node;
}

dll_t* dll_create(void) {
    dll_t* list = (dll_t*)malloc(sizeof(dll_t));
    if (list == NULL) {
        return NULL;
    }

    *list = (dll_t){
        .head = NULL,
        .tail = NULL,
        .size = 0
    };
    return list;
}

void dll_prepend(dll_t* list, int data) {
    dll_node_t* node = dll_create_node(data);
    dll_node_t* head = list->head;

    node->next = head;

    if (head != NULL) {
        head->prev = node;
    } else {
        list->tail = node;
    }
    list->head = node;
    list->size++;
}

void dll_insert(dll_t* list, int data) {
    dll_node_t* node = dll_create_node(data);
    dll_node_t* tail = list->tail;

    node->prev = tail;
    if (tail != NULL) {
        tail->next = node;
    } else {
        list->head = node;
    }
    list->tail = node;
    list->size++;
}

void dll_delete(dll_t* list, int data) {
    for (dll_node_t* node = list->head; node != NULL; node = node->next) {
        if (node->data == data) {
            dll_delete_node(list, node);
            return;
        }
    }
}

void dll_delete_node(dll_t* list, dll_node_t* node) {
    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        list->head = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    } else {
        list->tail = node->prev;
    }

    list->size--;
    free(node);
}

dll_node_t* dll_get(dll_t* list, int index) {
    if (index < 0 || index >= list->size) {
        return NULL;
    }

    dll_node_t* node = list->head;
    for (int i = 0; i < index && node != NULL; i++) {
        node = node->next;
    }

    return node;
}

dll_node_t* dll_find(dll_t* list, int data) {
    for (dll_node_t* node = list->head; node != NULL; node = node->next) {
        if (node->data == data) {
            return node;
        }
    }

    return NULL;
}

void dll_destroy(dll_t* list) {
    dll_node_t* node = list->head;
    while (node != NULL) {
        dll_node_t* next = node->next;
        free(node);
        node = next;
    }

    free(list);
}
