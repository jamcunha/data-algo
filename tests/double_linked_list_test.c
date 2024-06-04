#include <criterion/criterion.h>
#include "../data-structures/double_linked_list/double_linked_list.h"

dll_t* list;

void test_setup(void) {
    list = dll_create();
}

void test_teardown(void) {
    dll_destroy(list);
}

TestSuite(double_linked_list, .init = test_setup, .fini = test_teardown);

Test(double_linked_list, dll_create) {
    cr_assert_not_null(list, "dll_create() failed");
    cr_assert_null(list->head, "dll_create() failed");
    cr_assert_null(list->tail, "dll_create() failed");
    cr_assert_eq(list->size, 0, "dll_create() failed");
}

Test(double_linked_list, dll_prepend) {
    dll_prepend(list, 1);
    cr_assert_eq(list->head->data, 1, "dll_prepend() failed");
    cr_assert_eq(list->tail->data, 1, "dll_prepend() failed");
    cr_assert_eq(list->size, 1, "dll_prepend() failed");

    dll_prepend(list, 2);
    cr_assert_eq(list->head->data, 2, "dll_prepend() failed");
    cr_assert_eq(list->tail->data, 1, "dll_prepend() failed");
    cr_assert_eq(list->size, 2, "dll_prepend() failed");

    cr_assert_eq(list->head->next, list->tail, "dll_prepend() failed");
    cr_assert_eq(list->tail->prev, list->head, "dll_prepend() failed");
}

Test(double_linked_list, dll_insert) {
    dll_insert(list, 1);
    cr_assert_eq(list->head->data, 1, "dll_insert() failed");
    cr_assert_eq(list->tail->data, 1, "dll_insert() failed");
    cr_assert_eq(list->size, 1, "dll_insert() failed");

    dll_insert(list, 2);
    cr_assert_eq(list->head->data, 1, "dll_insert() failed");
    cr_assert_eq(list->tail->data, 2, "dll_insert() failed");
    cr_assert_eq(list->size, 2, "dll_insert() failed");

    cr_assert_eq(list->head->next, list->tail, "dll_insert() failed");
    cr_assert_eq(list->tail->prev, list->head, "dll_insert() failed");
}

Test(double_linked_list, dll_delete) {
    dll_insert(list, 1);
    dll_insert(list, 2);
    dll_insert(list, 3);

    dll_delete(list, 2);
    cr_assert_eq(list->head->data, 1, "dll_delete() failed");
    cr_assert_eq(list->tail->data, 3, "dll_delete() failed");
    cr_assert_eq(list->size, 2, "dll_delete() failed");

    dll_delete(list, 1);
    cr_assert_eq(list->head->data, 3, "dll_delete() failed");
    cr_assert_eq(list->tail->data, 3, "dll_delete() failed");
    cr_assert_eq(list->size, 1, "dll_delete() failed");
}

Test(double_linked_list, dll_delete_node) {
    dll_insert(list, 1);
    dll_insert(list, 2);
    dll_insert(list, 3);

    dll_node_t* node = dll_find(list, 2);
    dll_delete_node(list, node);
    cr_assert_eq(list->head->data, 1, "dll_delete_node() failed");
    cr_assert_eq(list->tail->data, 3, "dll_delete_node() failed");
    cr_assert_eq(list->size, 2, "dll_delete_node() failed");
}

Test(double_linked_list, dll_get) {
    dll_insert(list, 1);
    dll_insert(list, 2);
    dll_insert(list, 3);

    dll_node_t* node = dll_get(list, 0);
    cr_assert_not_null(node, "dll_get() failed");
    cr_assert_eq(node->data, 1, "dll_get() failed");

    node = dll_get(list, 1);
    cr_assert_not_null(node, "dll_get() failed");
    cr_assert_eq(node->data, 2, "dll_get() failed");

    node = dll_get(list, 2);
    cr_assert_not_null(node, "dll_get() failed");
    cr_assert_eq(node->data, 3, "dll_get() failed");

    node = dll_get(list, 3);
    cr_assert_null(node, "dll_get() failed");
}

Test(double_linked_list, dll_find) {
    dll_insert(list, 1);
    dll_insert(list, 2);
    dll_insert(list, 3);

    dll_node_t* node = dll_find(list, 2);
    cr_assert_not_null(node, "dll_find() failed");
    cr_assert_eq(node->data, 2, "dll_find() failed");

    node = dll_find(list, 4);
    cr_assert_null(node, "dll_find() failed");
}
