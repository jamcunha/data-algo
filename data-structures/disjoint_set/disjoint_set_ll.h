#ifndef DISJOINT_SET_LL_H
#define DISJOINT_SET_LL_H

#include <stdbool.h>

// Disjoint set using linked list

struct ds_ll_node {
    int data;
    struct ds_ll_node *next;
    struct ds_ll *set;
};

struct ds_ll {
    struct ds_ll_node *head;
    struct ds_ll_node *tail;
    int size; // used in weighted union

    bool is_obsolete; // used when freeing memory
};

typedef struct ds_ll_node ds_ll_node_t;
typedef struct ds_ll ds_ll_t;

ds_ll_t *make_set_ll(int x);

ds_ll_t *find_set_ll(ds_ll_node_t *x);

void union_set_ll(ds_ll_t *ds1, ds_ll_t *ds2);

void weighted_union_set_ll(ds_ll_t *ds1, ds_ll_t *ds2);

void destroy_set_ll(ds_ll_t *ds);

#endif // DISJOINT_SET_LL_H
