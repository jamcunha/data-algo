#include "binary_search_tree.h"

#include <stdlib.h>

static bst_node_t* create_node(int data) {
    bst_node_t* node = (bst_node_t*)malloc(sizeof(bst_node_t));
    *node = (bst_node_t) {
        .data = data,
        .parent = NULL,
        .left = NULL,
        .right = NULL,
    };
    return node;
}

static void insert(bst_node_t* root, int data) {
    if (data < root->data) {
        if (root->left == NULL) {
            root->left = create_node(data);
            root->left->parent = root;
        } else {
            insert(root->left, data);
        }
    } else {
        if (root->right == NULL) {
            root->right = create_node(data);
            root->right->parent = root;
        } else {
            insert(root->right, data);
        }
    }
}

static bst_node_t* search(bst_node_t* root, int data) {
    if (root == NULL) {
        return NULL;
    }

    if (root->data == data) {
        return root;
    }

    if (data < root->data) {
        return search(root->left, data);
    } else {
        return search(root->right, data);
    }
}

static bst_node_t* min(bst_node_t* root) {
    if (root->left == NULL) {
        return root;
    }

    return min(root->left);
}

static bst_node_t* max(bst_node_t* root) {
    if (root->right == NULL) {
        return root;
    }

    return max(root->right);
}

/*
static bst_node_t* successor(bst_node_t* node) {
    if (node == NULL) {
        return NULL;
    }

    if (node->right != NULL) {
        bst_node_t* successor = node->right;
        while (successor->left != NULL) {
            successor = successor->left;
        }
        return successor;
    }

    bst_node_t* parent = node->parent;
    while (parent != NULL && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }

    return parent;
}

static bst_node_t* predecessor(bst_node_t* node) {
    if (node == NULL) {
        return NULL;
    }

    if (node->left != NULL) {
        bst_node_t* predecessor = node->left;
        while (predecessor->right != NULL) {
            predecessor = predecessor->right;
        }
        return predecessor;
    }

    bst_node_t* parent = node->parent;
    while (parent != NULL && node == parent->left) {
        node = parent;
        parent = parent->parent;
    }

    return parent;
}
*/

static void transplant(bst_t* tree, bst_node_t* u, bst_node_t* v) {
    if (u->parent == NULL) {
        tree->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }

    if (v != NULL) {
        v->parent = u->parent;
    }
}

static void destroy(bst_node_t* root) {
    if (root == NULL) {
        return;
    }

    destroy(root->left);
    destroy(root->right);

    free(root);
}

static void inorder(bst_node_t* node, int* result, int* index) {
    if (node == NULL) {
        return;
    }

    inorder(node->left, result, index);
    result[*index] = node->data;
    (*index)++;
    inorder(node->right, result, index);
}

static void preorder(bst_node_t* node, int* result, int* index) {
    if (node == NULL) {
        return;
    }

    result[*index] = node->data;
    (*index)++;
    preorder(node->left, result, index);
    preorder(node->right, result, index);
}

static void postorder(bst_node_t* node, int* result, int* index) {
    if (node == NULL) {
        return;
    }

    postorder(node->left, result, index);
    postorder(node->right, result, index);
    result[*index] = node->data;
    (*index)++;
}

bst_t* bst_create(void) {
    bst_t* tree = (bst_t*)malloc(sizeof(bst_t));
    *tree = (bst_t) {
        .root = NULL,
        .size = 0,
    };

    return tree;
}

void bst_insert(bst_t* tree, int data) {
    if (tree == NULL) {
        return;
    }

    if (tree->root == NULL) {
        tree->root = create_node(data);
        return;
    }

    insert(tree->root, data);
    tree->size++;
}

void bst_delete(bst_t* tree, int data) {
    if (tree == NULL) {
        return;
    }

    bst_node_t* node = search(tree->root, data);
    if (node == NULL) {
        return;
    }

    if (node->left == NULL) {
        transplant(tree, node, node->right);

        if (node->right != NULL) {
            node->right->parent = node->parent;
            node->parent->left = node->right;
        }
    } else if (node->right == NULL) {
        transplant(tree, node, node->left);

        if (node->left != NULL) {
            node->left->parent = node->parent;
            node->parent->right = node->left;
        }
    } else {
        bst_node_t* successor = min(node->right);

        // NOTE: If successor is not the right child of node
        // then we need to replace successor with its right child
        // and assign node's right child to successor's right child
        if (successor->parent != node) {
            transplant(tree, successor, successor->right);
            successor->right = node->right;
            successor->right->parent = successor;

            node->right->parent = successor;
        }

        transplant(tree, node, successor);
        successor->left = node->left;
        successor->left->parent = successor;

        successor->parent = node->parent;

        if (node->parent == NULL) {
            tree->root = successor;
        } else if (node->parent->left == node) {
            node->parent->left = successor;
        } else {
            node->parent->right = successor;
        }
    }

    free(node);
    tree->size--;
}

bool bst_search(bst_t* tree, int data) {
    if (tree == NULL) {
        return false;
    }

    return search(tree->root, data) != NULL;
}

int bst_min(bst_t* tree) {
    if (tree == NULL) {
        // TODO: maybe add asserts instead of returning -1 (To all data structures and algos)
        return -1;
    }

    return min(tree->root)->data;
}

int bst_max(bst_t* tree) {
    if (tree == NULL) {
        return -1;
    }

    return max(tree->root)->data;
}

int* bst_inorder(bst_t* tree) {
    if (tree == NULL) {
        return NULL;
    }

    int* result = (int*)malloc(sizeof(int) * tree->size);
    int index = 0;

    inorder(tree->root, result, &index);
    return result;
}

int* bst_preorder(bst_t* tree) {
    if (tree == NULL) {
        return NULL;
    }

    int* result = (int*)malloc(sizeof(int) * tree->size);
    int index = 0;

    preorder(tree->root, result, &index);
    return result;
}

int* bst_postorder(bst_t* tree) {
    if (tree == NULL) {
        return NULL;
    }

    int* result = (int*)malloc(sizeof(int) * tree->size);
    int index = 0;

    postorder(tree->root, result, &index);
    return result;
}

void bst_destroy(bst_t* tree) {
    if (tree == NULL) {
        return;
    }

    destroy(tree->root);
    free(tree);
}
