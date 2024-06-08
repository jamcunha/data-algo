#include "avl_tree.h"

#include <stdlib.h>

static avl_node_t* create_node(int data) {
    avl_node_t* node = (avl_node_t*)malloc(sizeof(avl_node_t));
    *node = (avl_node_t){
        .data = data,
        .height = 0,
        .parent = NULL,
        .left = NULL,
        .right = NULL,
    };
    return node;
}

static void destroy(avl_node_t* node) {
    if (node == NULL) {
        return;
    }

    destroy(node->left);
    destroy(node->right);
    free(node);
}

static int height(avl_node_t* node) {
    return node == NULL ? -1 : node->height;
}

static void rotate_left(avl_tree_t* tree, avl_node_t* node) {
    avl_node_t* right = node->right;
    node->right = right->left;
    if (right->left != NULL) {
        right->left->parent = node;
    }

    right->parent = node->parent;
    if (node->parent == NULL) {
        tree->root = right;
    } else if (node == node->parent->left) {
        node->parent->left = right;
    } else {
        node->parent->right = right;
    }

    right->left = node;
    node->parent = right;

    int rh = height(node->right);
    int lh = height(node->left);
    node->height = (lh > rh ? lh : rh) + 1;

    rh = height(right->right);
    lh = height(right->left);
    right->height = (lh > rh ? lh : rh) + 1;
}

static void rotate_right(avl_tree_t* tree, avl_node_t* node) {
    avl_node_t* left = node->left;
    node->left = left->right;
    if (left->right != NULL) {
        left->right->parent = node;
    }

    left->parent = node->parent;
    if (node->parent == NULL) {
        tree->root = left;
    } else if (node == node->parent->right) {
        node->parent->right = left;
    } else {
        node->parent->left = left;
    }

    left->right = node;
    node->parent = left;

    int rh = height(node->right);
    int lh = height(node->left);
    node->height = (lh > rh ? lh : rh) + 1;

    rh = height(left->right);
    lh = height(left->left);
    left->height = (lh > rh ? lh : rh) + 1;
}

static int balance_factor(avl_node_t* node) {
    return height(node->left) - height(node->right);
}

static void balance(avl_tree_t* tree, avl_node_t* node) {
    int rh = height(node->right);
    int lh = height(node->left);

    node->height = (lh > rh ? lh : rh) + 1;
    int balance = lh - rh;

    if (balance > 1 && balance_factor(node->left) >= 0) {
        rotate_right(tree, node);
    } else if (balance > 1 && balance_factor(node->left) < 0) {
        rotate_left(tree, node->left);
        rotate_right(tree, node);
    } else if (balance < -1 && balance_factor(node->right) <= 0) {
        rotate_left(tree, node);
    } else if (balance < -1 && balance_factor(node->right) > 0) {
        rotate_right(tree, node->right);
        rotate_left(tree, node);
    }
}

static bool insert(avl_tree_t* tree, avl_node_t* node, int data) {
    if (data == node->data) {
        // do not insert duplicates
        return false;
    }

    bool to_balance = false;
    if (data < node->data) {
        if (node->left == NULL) {
            node->left = create_node(data);
            node->left->parent = node;
            to_balance = true;
        } else {
            to_balance = insert(tree, node->left, data);
        }
    } else {
        if (node->right == NULL) {
            node->right = create_node(data);
            node->right->parent = node;
            to_balance = true;
        } else {
            to_balance = insert(tree, node->right, data);
        }
    }

    if (to_balance) balance(tree, node);
    return to_balance;
}

static void transplant(avl_tree_t* tree, avl_node_t* u, avl_node_t* v) {
    if (u->parent == NULL) {
        tree->root = v;

        if (v != NULL) {
            v->parent = NULL;

            int lh = height(v->left);
            int rh = height(v->right);
            v->height = (lh > rh ? lh : rh) + 1;
        }
    } else if (u == u->parent->left) {
        u->parent->left = v;

        if (v != NULL) {
            v->parent = u->parent;

            int lh = height(v->left);
            int rh = height(v->right);
            v->height = (lh > rh ? lh : rh) + 1;
        }
    } else {
        u->parent->right = v;

        if (v != NULL) {
            v->parent = u->parent;

            int lh = height(v->left);
            int rh = height(v->right);
            v->height = (lh > rh ? lh : rh) + 1;
        }
    }
}

static bool delete(avl_tree_t* tree, avl_node_t* node, int data) {
    if (node == NULL) {
        return false;
    }

    bool to_balance = false;
    if (data < node->data) {
        to_balance = delete(tree, node->left, data);
    } else if (data > node->data) {
        to_balance = delete(tree, node->right, data);
    } else {
        if (node->left == NULL) {
            transplant(tree, node, node->right);
        } else if (node->right == NULL) {
            transplant(tree, node, node->left);
        } else {
            avl_node_t* successor = node->right;
            while (successor->left != NULL) {
                successor = successor->left;
            }

            if (successor->parent != node) {
                transplant(tree, successor, successor->right);
                successor->right = node->right;
                successor->right->parent = successor;

                node->right->parent = successor;
            }

            transplant(tree, node, successor);
            successor->left = node->left;
            successor->left->parent = successor;
        }

        free(node);
        return true;
    }

    if (to_balance) balance(tree, node);
    return to_balance;
}

avl_tree_t* avl_create(void) {
    avl_tree_t* tree = (avl_tree_t*)malloc(sizeof(avl_tree_t));
    *tree = (avl_tree_t){
        .root = NULL,
        .size = 0,
    };
    return tree;
}

void avl_insert(avl_tree_t* tree, int data) {
    if (tree == NULL) {
        return;
    }

    if (tree->root == NULL) {
        tree->root = create_node(data);
        return;
    }

    insert(tree, tree->root, data);
    tree->size++;
}

void avl_delete(avl_tree_t* tree, int data) {
    if (tree == NULL) {
        return;
    }

    if (tree->root == NULL) {
        return;
    }

    delete(tree, tree->root, data);
    tree->size--;
}

bool avl_search(avl_tree_t* tree, int data) {
    if (tree == NULL) {
        return false;
    }

    avl_node_t* node = tree->root;
    while (node != NULL && node->data != data) {
        if (data < node->data) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    return node != NULL;
}

void avl_destroy(avl_tree_t* tree) {
    if (tree == NULL) {
        return;
    }

    destroy(tree->root);
    free(tree);
}
