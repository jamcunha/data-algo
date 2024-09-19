#ifndef DISJOINT_SET_FOREST_H
#define DISJOINT_SET_FOREST_H

typedef struct ds_forest {
    int *parent;
    int *rank;
    int size;
} ds_forest_t;

ds_forest_t *make_set_forest(int *elems, int size);

int find_set_forest(ds_forest_t *ds, int x);

void union_set_forest(ds_forest_t *ds, int x, int y);

void destroy_set_forest(ds_forest_t *ds);

#endif // DISJOINT_SET_FOREST_H
