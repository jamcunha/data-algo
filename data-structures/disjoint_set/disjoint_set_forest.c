#include "disjoint_set_forest.h"
#include <stdlib.h>

static void link(ds_forest_t *ds, int x, int y) {
    if (x == y) {
        return;
    }

    // Union by rank
    if (ds->rank[x] > ds->rank[y]) {
        ds->parent[y] = x;
    } else {
        ds->parent[x] = y;
        if (ds->rank[x] == ds->rank[y]) {
            ds->rank[y]++;
        }
    }
}

ds_forest_t *make_set_forest(int *elems, int size) {
    ds_forest_t *ds = (ds_forest_t *)malloc(sizeof(ds_forest_t));
    ds->parent = (int *)malloc(size * sizeof(int));
    ds->rank = (int *)malloc(size * sizeof(int));
    ds->size = size;

    for (int i = 0; i < size; i++) {
        ds->parent[i] = elems[i];
        ds->rank[i] = 0;
    }

    return ds;
}

int find_set_forest(ds_forest_t *ds, int x) {
    // Path compression
    if (x != ds->parent[x]) {
        ds->parent[x] = find_set_forest(ds, ds->parent[x]);
    }

    return ds->parent[x];
}

void union_set_forest(ds_forest_t *ds, int x, int y) {
    link(ds, find_set_forest(ds, x), find_set_forest(ds, y));
}

void destroy_set_forest(ds_forest_t *ds) {
    free(ds->parent);
    free(ds->rank);
    free(ds);
}
