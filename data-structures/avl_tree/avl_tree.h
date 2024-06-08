#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdbool.h>

typedef struct avl_node {
    int data;
    int height;
    struct avl_node* left;
    struct avl_node* right;
    struct avl_node* parent;
} avl_node_t;

typedef struct avl_tree {
    avl_node_t* root;
    int size;
} avl_tree_t;

avl_tree_t* avl_create(void);

void avl_insert(avl_tree_t* tree, int data);

void avl_delete(avl_tree_t* tree, int data);

bool avl_search(avl_tree_t* tree, int data);

void avl_destroy(avl_tree_t* tree);

#endif // AVL_TREE_H
