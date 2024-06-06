#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <stdbool.h>

typedef struct bst_node {
    int data;
    struct bst_node *parent;
    struct bst_node *left;
    struct bst_node *right;
} bst_node_t;

typedef struct bst {
    bst_node_t* root;
    int size;
} bst_t;

bst_t* bst_create(void);

void bst_insert(bst_t* tree, int data);

void bst_delete(bst_t* tree, int data);

bool bst_search(bst_t* tree, int data);

int bst_min(bst_t* tree);

int bst_max(bst_t* tree);

int* bst_inorder(bst_t* tree);

int* bst_preorder(bst_t* tree);

int* bst_postorder(bst_t* tree);

void bst_destroy(bst_t* tree);

#endif // BINARY_SEARCH_TREE_H
