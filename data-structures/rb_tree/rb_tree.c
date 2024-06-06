#include "rb_tree.h"
#include <stdlib.h>

static rb_node_t* create_node(int data) {
    rb_node_t* node = (rb_node_t*)malloc(sizeof(rb_node_t));
    *node = (rb_node_t) {
        .data = data,
        .parent = NULL,
        .left = NULL,
        .right = NULL,
        .color = RED,
        .is_null = false,
    };
    return node;
}

static void destroy(rb_node_t* root) {
    if (root == NULL) {
        return;
    }

    destroy(root->left);
    destroy(root->right);
    free(root);
}

static rb_node_t* search(rb_node_t* root, int data) {
    while (root != NULL && root->data != data) {
        if (data < root->data) {
            root = root->left;
        } else {
            root = root->right;
        }
    }

    return root;
}

static void rotate_left(rb_tree_t* tree, rb_node_t* node) {
    rb_node_t* right = node->right;
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
}

static void rotate_right(rb_tree_t* tree, rb_node_t* node) {
    rb_node_t* left = node->left;
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
}

static void insert_fixup(rb_tree_t* tree, rb_node_t* node) {
    while (node != tree->root && node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
            rb_node_t* uncle = node->parent->parent->right;
            if (uncle != NULL && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    rotate_left(tree, node);
                }

                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotate_right(tree, node->parent->parent);
            }
        } else {
            rb_node_t* uncle = node->parent->parent->left;
            if (uncle != NULL && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rotate_right(tree, node);
                }

                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotate_left(tree, node->parent->parent);
            }
        }
    }

    tree->root->color = BLACK;
}

static void transplant(rb_tree_t* tree, rb_node_t* u, rb_node_t* v) {
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

rb_tree_t* rb_create(void) {
    rb_tree_t* tree = (rb_tree_t*)malloc(sizeof(rb_tree_t));
    *tree = (rb_tree_t) {
        .root = NULL,
        .size = 0,
    };
    return tree;
}

static void delete_fixup(rb_tree_t* tree, rb_node_t* node) {
    while (node != tree->root && node->color == BLACK) {
        if (node == node->parent->left) {
            rb_node_t* sibling = node->parent->right;
            if (sibling != NULL && sibling->color == RED) {
                sibling->color = BLACK;
                node->parent->color = RED;
                rotate_left(tree, node->parent);
                sibling = node->parent->right;
            }

            if (sibling != NULL && (sibling->left == NULL || sibling->left->color == BLACK) && (sibling->right == NULL || sibling->right->color == BLACK)) {
                sibling->color = RED;
                node = node->parent;
            } else {
                if (sibling != NULL && (sibling->right == NULL || sibling->right->color == BLACK)) {
                    if (sibling->left != NULL) {
                        sibling->left->color = BLACK;
                    }

                    sibling->color = RED;
                    rotate_right(tree, sibling);
                    sibling = node->parent->right;
                }

                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                if (sibling->right != NULL) {
                    sibling->right->color = BLACK;
                }
                rotate_left(tree, node->parent);
                node = tree->root;
            }
        } else {
            rb_node_t* sibling = node->parent->left;
            if (sibling != NULL && sibling->color == RED) {
                sibling->color = BLACK;
                node->parent->color = RED;
                rotate_right(tree, node->parent);
                sibling = node->parent->left;
            }

            if (sibling != NULL && (sibling->left == NULL || sibling->left->color == BLACK) && (sibling->right == NULL || sibling->right->color == BLACK)) {
                sibling->color = RED;
                node = node->parent;
            } else {
                if (sibling != NULL && sibling->left->color == BLACK) {
                    if (sibling->right != NULL) {
                        sibling->right->color = BLACK;
                    }
                    sibling->color = RED;
                    rotate_left(tree, sibling);
                    sibling = node->parent->left;
                }

                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                if (sibling->left != NULL) {
                    sibling->left->color = BLACK;
                }
                rotate_right(tree, node->parent);
                node = tree->root;
            }
        }
    }

    if (node != NULL) {
        node->color = BLACK;
    }
}

void rb_insert(rb_tree_t* tree, int data) {
    if (tree == NULL) {
        return;
    }

    rb_node_t* node = create_node(data);

    rb_node_t* parent = NULL;
    for (rb_node_t* current = tree->root; current != NULL;) {
        parent = current;
        if (node->data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    node->parent = parent;

    if (parent == NULL) {
        tree->root = node;
    } else if (node->data < parent->data) {
        parent->left = node;
    } else {
        parent->right = node;
    }

    insert_fixup(tree, node);
    tree->size++;
}

void rb_delete(rb_tree_t* tree, int data) {
    if (tree == NULL) {
        return;
    }

    rb_node_t* node = search(tree->root, data);
    if (node == NULL) {
        return;
    }

    color_t y_original_color = node->color;

    // node used to fix tree
    rb_node_t* x = NULL;

    if (node->left == NULL) {
        x = node->right;
        if (x == NULL) {
            x = create_node(0);
            x->color = BLACK;
            x->is_null = true;

            node->right = x;
            x->parent = node;
        }

        transplant(tree, node, node->right);

        if (node->right != NULL) {
            node->right->parent = node->parent;
            node->parent->left = node->right;
        }
    } else if (node->right == NULL) {
        x = node->left;
        if (x == NULL) {
            x = create_node(0);
            x->color = BLACK;
            x->is_null = true;

            node->left = x;
            x->parent = node;
        }

        transplant(tree, node, node->left);

        if (node->left != NULL) {
            node->left->parent = node->parent;
            node->parent->right = node->left;
        }
    } else {
        // get the successor of node
        rb_node_t* successor = node->right;
        while (successor->left != NULL) {
            successor = successor->left;
        }

        y_original_color = successor->color;
        x = successor->right;
        if (x == NULL) {
            x = create_node(0);
            x->color = BLACK;
            x->is_null = true;

            successor->right = x;
            x->parent = successor;
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
        successor->parent = node->parent;

        if (node->parent == NULL) {
            tree->root = successor;
        } else if (node == node->parent->left) {
            node->parent->left = successor;
        } else {
            node->parent->right = successor;
        }

        successor->color = node->color;
    }

    // to remove if null node
    rb_node_t* x_backup = x;

    // correct red black tree violations
    if (y_original_color == BLACK) {
        delete_fixup(tree, x);
    }

    if (x_backup != NULL && x_backup->is_null) {
        if (x_backup->parent->left == x_backup) {
            x_backup->parent->left = NULL;
        } else {
            x_backup->parent->right = NULL;
        }

        free(x_backup);
    }
}

bool rb_search(rb_tree_t* tree, int data) {
    if (tree == NULL) {
        return false;
    }

    return search(tree->root, data) != NULL;
}

void rb_destroy(rb_tree_t* tree) {
    if (tree == NULL) {
        return;
    }

    destroy(tree->root);
    free(tree);
}
