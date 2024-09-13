#include <criterion/criterion.h>
#include "../data-structures/b_tree/b_tree.h"

#include <stdio.h>
// static void traverse(b_node_t* node, int depth) {
//     if (node != NULL) {
//         // Indentation
//         for (int i = 0; i < depth; ++i) {
//             printf("  ");
//         }
//
//         // Print keys
//         printf("[ ");
//         for (int i = 0; i < node->num_keys; ++i) {
//             printf("%d ", node->keys[i]);
//         }
//         printf("] (%d)%s\n", node->num_keys, node->is_leaf ? " [L]" : "");
//
//         // Traverse children
//         if (!node->is_leaf) {
//             for (int i = 0; i < node->num_keys + 1; ++i) {
//                 traverse(node->children[i], depth + 1);
//             }
//         }
//     }
// }

b_tree_t* tree = NULL;

void setup(void) {
    tree = b_tree_create();
}

void teardown(void) {
    b_tree_destroy(tree);
}

TestSuite(b_tree, .init = setup, .fini = teardown);

Test(b_tree, create_b_tree) {
    cr_assert_not_null(tree, "Tree should not be NULL");
    cr_assert_null(tree->root, "Root should be NULL");
}

// TODO: (or not) Add a test where a node to be splitted has max children
Test(b_tree, insert_b_tree) {
    b_tree_insert(tree, 1);
    b_tree_insert(tree, 2);
    b_tree_insert(tree, 3);
    b_tree_insert(tree, 4);
    b_tree_insert(tree, 5);

    cr_assert_not_null(tree->root, "Root should not be NULL");
    cr_assert(tree->root->is_leaf, "Root should be a leaf node");
    cr_assert_eq(tree->root->num_keys, 5, "Root should have 4 key, have %d", tree->root->num_keys);

    for (int i = 0; i < tree->root->num_keys; ++i) {
        cr_assert_eq(tree->root->keys[i], i + 1, "Root should have key %d, have %d",
                     i + 1, tree->root->keys[i]);
    }

    for (int i = 0; i < MAX_KEYS + 1; ++i) {
        cr_assert_null(tree->root->children[i], "Child node should be NULL");
    }

    b_tree_insert(tree, 6);

    cr_assert_not_null(tree->root, "Root should not be NULL");
    cr_assert_not(tree->root->is_leaf, "Root should not be a leaf node");
    cr_assert_eq(tree->root->num_keys, 1, "Root should have 1 key, have %d", tree->root->num_keys);
    cr_assert_eq(tree->root->keys[0], 3, "Root should have key 3, have %d", tree->root->keys[0]);

    cr_assert_not_null(tree->root->children[0], "Child node should not be NULL");
    cr_assert(tree->root->children[0]->is_leaf, "Child node should be a leaf node");
    cr_assert_eq(tree->root->children[0]->num_keys, 2, "Child node should have 2 keys, have %d", tree->root->children[0]->num_keys);

    cr_assert_eq(tree->root->children[0]->keys[0], 1, "Child node should have key 1, have %d", tree->root->children[0]->keys[0]);
    cr_assert_eq(tree->root->children[0]->keys[1], 2, "Child node should have key 2, have %d", tree->root->children[0]->keys[1]);

    // confirm it's a leaf
    for (int i = 0; i < MAX_KEYS + 1; ++i) {
        cr_assert_null(tree->root->children[0]->children[i], "Child node should be NULL");
    }

    cr_assert_not_null(tree->root->children[1], "Child node should not be NULL");
    cr_assert(tree->root->children[1]->is_leaf, "Child node should be a leaf node");
    cr_assert_eq(tree->root->children[1]->num_keys, 3, "Child node should have 2 keys, have %d", tree->root->children[1]->num_keys);

    cr_assert_eq(tree->root->children[1]->keys[0], 4, "Child node should have key 4, have %d", tree->root->children[1]->keys[0]);
    cr_assert_eq(tree->root->children[1]->keys[1], 5, "Child node should have key 5, have %d", tree->root->children[1]->keys[1]);
    cr_assert_eq(tree->root->children[1]->keys[2], 6, "Child node should have key 6, have %d", tree->root->children[1]->keys[2]);

    // confirm it's a leaf
    for (int i = 0; i < MAX_KEYS + 1; ++i) {
        cr_assert_null(tree->root->children[1]->children[i], "Child node should be NULL");
    }

    // Add to fill up the bigger child of root
    b_tree_insert(tree, 7);
    b_tree_insert(tree, 8);

    b_tree_insert(tree, 9);

    cr_assert_not_null(tree->root, "Root should not be NULL");
    cr_assert_not(tree->root->is_leaf, "Root should not be a leaf node");
    cr_assert_eq(tree->root->num_keys, 2, "Root should have 1 key, have %d", tree->root->num_keys);
    cr_assert_eq(tree->root->keys[0], 3, "Root should have key 3, have %d", tree->root->keys[0]);
    cr_assert_eq(tree->root->keys[1], 6, "Root should have key 6, have %d", tree->root->keys[1]);

    cr_assert_not_null(tree->root->children[0], "Child node should not be NULL");
    cr_assert(tree->root->children[0]->is_leaf, "Child node should be a leaf node");
    cr_assert_eq(tree->root->children[0]->num_keys, 2, "Child node should have 2 keys, have %d", tree->root->children[0]->num_keys);

    cr_assert_eq(tree->root->children[0]->keys[0], 1, "Child node should have key 1, have %d", tree->root->children[0]->keys[0]);
    cr_assert_eq(tree->root->children[0]->keys[1], 2, "Child node should have key 2, have %d", tree->root->children[0]->keys[1]);

    cr_assert_not_null(tree->root->children[1], "Child node should not be NULL");
    cr_assert(tree->root->children[1]->is_leaf, "Child node should be a leaf node");
    cr_assert_eq(tree->root->children[1]->num_keys, 2, "Child node should have 2 keys, have %d", tree->root->children[1]->num_keys);

    cr_assert_eq(tree->root->children[1]->keys[0], 4, "Child node should have key 4, have %d", tree->root->children[1]->keys[0]);
    cr_assert_eq(tree->root->children[1]->keys[1], 5, "Child node should have key 5, have %d", tree->root->children[1]->keys[1]);

    cr_assert_not_null(tree->root->children[2], "Child node should not be NULL");
    cr_assert(tree->root->children[2]->is_leaf, "Child node should be a leaf node");
    cr_assert_eq(tree->root->children[2]->num_keys, 3, "Child node should have 3 keys, have %d", tree->root->children[2]->num_keys);

    cr_assert_eq(tree->root->children[2]->keys[0], 7, "Child node should have key 7, have %d", tree->root->children[2]->keys[0]);
    cr_assert_eq(tree->root->children[2]->keys[1], 8, "Child node should have key 8, have %d", tree->root->children[2]->keys[1]);
    cr_assert_eq(tree->root->children[2]->keys[2], 9, "Child node should have key 9, have %d", tree->root->children[2]->keys[2]);
}

// TODO: Write the B-Tree delete test
Test(b_tree, delete_b_tree) {
    printf("Need to write a test for B-Tree delete\n");
}

Test(b_tree, search_b_tree) {
    b_tree_insert(tree, 1);
    b_tree_insert(tree, 2);
    b_tree_insert(tree, 3);
    b_tree_insert(tree, 4);
    b_tree_insert(tree, 5);

    cr_assert(b_tree_search(tree, 1), "Key 1 should be found");
    cr_assert(b_tree_search(tree, 2), "Key 2 should be found");
    cr_assert(b_tree_search(tree, 3), "Key 3 should be found");
    cr_assert(b_tree_search(tree, 4), "Key 4 should be found");
    cr_assert(b_tree_search(tree, 5), "Key 5 should be found");
    cr_assert_not(b_tree_search(tree, 6), "Key 6 should not be found");
}
