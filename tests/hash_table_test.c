#include <criterion/criterion.h>
#include "../data-structures/hash_table/hash_table.h"

ht_t* table;

void test_setup(void) {
    table = ht_create(11);
}

void test_teardown(void) {
    ht_destroy(table);
}

TestSuite(hash_table, .init = test_setup, .fini = test_teardown);

Test(hash_table, ht_create) {
    cr_assert_not_null(table, "ht_create() failed");
    cr_assert_eq(table->size, 11, "ht_create() failed");
    cr_assert_not_null(table->table, "ht_create() failed");
}

Test(hash_table, ht_insert) {
    ht_insert(table, 1, 20);
    cr_assert_eq(ht_search(table, 1), 20, "ht_insert() failed");

    ht_insert(table, 45, 30);
    cr_assert_eq(ht_search(table, 45), 30, "ht_insert() failed");
}

Test(hash_table, ht_delete) {
    ht_insert(table, 1, 20);
    ht_insert(table, 45, 30);

    cr_assert_eq(ht_delete(table, 1), 20, "ht_delete() failed");
    cr_assert_eq(ht_search(table, 1), -1, "ht_delete() failed");

    cr_assert_eq(ht_delete(table, 45), 30, "ht_delete() failed");
    cr_assert_eq(ht_search(table, 45), -1, "ht_delete() failed");
}

Test(hash_table, ht_search) {
    ht_insert(table, 1, 20);
    cr_assert_eq(ht_search(table, 1), 20, "ht_search() failed");

    ht_insert(table, 45, 30);
    cr_assert_eq(ht_search(table, 45), 30, "ht_search() failed");
}
