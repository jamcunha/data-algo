#ifndef B_TREE_H
#define B_TREE_H

#include <stdbool.h>

// NOTE: MAX_KEYS could be a param when creating the tree
#define MAX_KEYS 5
#define MIN_KEYS (MAX_KEYS / 2)

typedef struct b_node {
    int             keys[MAX_KEYS];
    struct b_node*  children[MAX_KEYS + 1];
    int             num_keys;
    bool            is_leaf;
} b_node_t;

typedef struct b_tree {
    b_node_t* root;
} b_tree_t;

b_tree_t* b_tree_create(void);

void b_tree_insert(b_tree_t* tree, int key);

void b_tree_delete(b_tree_t* tree, int key);

bool b_tree_search(b_tree_t* tree, int key);

void b_tree_destroy(b_tree_t* tree);

#endif // B_TREE_H
