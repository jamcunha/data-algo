#include "stack.h"

#include <assert.h>
#include <stdlib.h>

stack_t* stack_create(void) {
    stack_t* stack = (stack_t*)calloc(1, sizeof(stack_t));
    if (stack == NULL) {
        return NULL;
    }

    stack->top = 0;
    stack->capacity = STACK_INIT_CAPACITY;
    stack->data = (int*)calloc(STACK_INIT_CAPACITY, sizeof(int));
    if (stack->data == NULL) {
        free(stack);
        return NULL;
    }

    return stack;
}

void stack_destroy(stack_t* stack) {
    assert(stack != NULL);

    free(stack->data);
    free(stack);
}

void stack_push(stack_t* stack, int value) {
    assert(stack != NULL);

    if (stack->top == stack->capacity) {
        stack->capacity *= 2;
        stack->data = (int*)realloc(stack->data, stack->capacity * sizeof(int));
    }

    stack->data[stack->top++] = value;
}

void stack_pop(stack_t* stack) {
    assert(stack != NULL);
    assert(!is_stack_empty(stack));

    stack->top--;
}

int stack_top(stack_t* stack) {
    assert(stack != NULL);

    return stack->data[stack->top - 1];
}

bool is_stack_empty(stack_t* stack) {
    assert(stack != NULL);

    return stack->top == 0;
}
