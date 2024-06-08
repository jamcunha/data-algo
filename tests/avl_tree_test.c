#include <criterion/criterion.h>
#include "../data-structures/avl_tree/avl_tree.h"

avl_tree_t* tree;

void setup(void) {
    tree = avl_create();
}

void teardown(void) {
    avl_destroy(tree);
}

TestSuite(avl_tree, .init = setup, .fini = teardown);

Test(avl_tree, create) {
    cr_assert_not_null(tree, "tree should not be NULL");
    cr_assert_null(tree->root, "root should be NULL");
}

Test(avl_tree, insert) {
    avl_insert(tree, 1);
    cr_assert_not_null(tree->root, "root should not be NULL");
    cr_assert_eq(tree->root->data, 1, "root data should be 1, got %d", tree->root->data);
    cr_assert_null(tree->root->left, "root left should be NULL");
    cr_assert_null(tree->root->right, "root right should be NULL");
}

Test(avl_tree, insert_with_rotate_right) {
    avl_insert(tree, 3);
    avl_insert(tree, 2);
    avl_insert(tree, 1);

    cr_assert_not_null(tree->root, "root should not be NULL");
    cr_assert_eq(tree->root->data, 2, "root data should be 2, got %d", tree->root->data);

    cr_assert_not_null(tree->root->left, "root left should not be NULL");
    cr_assert_eq(tree->root->left->data, 1, "root left data should be 1, got %d", tree->root->left->data);

    cr_assert_not_null(tree->root->right, "root right should not be NULL");
    cr_assert_eq(tree->root->right->data, 3, "root right data should be 3, got %d", tree->root->right->data);

    cr_assert_null(tree->root->left->left, "root left left should be NULL");
    cr_assert_null(tree->root->left->right, "root left right should be NULL");

    cr_assert_null(tree->root->right->left, "root right left should be NULL");
    cr_assert_null(tree->root->right->right, "root right right should be NULL");
}

Test(avl_tree, insert_with_rotate_left_rotate_right) {
    avl_insert(tree, 3);
    avl_insert(tree, 1);
    avl_insert(tree, 2);

    cr_assert_not_null(tree->root, "root should not be NULL");
    cr_assert_eq(tree->root->data, 2, "root data should be 2, got %d", tree->root->data);

    cr_assert_not_null(tree->root->left, "root left should not be NULL");
    cr_assert_eq(tree->root->left->data, 1, "root left data should be 1, got %d", tree->root->left->data);

    cr_assert_not_null(tree->root->right, "root right should not be NULL");
    cr_assert_eq(tree->root->right->data, 3, "root right data should be 3, got %d", tree->root->right->data);

    cr_assert_null(tree->root->left->left, "root left left should be NULL");
    cr_assert_null(tree->root->left->right, "root left right should be NULL");

    cr_assert_null(tree->root->right->left, "root right left should be NULL");
    cr_assert_null(tree->root->right->right, "root right right should be NULL");
}

Test(avl_tree, insert_with_rotate_left) {
    avl_insert(tree, 1);
    avl_insert(tree, 2);
    avl_insert(tree, 3);

    cr_assert_not_null(tree->root, "root should not be NULL");
    cr_assert_eq(tree->root->data, 2, "root data should be 2, got %d", tree->root->data);

    cr_assert_not_null(tree->root->left, "root left should not be NULL");
    cr_assert_eq(tree->root->left->data, 1, "root left data should be 1, got %d", tree->root->left->data);

    cr_assert_not_null(tree->root->right, "root right should not be NULL");
    cr_assert_eq(tree->root->right->data, 3, "root right data should be 3, got %d", tree->root->right->data);

    cr_assert_null(tree->root->left->left, "root left left should be NULL");
    cr_assert_null(tree->root->left->right, "root left right should be NULL");

    cr_assert_null(tree->root->right->left, "root right left should be NULL");
    cr_assert_null(tree->root->right->right, "root right right should be NULL");
}

Test(avl_tree, insert_with_rotate_right_left) {
    avl_insert(tree, 1);
    avl_insert(tree, 3);
    avl_insert(tree, 2);

    cr_assert_not_null(tree->root, "root should not be NULL");
    cr_assert_eq(tree->root->data, 2, "root data should be 2, got %d", tree->root->data);

    cr_assert_not_null(tree->root->left, "root left should not be NULL");
    cr_assert_eq(tree->root->left->data, 1, "root left data should be 1, got %d", tree->root->left->data);

    cr_assert_not_null(tree->root->right, "root right should not be NULL");
    cr_assert_eq(tree->root->right->data, 3, "root right data should be 3, got %d", tree->root->right->data);

    cr_assert_null(tree->root->left->left, "root left left should be NULL");
    cr_assert_null(tree->root->left->right, "root left right should be NULL");

    cr_assert_null(tree->root->right->left, "root right left should be NULL");
    cr_assert_null(tree->root->right->right, "root right right should be NULL");
}

Test(avl_tree, delete) {
    avl_insert(tree, 1);
    avl_insert(tree, 2);
    avl_insert(tree, 3);

    avl_delete(tree, 1);

    cr_assert_not_null(tree->root, "root should not be NULL");
    cr_assert_eq(tree->root->data, 2, "root data should be 2, got %d", tree->root->data);

    cr_assert_null(tree->root->left, "root left should be NULL");

    cr_assert_not_null(tree->root->right, "root right should not be NULL");
    cr_assert_eq(tree->root->right->data, 3, "root right data should be 3, got %d", tree->root->right->data);
}

Test(avl_tree, delete_complex) {
    avl_insert(tree, 3);
    avl_insert(tree, 1);
    avl_insert(tree, 2);
    avl_insert(tree, 4);
    avl_insert(tree, 5);
    avl_insert(tree, 10);
    avl_insert(tree, 9);
    avl_insert(tree, 8);
    avl_insert(tree, 11);

    avl_delete(tree, 4);

    cr_assert_not_null(tree->root, "root should not be NULL");
    cr_assert_eq(tree->root->data, 5, "root data should be 5, got %d", tree->root->data);
    cr_assert_eq(tree->root->height, 3, "root height should be 3, got %d", tree->root->height);

    cr_assert_not_null(tree->root->left, "root->left should not be NULL");
    cr_assert_eq(tree->root->left->data, 2, "root->left data should be 2, got %d", tree->root->left->data);
    cr_assert_eq(tree->root->left->height, 1, "root->left height should be 1, got %d", tree->root->left->height);

    cr_assert_not_null(tree->root->right, "root->right should not be NULL");
    cr_assert_eq(tree->root->right->data, 9, "root->right data should be 2, got %d", tree->root->right->data);
    cr_assert_eq(tree->root->right->height, 2, "root->right height should be 1, got %d", tree->root->right->height);

    cr_assert_not_null(tree->root->left->left, "root->left->left should not be NULL");
    cr_assert_eq(tree->root->left->left->data, 1, "root->left->left data should be 1, got %d", tree->root->left->left->data);
    cr_assert_eq(tree->root->left->left->height, 0, "root->left->left height should be 0, got %d", tree->root->left->left->height);

    cr_assert_not_null(tree->root->left->right, "root->left->right should not be NULL");
    cr_assert_eq(tree->root->left->right->data, 3, "root->left->right data should be 3, got %d", tree->root->left->right->data);
    cr_assert_eq(tree->root->left->right->height, 0, "root->left->right height should be 0, got %d", tree->root->left->right->height);

    cr_assert_not_null(tree->root->right->left, "root->right->left should not be NULL");
    cr_assert_eq(tree->root->right->left->data, 8, "root->right->left data should be 8, got %d", tree->root->right->left->data);
    cr_assert_eq(tree->root->right->left->height, 0, "root->right->left height should be 0, got %d", tree->root->right->left->height);

    cr_assert_not_null(tree->root->right->right, "root->right->right should not be NULL");
    cr_assert_eq(tree->root->right->right->data, 10, "root->right->right data should be 10, got %d", tree->root->right->right->data);
    cr_assert_eq(tree->root->right->right->height, 1, "root->right->right height should be 1, got %d", tree->root->right->right->height);

    cr_assert_null(tree->root->left->left->left, "root->left->left->left should be NULL");
    cr_assert_null(tree->root->left->left->right, "root->left->left->right should be NULL");

    cr_assert_null(tree->root->left->right->left, "root->left->right->left should be NULL");
    cr_assert_null(tree->root->left->right->right, "root->left->right->right should be NULL");

    cr_assert_null(tree->root->right->left->left, "root->rigth->left->left should be NULL");
    cr_assert_null(tree->root->right->left->right, "root->right->left->right should be NULL");

    cr_assert_null(tree->root->right->right->left, "root->right->right->left should be NULL");

    cr_assert_not_null(tree->root->right->right->right, "root->right->right->right should not be NULL");
    cr_assert_eq(tree->root->right->right->right->data, 11, "root->right->right->right data should be 11, got %d", tree->root->right->right->right->data);
    cr_assert_eq(tree->root->right->right->right->height, 0, "root->right->right->right height should be 0, got %d", tree->root->right->right->right->height);

    cr_assert_null(tree->root->right->right->right->left, "root->right->right->right->left should be NULL");
    cr_assert_null(tree->root->right->right->right->right, "root->right->right->right->right should be NULL");
}

Test(avl_tree, search) {
    avl_insert(tree, 1);
    avl_insert(tree, 2);
    avl_insert(tree, 3);

    cr_assert(avl_search(tree, 1), "1 should be found in the tree");
    cr_assert_not(avl_search(tree, 4), "4 should not be found in the tree");
}
