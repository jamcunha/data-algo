#include <criterion/criterion.h>
#include "../data-structures/stack/stack.h"

static stack_t* stack;

static void test_setup(void) {
    stack = stack_create();
}

static void test_teardown(void) {
    stack_destroy(stack);
}

Test(stack, stack_init, .init = test_setup, .fini = test_teardown) {
    cr_assert_not_null(stack, "stack_init() failed");
    cr_assert_eq(stack->top, 0, "stack_init() failed");
    cr_assert_eq(stack->capacity, STACK_INIT_CAPACITY, "stack_init() failed");
    cr_assert_not_null(stack->data, "stack_init() failed");
}

Test(stack, stack_push, .init = test_setup, .fini = test_teardown) {
    for (int i = 0; i < 10; i++) {
        stack_push(stack, i);
    }

    cr_assert_eq(stack->top, 10, "stack_push() failed");
    for (int i = 0; i < 10; i++) {
        cr_assert_eq(stack->data[i], i, "stack_push() failed");
    }
}

Test(stack, stack_push_resize, .init = test_setup, .fini = test_teardown) {
    for (int i = 0; i < 10; i++) {
        stack_push(stack, i);
    }

    stack_push(stack, 10);
    cr_assert_eq(stack->top, 11, "stack_push() failed");
    cr_assert_eq(stack->capacity, STACK_INIT_CAPACITY * 2, "stack_push() failed");
    for (int i = 0; i < 11; i++) {
        cr_assert_eq(stack->data[i], i, "stack_push() failed");
    }
}

Test(stack, stack_pop, .init = test_setup, .fini = test_teardown) {
    for (int i = 0; i < 10; i++) {
        stack_push(stack, i);
    }

    for (int i = 0; i < 10; i++) {
        cr_assert_eq(stack_top(stack), 9 - i, "stack_top() failed");
        stack_pop(stack);
    }

    cr_assert_eq(stack->top, 0, "stack_pop() failed");
}
