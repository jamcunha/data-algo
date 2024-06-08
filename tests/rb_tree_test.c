#include <criterion/criterion.h>
#include "../data-structures/rb_tree/rb_tree.h"

// TODO: Add more in-depth tests

rb_tree_t* tree;

void setup(void) {
    tree = rb_create();
}

void teardown(void) {
    rb_destroy(tree);
}

TestSuite(rb_tree, .init = setup, .fini = teardown);

Test(rb_tree, create) {
    cr_assert_not_null(tree);
    cr_assert_null(tree->root);
}

Test(rb_tree, insert) {
    rb_insert(tree, 10);

    cr_assert_not_null(tree->root);
    cr_assert_eq(tree->root->data, 10);
    cr_assert_eq(tree->root->color, BLACK);
}

Test(rb_tree, insert_duplicate) {
    rb_insert(tree, 10);
    rb_insert(tree, 10);

    cr_assert_not_null(tree->root);
    cr_assert_eq(tree->root->data, 10);
    cr_assert_eq(tree->root->color, BLACK);
    cr_assert_null(tree->root->left);
    cr_assert_null(tree->root->right);
}

Test(rb_tree, insert_with_fixup) {
    rb_insert(tree, 5);
    rb_insert(tree, 10);
    rb_insert(tree, 15);
    rb_insert(tree, 20);
    rb_insert(tree, 25);
    rb_insert(tree, 30);
    rb_insert(tree, 35);

    cr_assert_not_null(tree->root);
    cr_assert_eq(tree->root->data, 10,
                 "expected: 10, got: %d", tree->root->data);
    cr_assert_eq(tree->root->color, BLACK,
                 "expected: BLACK, got: %s", tree->root->color ? "RED" : "BLACK");

    cr_assert_not_null(tree->root->left);
    cr_assert_eq(tree->root->left->data, 5,
                 "expected: 5, got: %d", tree->root->left->data);
    cr_assert_eq(tree->root->left->color, BLACK,
                 "expected: BLACK, got: %s", tree->root->left->color ? "RED" : "BLACK");

    cr_assert_not_null(tree->root->right);
    cr_assert_eq(tree->root->right->data, 20,
                 "expected: 20, got: %d", tree->root->right->data);
    cr_assert_eq(tree->root->right->color, RED,
                 "expected: RED, got: %s", tree->root->right->color ? "RED" : "BLACK");

    cr_assert_not_null(tree->root->right->left);
    cr_assert_eq(tree->root->right->left->data, 15,
                 "expected: 15, got: %d", tree->root->right->left->data);
    cr_assert_eq(tree->root->right->left->color, BLACK,
                 "expected: BLACK, got: %s", tree->root->right->left->color ? "RED" : "BLACK");

    cr_assert_not_null(tree->root->right->right);
    cr_assert_eq(tree->root->right->right->data, 30,
                 "expected: 25, got: %d", tree->root->right->right->data);
    cr_assert_eq(tree->root->right->right->color, BLACK,
                 "expected: BLACK, got: %s", tree->root->right->right->color ? "RED" : "BLACK");

    cr_assert_not_null(tree->root->right->right->left);
    cr_assert_eq(tree->root->right->right->left->data, 25,
                 "expected: 25, got: %d", tree->root->right->right->left->data);
    cr_assert_eq(tree->root->right->right->left->color, RED,
                 "expected: RED, got: %s", tree->root->right->right->left->color ? "RED" : "BLACK");

    cr_assert_not_null(tree->root->right->right->right);
    cr_assert_eq(tree->root->right->right->right->data, 35,
                 "expected: 35, got: %d", tree->root->right->right->right->data);
    cr_assert_eq(tree->root->right->right->right->color, RED,
                 "expected: RED, got: %s", tree->root->right->right->right->color ? "RED" : "BLACK");
}

Test(rb_tree, delete) {
    rb_insert(tree, 5);
    rb_insert(tree, 10);
    rb_insert(tree, 15);
    rb_insert(tree, 20);
    rb_insert(tree, 25);
    rb_insert(tree, 30);
    rb_insert(tree, 35);

    rb_delete(tree, 5);

    cr_assert_not_null(tree->root);
    cr_assert_eq(tree->root->data, 20,
                 "expected: 20, got: %d", tree->root->data);
    cr_assert_eq(tree->root->color, BLACK,
                 "expected: BLACK, got: %s", tree->root->color ? "RED" : "BLACK");

    cr_assert_not_null(tree->root->left);
    cr_assert_eq(tree->root->left->data, 10,
                 "expected: 10, got: %d", tree->root->left->data);
    cr_assert_eq(tree->root->left->color, BLACK,
                 "expected: BLACK, got: %s", tree->root->left->color ? "RED" : "BLACK");

    cr_assert_not_null(tree->root->right);
    cr_assert_eq(tree->root->right->data, 30,
                 "expected: 30, got: %d", tree->root->right->data);
    cr_assert_eq(tree->root->right->color, BLACK,
                 "expected: BLACK, got: %s", tree->root->right->color ? "RED" : "BLACK");

    cr_assert_null(tree->root->left->left);

    cr_assert_not_null(tree->root->left->right);
    cr_assert_eq(tree->root->left->right->data, 15,
                 "expected: 15, got: %d", tree->root->left->right->data);
    cr_assert_eq(tree->root->left->right->color, RED,
                 "expected: RED, got: %s", tree->root->left->right->color ? "RED" : "BLACK");

    cr_assert_not_null(tree->root->right->left);
    cr_assert_eq(tree->root->right->left->data, 25,
                 "expected: 25, got: %d", tree->root->right->left->data);
    cr_assert_eq(tree->root->right->left->color, RED,
                 "expected: RED, got: %s", tree->root->right->left->color ? "RED" : "BLACK");

    cr_assert_not_null(tree->root->right->right);
    cr_assert_eq(tree->root->right->right->data, 35,
                 "expected: 35, got: %d", tree->root->right->right->data);
    cr_assert_eq(tree->root->right->right->color, RED,
                 "expected: RED, got: %s", tree->root->right->right->color ? "RED" : "BLACK");

    cr_assert_not(rb_search(tree, 5));
}

Test(rb_tree, search) {
    rb_insert(tree, 10);
    rb_insert(tree, 5);
    rb_insert(tree, 15);

    cr_assert(rb_search(tree, 10));
    cr_assert(rb_search(tree, 5));
    cr_assert(rb_search(tree, 15));
    cr_assert_not(rb_search(tree, 20));
}
