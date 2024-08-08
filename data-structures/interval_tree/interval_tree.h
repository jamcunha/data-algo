#ifndef INTERVAL_TREE_H
#define INTERVAL_TREE_H

#include <stdbool.h>

typedef struct interval {
    int low;
    int high;
} interval_t;

typedef struct interval_tree_node {
    interval_t interval;
    int max;
    struct interval_tree_node* left;
    struct interval_tree_node* right;
} interval_tree_node_t;

typedef struct interval_tree {
    interval_tree_node_t* root;
    int size;
} interval_tree_t;

interval_tree_t* interval_tree_create(void);

bool interval_tree_insert(interval_tree_t* tree, int low, int high);

interval_t* interval_tree_search_interval(interval_tree_t* tree, int low, int high, int* num_intervals);

interval_t* interval_tree_search_point(interval_tree_t* tree, int point, int* num_intervals);

void interval_tree_destroy(interval_tree_t* tree);

#endif // INTERVAL_TREE_H
