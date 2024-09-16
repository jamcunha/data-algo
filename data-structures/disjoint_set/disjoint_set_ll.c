#include "disjoint_set_ll.h"
#include <stdlib.h>

static ds_ll_node_t *create_node(ds_ll_t* ds, int data) {
    ds_ll_node_t *node = (ds_ll_node_t *)malloc(sizeof(ds_ll_node_t));
    node->data = data;
    node->next = NULL;
    node->set = ds;
    return node;
}

ds_ll_t *make_set_ll(int x) {
    ds_ll_t *ds = (ds_ll_t *)malloc(sizeof(ds_ll_t));
    ds->head = create_node(ds, x);
    ds->tail = ds->head;
    ds->size = 1;
    return ds;
}

ds_ll_t *find_set_ll(ds_ll_node_t *x) {
    return x->set;
}

void union_set_ll(ds_ll_t *ds1, ds_ll_t *ds2) {
    if (ds1 == ds2) {
        return;
    }

    ds_ll_node_t *node = ds2->head;
    while (node) {
        node->set = ds1;
        node = node->next;
    }

    ds1->tail->next = ds2->head;
    ds1->tail = ds2->tail;

    ds1->size += ds2->size;
    ds2->is_obsolete = true;
}

void weighted_union_set_ll(ds_ll_t *ds1, ds_ll_t *ds2) {
    if (ds1 == ds2) {
        return;
    }

    if (ds1->size < ds2->size) {
        union_set_ll(ds2, ds1);
    } else {
        union_set_ll(ds1, ds2);
    }
}

void destroy_set_ll(ds_ll_t *ds) {
    if (!ds->is_obsolete) {
        ds_ll_node_t *node = ds->head;
        while (node) {
            ds_ll_node_t *temp = node;
            node = node->next;
            free(temp);
        }
    }

    free(ds);
}
