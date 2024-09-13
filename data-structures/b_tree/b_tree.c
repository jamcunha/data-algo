#include "b_tree.h"
#include "time.h"
#include <stdlib.h>

static b_node_t* b_node_create(bool is_leaf) {
    b_node_t* node = (b_node_t*)malloc(sizeof(b_node_t));
    node->num_keys = 0;
    node->is_leaf = is_leaf;

    for (int i = 0; i < MAX_KEYS; ++i) {
        node->children[i] = NULL;
    }

    return node;
}

static void destroy(b_node_t* node) {
    if (node) {
        if (!node->is_leaf) {
            for (int i = 0; i < node->num_keys + 1; ++i) {
                destroy(node->children[i]);
            }
        }
        free(node);
    }
}

static b_node_t* search(b_node_t* node, int key) {
    if (!node) {
        return NULL;
    }

    int idx = 0;
    while (idx < node->num_keys && key > node->keys[idx]) {
        ++idx;
    }

    if (idx < node->num_keys && key == node->keys[idx]) {
        return node;
    }

    if (node->is_leaf) {
        return NULL;
    }

    return search(node->children[idx], key);
}

static void split(b_node_t* parent, int idx) {
    int t = (MAX_KEYS + 1) / 2;
    b_node_t* child = parent->children[idx];

    // Create a new node to take half of the child node's keys
    b_node_t* new_node = b_node_create(child->is_leaf);
    new_node->num_keys = t - 1;

    // New node gets the right half of the child node's keys ...
    for (int i = 0; i < t - 1; ++i) {
        new_node->keys[i] = child->keys[i + t];
    }

    // ... and get's the right half of the child node's children
    if (!child->is_leaf) {
        for (int i = 0; i < t; ++i) {
            new_node->children[i] = child->children[i + t];
        }
    }

    child->num_keys = t - 1;

    // Shift parent's children to the right
    for (int i = parent->num_keys; i > idx; --i) {
        parent->children[i + 1] = parent->children[i];
    }

    parent->children[idx + 1] = new_node;

    // Shift parent's keys to the right
    for (int i = parent->num_keys - 1; i >= idx; --i) {
        parent->keys[i + 1] = parent->keys[i];
    }

    // Move the child's median key to the parent node
    parent->keys[idx] = child->keys[t - 1];
    ++parent->num_keys;
}

static void insert_non_full(b_node_t* node, int key) {
    int idx = node->num_keys - 1;

    if (node->is_leaf) {
        // Insert into a leaf

        // Shift keys to make room for the new key
        while (idx >= 0 && key < node->keys[idx]) {
            node->keys[idx + 1] = node->keys[idx];
            --idx;
        }

        // Insert key
        node->keys[idx + 1] = key;
        ++node->num_keys;
    } else {
        // Find the child to insert the key
        while (idx >= 0 && key < node->keys[idx]) {
            --idx;
        }
        ++idx;

        // Split the child if it's full
        if (node->children[idx]->num_keys == MAX_KEYS) {
            split(node, idx);

            // Determine if the key should be inserted on the new child (from the split)
            if (key > node->keys[idx]) {
                ++idx;
            }
        }

        insert_non_full(node->children[idx], key);
    }
}

static b_node_t* getPredNode(b_node_t* node) {
    while (!node->is_leaf) {
        node = node->children[node->num_keys];
    }

    return node;
}

static b_node_t* getPredSucc(b_node_t* node) {
    while (!node->is_leaf) {
        node = node->children[0];
    }

    return node;
}

static void merge(b_node_t* node, int idx) {
    int t = (MAX_KEYS + 1) / 2;

    b_node_t* child = node->children[idx];
    b_node_t* sibling = node->children[idx + 1];

    // Move key from parent to child
    child->keys[t - 1] = node->keys[idx];

    // Move keys from sibling to child
    for (int i = 0; i < sibling->num_keys; ++i) {
        child->keys[i + t] = sibling->keys[i];
    }

    // Move children from sibling to child
    if (!child->is_leaf) {
        for (int i = 0; i <= sibling->num_keys; ++i) {
            child->children[i + t] = sibling->children[i];
        }
    }

    // Shift keys in parent to the left
    for (int i = idx; i < node->num_keys - 1; ++i) {
        node->keys[i] = node->keys[i + 1];
    }

    // Shift children in parent to the left
    for (int i = idx + 1; i < node->num_keys; ++i) {
        node->children[i] = node->children[i + 1];
    }

    child->num_keys += sibling->num_keys + 1;
    node->num_keys--;
    
    free(sibling);
}

static void delete(b_node_t* node, int key) {
    int idx = 0;
    while (idx < node->num_keys && node->keys[idx] < key) {
        ++idx;
    }

    if (node->is_leaf) {
        // Case 1: Node is leaf, if key is present, delete it
        if (idx < node->num_keys && node->keys[idx] == key) {
            for (int i = idx; i < node->num_keys - 1; ++i) {
                node->keys[i] = node->keys[i + 1];
            }
            --node->num_keys;
        }

        return;
    }

    int t = (MAX_KEYS + 1) / 2;

    // Case 2: Node is not leaf and key is present
    if (idx < node->num_keys && node->keys[idx] == key) {
        // Case 2.a: If the child that precedes key (C[idx]) has at least t keys
        if (node->children[idx]->num_keys >= t) {
            // Find the node with the predecessor of key
            b_node_t* pred = getPredNode(node->children[idx]);

            // Replace key with pred
            node->keys[idx] = pred->keys[pred->num_keys - 1];
            delete(node->children[idx], pred->keys[pred->num_keys - 1]);

        // Case 2.b: If the child that succeeds key (C[idx + 1]) has at least t keys
        } else if (node->children[idx + 1]->num_keys >= t) {
            // Find the node with the successor of key
            b_node_t* succ = getPredSucc(node->children[idx + 1]);

            // Replace key with succ
            node->keys[idx] = succ->keys[0];
            delete(node->children[idx + 1], succ->keys[0]);

        // Case 2.c: Both C[idx] and C[idx + 1] have t - 1 keys
        } else {
            // Merge C[idx] and C[idx + 1] into C[idx] and delete key
            merge(node, idx);
            delete(node->children[idx], node->children[idx]->keys[t - 1]);
        }

    // Case 3: Node does not contain the key
    } else {
        // Determine if the key is in the last child
        // Needs to be stored because node may change after borrowing and merging
        bool flag = idx == node->num_keys;

        b_node_t* child = node->children[idx];

        // Determine if the child has at least t keys
        if (child->num_keys < t) {
            // Case 3.a: If the child has less than t keys and a sibling has at least t keys
            if (idx > 0 && node->children[idx - 1]->num_keys >= t) {
                b_node_t* sibling = node->children[idx - 1];

                // Shift keys in child to the right
                for (int i = child->num_keys - 1; i >= 0; --i) {
                    child->keys[i + 1] = child->keys[i];
                }

                if (!child->is_leaf) {
                    // Shift children in child to the right
                    for (int i = child->num_keys; i >= 0; --i) {
                        child->children[i + 1] = child->children[i];
                    }
                }

                child->keys[0] = node->keys[idx - 1];

                if (!child->is_leaf) {
                    child->children[0] = sibling->children[sibling->num_keys];
                }

                node->keys[idx - 1] = sibling->keys[sibling->num_keys - 1];

                ++child->num_keys;
                --sibling->num_keys;

            // Case 3.a
            } else if (idx < node->num_keys && node->children[idx + 1]->num_keys >= t) {
                b_node_t* sibling = node->children[idx + 1];

                child->keys[child->num_keys] = node->keys[idx];

                if (!child->is_leaf) {
                    child->children[child->num_keys + 1] = sibling->children[0];
                }

                node->keys[idx] = sibling->keys[0];

                for (int i = 1; i < sibling->num_keys; ++i) {
                    sibling->keys[i - 1] = sibling->keys[i];
                }

                if (!sibling->is_leaf) {
                    for (int i = 1; i <= sibling->num_keys; ++i) {
                        sibling->children[i - 1] = sibling->children[i];
                    }
                }

                ++child->num_keys;
                --sibling->num_keys;

            // Case 3.b: Both child and its siblings have t - 1 keys, merge child with a sibling with a value of node as median
            } else {
                if (idx < node->num_keys) {
                    merge(node, idx);
                } else {
                    merge(node, idx - 1);
                }
            }
        } else if (flag && idx > node->num_keys) {
            delete(node->children[idx - 1], key);
        } else {
            delete(node->children[idx], key);
        }
    }
}

b_tree_t* b_tree_create(void) {
    b_tree_t* tree = (b_tree_t*)malloc(sizeof(b_tree_t));
    tree->root = NULL;
    return tree;
}

void b_tree_insert(b_tree_t* tree, int key) {
    if (!tree) {
        return;
    }

    if (!tree->root) {
        tree->root = b_node_create(true);
        tree->root->keys[0] = key;
        tree->root->num_keys = 1;
        return;
    }

    if (tree->root->num_keys == MAX_KEYS) {
        b_node_t* new_root = b_node_create(false);
        new_root->children[0] = tree->root;
        tree->root = new_root;
        split(new_root, 0);
    }

    insert_non_full(tree->root, key);
}

void b_tree_delete(b_tree_t* tree, int key) {
    if (!tree) { return; }
    if (!tree->root) { return; }

    delete(tree->root, key);

    if (tree->root->num_keys == 0) {
        b_node_t* tmp = tree->root;
        tree->root = tree->root->children[0];
        free(tmp);
    }
}

bool b_tree_search(b_tree_t* tree, int key) {
    if (!tree) {
        return false;
    }

    return search(tree->root, key) != NULL;
}

void b_tree_destroy(b_tree_t* tree) {
    if (!tree) {
        return;
    }

    destroy(tree->root);
    free(tree);
}
