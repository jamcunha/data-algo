#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

typedef struct dll_node {
    int                 data;
    struct dll_node*    prev;
    struct dll_node*    next;
} dll_node_t;

typedef struct dll {
    dll_node_t* head;
    dll_node_t* tail;
    int         size;
} dll_t;

dll_t* dll_create(void);

void dll_prepend(dll_t* list, int data);

void dll_insert(dll_t* list, int data);

void dll_delete(dll_t* list, int data);

void dll_delete_node(dll_t* list, dll_node_t* node);

dll_node_t* dll_get(dll_t* list, int index);

dll_node_t* dll_find(dll_t* list, int data);

void dll_destroy(dll_t* list);

#endif // DOUBLE_LINKED_LIST_H
