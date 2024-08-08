#include <criterion/criterion.h>
#include "../data-structures/interval_tree/interval_tree.h"
#include "criterion/internal/assert.h"

interval_tree_t* tree;

void setup(void) {
    tree = interval_tree_create();
}

void teardown(void) {
    interval_tree_destroy(tree);
}

TestSuite(interval_tree, .init = setup, .fini = teardown);

Test(interval_tree, create_tree) {
    cr_assert_not_null(tree, "Tree should not be NULL");
    cr_assert_null(tree->root, "Root should be NULL");
}

Test(interval_tree, insert) {
    interval_tree_insert(tree, 2, 4);
    interval_tree_insert(tree, 10, 12);
    interval_tree_insert(tree, 5, 7);
    interval_tree_insert(tree, 15, 17);

    interval_tree_node_t* node = tree->root;

    cr_assert_not_null(node, "Node should not be NULL");
    cr_assert_eq(node->interval.low, 2, "Node interval low should be 2, got %d", node->interval.low);
    cr_assert_eq(node->interval.high, 4, "Node interval high should be 4, got %d", node->interval.high);
    cr_assert_null(node->left, "Node left child should be NULL");
    cr_assert_not_null(node->right, "Node right child should not be NULL");

    node = node->right;

    cr_assert_eq(node->interval.low, 10, "Node interval low should be 10, got %d", node->interval.low);
    cr_assert_eq(node->interval.high, 12, "Node interval high should be 12, got %d", node->interval.high);
    cr_assert_not_null(node->left, "Node left child should not be NULL");
    cr_assert_eq(node->left->interval.low, 5, "Node left child interval low should be 5, got %d", node->left->interval.low);
    cr_assert_eq(node->left->interval.high, 7, "Node left child interval high should be 7, got %d", node->left->interval.high);
    cr_assert_not_null(node->right, "Node right child should be NULL");
    cr_assert_eq(node->right->interval.low, 15, "Node right child interval low should be 15, got %d", node->right->interval.low);
    cr_assert_eq(node->right->interval.high, 17, "Node right child interval high should be 17, got %d", node->right->interval.high);

    cr_assert_null(node->left->left, "Node left child left child should be NULL");
    cr_assert_null(node->left->right, "Node left child right child should be NULL");
    cr_assert_null(node->right->left, "Node right child left child should be NULL");
    cr_assert_null(node->right->right, "Node right child right child should be NULL");
}

Test(interval_tree, search_interval) {
    interval_tree_insert(tree, 2, 4);
    interval_tree_insert(tree, 10, 12);
    interval_tree_insert(tree, 5, 7);
    interval_tree_insert(tree, 15, 17);

    int num_intervals;
    interval_t* intervals = interval_tree_search_interval(tree, 20, 25, &num_intervals);

    cr_assert_eq(num_intervals, 0, "Number of intervals should be 0, got %d", num_intervals);

    free(intervals);

    intervals = interval_tree_search_interval(tree, 3, 7, &num_intervals);

    cr_assert_eq(num_intervals, 2, "Number of intervals should be 2, got %d", num_intervals);
    cr_assert_eq(intervals[0].low, 2, "First interval low should be 2, got %d", intervals[0].low);
    cr_assert_eq(intervals[0].high, 4, "First interval high should be 4, got %d", intervals[0].high);
    cr_assert_eq(intervals[1].low, 5, "Second interval low should be 5, got %d", intervals[1].low);
    cr_assert_eq(intervals[1].high, 7, "Second interval high should be 7, got %d", intervals[1].high);

    free(intervals);
}

Test(interval_tree, search_point) {
    interval_tree_insert(tree, 2, 4);
    interval_tree_insert(tree, 5, 7);
    interval_tree_insert(tree, 10, 12);
    interval_tree_insert(tree, 4, 8);

    int num_intervals;
    interval_t* intervals = interval_tree_search_point(tree, 20, &num_intervals);

    cr_assert_eq(num_intervals, 0, "Number of intervals should be 0, got %d", num_intervals);

    free(intervals);

    intervals = interval_tree_search_point(tree, 6, &num_intervals);

    cr_assert_eq(num_intervals, 2, "Number of intervals should be 2, got %d", num_intervals);
    cr_assert_eq(intervals[0].low, 5, "First interval low should be 5, got %d", intervals[0].low);
    cr_assert_eq(intervals[0].high, 7, "First interval high should be 7, got %d", intervals[0].high);
    cr_assert_eq(intervals[1].low, 4, "Second interval low should be 4, got %d", intervals[1].low);
    cr_assert_eq(intervals[1].high, 8, "Second interval high should be 8, got %d", intervals[1].high);

    free(intervals);
}
