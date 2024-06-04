#include <criterion/criterion.h>
#include "../data-structures/single_linked_list/single_linked_list.h"

sll_t* list;

void test_setup(void) {
    list = sll_create();
}

void test_teardown(void) {
    sll_destroy(list);
}

TestSuite(single_linked_list, .init = test_setup, .fini = test_teardown);

Test(single_linked_list, sll_create) {
    cr_assert_not_null(list, "sll_create() failed");
    cr_assert_null(list->head, "sll_create() failed");
    cr_assert_null(list->tail, "sll_create() failed");
    cr_assert_eq(list->size, 0, "sll_create() failed");
}

Test(single_linked_list, sll_prepend) {
    sll_prepend(list, 1);
    cr_assert_eq(list->head->data, 1, "sll_prepend() failed");
    cr_assert_eq(list->tail->data, 1, "sll_prepend() failed");
    cr_assert_eq(list->size, 1, "sll_prepend() failed");

    sll_prepend(list, 2);
    cr_assert_eq(list->head->data, 2, "sll_prepend() failed");
    cr_assert_eq(list->tail->data, 1, "sll_prepend() failed");
    cr_assert_eq(list->size, 2, "sll_prepend() failed");
}

Test(single_linked_list, sll_insert) {
    sll_insert(list, 1);
    cr_assert_eq(list->head->data, 1, "sll_insert() failed");
    cr_assert_eq(list->tail->data, 1, "sll_insert() failed");
    cr_assert_eq(list->size, 1, "sll_insert() failed");

    sll_insert(list, 2);
    cr_assert_eq(list->head->data, 1, "sll_insert() failed");
    cr_assert_eq(list->tail->data, 2, "sll_insert() failed");
    cr_assert_eq(list->size, 2, "sll_insert() failed");
}

Test(single_linked_list, sll_delete) {
    sll_insert(list, 1);
    sll_insert(list, 2);
    sll_insert(list, 3);

    sll_delete(list, 2);
    cr_assert_eq(list->head->data, 1, "sll_delete() failed");
    cr_assert_eq(list->tail->data, 3, "sll_delete() failed");
    cr_assert_eq(list->size, 2, "sll_delete() failed");

    sll_delete(list, 1);
    cr_assert_eq(list->head->data, 3, "sll_delete() failed");
    cr_assert_eq(list->tail->data, 3, "sll_delete() failed");
    cr_assert_eq(list->size, 1, "sll_delete() failed");

    sll_delete(list, 3);
    cr_assert_null(list->head, "sll_delete() failed");
    cr_assert_null(list->tail, "sll_delete() failed");
    cr_assert_eq(list->size, 0, "sll_delete() failed");
}

Test(single_linked_list, sll_delete_node) {
    sll_insert(list, 1);
    sll_insert(list, 2);
    sll_insert(list, 3);

    sll_node_t* node = sll_find(list, 2);
    sll_delete_node(list, node);
    cr_assert_eq(list->head->data, 1, "sll_delete_node() failed");
    cr_assert_eq(list->tail->data, 3, "sll_delete_node() failed");
    cr_assert_eq(list->size, 2, "sll_delete_node() failed");
}

Test(single_linked_list, sll_get) {
    sll_insert(list, 1);
    sll_insert(list, 2);
    sll_insert(list, 3);

    sll_node_t* node = sll_get(list, 0);
    cr_assert_not_null(node, "sll_get() failed");
    cr_assert_eq(node->data, 1, "sll_get() failed");

    node = sll_get(list, 1);
    cr_assert_not_null(node, "sll_get() failed");
    cr_assert_eq(node->data, 2, "sll_get() failed");

    node = sll_get(list, 2);
    cr_assert_not_null(node, "sll_get() failed");
    cr_assert_eq(node->data, 3, "sll_get() failed");

    node = sll_get(list, 3);
    cr_assert_null(node, "sll_get() failed");
}

Test(single_linked_list, sll_find) {
    sll_insert(list, 1);
    sll_insert(list, 2);
    sll_insert(list, 3);

    sll_node_t* node = sll_find(list, 2);
    cr_assert_not_null(node, "sll_find() failed");
    cr_assert_eq(node->data, 2, "sll_find() failed");

    node = sll_find(list, 4);
    cr_assert_null(node, "sll_find() failed");
}
