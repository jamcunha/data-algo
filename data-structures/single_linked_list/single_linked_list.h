#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

typedef struct sll_node {
    int                 data;
    struct sll_node*    next;
} sll_node_t;

typedef struct sll {
    sll_node_t* head;
    sll_node_t* tail;
    int         size;
} sll_t;

sll_t* sll_create(void);

void sll_prepend(sll_t* list, int data);

void sll_insert(sll_t* list, int data);

void sll_delete(sll_t* list, int data);

void sll_delete_node(sll_t* list, sll_node_t* node);

sll_node_t* sll_get(sll_t* list, int index);

sll_node_t* sll_find(sll_t* list, int data);

void sll_destroy(sll_t* list);

#endif // SINGLE_LINKED_LIST_H
