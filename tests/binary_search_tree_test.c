#include <criterion/criterion.h>
#include "../data-structures/binary_search_tree/binary_search_tree.h"

bst_t* tree;

void setup(void) {
    tree = bst_create();
}

void teardown(void) {
    bst_destroy(tree);
}

TestSuite(binary_search_tree, .init = setup, .fini = teardown);

Test(binary_search_tree, create_tree) {
    cr_assert_not_null(tree, "Tree should not be NULL");
    cr_assert_null(tree->root, "Root should be NULL");
}

Test(binary_search_tree, insert) {
    bst_insert(tree, 5);
    bst_insert(tree, 2);
    bst_insert(tree, 4);

    bst_node_t* node = tree->root;

    cr_assert_not_null(node, "Node should not be NULL");
    cr_assert_eq(node->data, 5, "Node data should be 5, got %d", node->data);
    cr_assert_not_null(node->left, "Node left child should not be NULL");
    cr_assert_eq(node->left->data, 2, "Node left child data should be 2, got %d", node->left->data);
    cr_assert_null(node->right, "Node right child should be NULL");

    node = node->left;
    cr_assert_eq(node->data, 2, "Node data should be 2, got %d", node->data);
    cr_assert_null(node->left, "Node left child should be NULL");
    cr_assert_not_null(node->right, "Node right child should not be NULL");
    cr_assert_eq(node->right->data, 4, "Node right child data should be 4, got %d", node->right->data);
}

Test(binary_search_tree, remove) {
    bst_insert(tree, 5);
    bst_insert(tree, 2);
    bst_insert(tree, 10);
    bst_insert(tree, 7);

    bst_remove(tree, 10);

    bst_node_t* node = tree->root;

    cr_assert_not_null(node, "Node should not be NULL");
    cr_assert_eq(node->data, 5, "Node data should be 5, got %d", node->data);
    cr_assert_not_null(node->left, "Node left child should not be NULL");
    cr_assert_eq(node->left->data, 2, "Node left child data should be 2, got %d", node->left->data);
    cr_assert_not_null(node->right, "Node right child should not be NULL");
    cr_assert_eq(node->right->data, 7, "Node right child data should be 7, got %d", node->right->data);
}

Test(binary_search_tree, search) {
    bst_insert(tree, 5);
    bst_insert(tree, 2);
    bst_insert(tree, 4);

    cr_assert(bst_search(tree, 5), "Tree should contain 5");
    cr_assert(bst_search(tree, 2), "Tree should contain 2");
    cr_assert(bst_search(tree, 4), "Tree should contain 4");
    cr_assert_not(bst_search(tree, 3), "Tree should not contain 3");
}

Test(binary_search_tree, min) {
    bst_insert(tree, 5);
    bst_insert(tree, 2);
    bst_insert(tree, 4);

    int min = bst_min(tree);
    cr_assert_eq(min, 2, "Min should be 2, got %d", min);
}

Test(binary_search_tree, max) {
    bst_insert(tree, 5);
    bst_insert(tree, 2);
    bst_insert(tree, 4);

    int max = bst_max(tree);
    cr_assert_eq(max, 5, "Max should be 5, got %d", max);
}

Test(binary_search_tree, inorder) {
    bst_insert(tree, 5);
    bst_insert(tree, 2);
    bst_insert(tree, 4);
    bst_insert(tree, 10);
    bst_insert(tree, 7);

    int* inorder = bst_inorder(tree);
    cr_assert_eq(inorder[0], 2, "Inorder[0] should be 2, got %d", inorder[0]);
    cr_assert_eq(inorder[1], 4, "Inorder[1] should be 4, got %d", inorder[1]);
    cr_assert_eq(inorder[2], 5, "Inorder[2] should be 5, got %d", inorder[2]);
    cr_assert_eq(inorder[3], 7, "Inorder[3] should be 7, got %d", inorder[3]);
    cr_assert_eq(inorder[4], 10, "Inorder[4] should be 10, got %d", inorder[4]);

    free(inorder);
}

Test(binary_search_tree, preorder) {
    bst_insert(tree, 5);
    bst_insert(tree, 2);
    bst_insert(tree, 4);
    bst_insert(tree, 10);
    bst_insert(tree, 7);

    int* preorder = bst_preorder(tree);
    cr_assert_eq(preorder[0], 5, "Preorder[0] should be 5, got %d", preorder[0]);
    cr_assert_eq(preorder[1], 2, "Preorder[1] should be 2, got %d", preorder[1]);
    cr_assert_eq(preorder[2], 4, "Preorder[2] should be 4, got %d", preorder[2]);
    cr_assert_eq(preorder[3], 10, "Preorder[3] should be 10, got %d", preorder[3]);
    cr_assert_eq(preorder[4], 7, "Preorder[4] should be 7, got %d", preorder[4]);

    free(preorder);
}

Test(binary_search_tree, postorder) {
    bst_insert(tree, 5);
    bst_insert(tree, 2);
    bst_insert(tree, 4);
    bst_insert(tree, 10);
    bst_insert(tree, 7);

    int* postorder = bst_postorder(tree);
    cr_assert_eq(postorder[0], 4, "Postorder[0] should be 4, got %d", postorder[0]);
    cr_assert_eq(postorder[1], 2, "Postorder[1] should be 2, got %d", postorder[1]);
    cr_assert_eq(postorder[2], 7, "Postorder[2] should be 7, got %d", postorder[2]);
    cr_assert_eq(postorder[3], 10, "Postorder[3] should be 10, got %d", postorder[3]);
    cr_assert_eq(postorder[4], 5, "Postorder[4] should be 5, got %d", postorder[4]);

    free(postorder);
}
