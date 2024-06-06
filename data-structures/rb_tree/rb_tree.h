#ifndef RB_TREE_H
#define RB_TREE_H

#include <stdbool.h>

typedef enum {
    RED = true,
    BLACK = false,
} color_t;

typedef struct rb_node {
    int data;
    color_t color;
    struct rb_node *parent;
    struct rb_node *left;
    struct rb_node *right;

    // For nil nodes
    bool is_null;
} rb_node_t;

typedef struct rb_tree {
    rb_node_t* root;
    int size;
} rb_tree_t;

rb_tree_t* rb_create(void);

void rb_insert(rb_tree_t* tree, int data);

void rb_delete(rb_tree_t* tree, int data);

bool rb_search(rb_tree_t* tree, int data);

void rb_destroy(rb_tree_t* tree);

#endif // RB_TREE_H
