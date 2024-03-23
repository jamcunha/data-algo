#include "stack.h"

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
    if (stack == NULL) {
        return;
    }

    free(stack->data);
    free(stack);
}

bool stack_push(stack_t* stack, int value) {
    if (stack == NULL) {
        return false;
    }

    if (stack->top == stack->capacity) {
        stack->capacity *= 2;
        stack->data = (int*)realloc(stack->data, stack->capacity * sizeof(int));
        if (stack->data == NULL) {
            return false;
        }
    }

    stack->data[stack->top++] = value;
    return true;
}

bool stack_pop(stack_t* stack) {
    if (is_stack_empty(stack)) {
        return false;
    }

    stack->top--;
    return true;
}

bool stack_top(stack_t* stack, int* value) {
    if (is_stack_empty(stack)) {
        return false;
    }

    *value = stack->data[stack->top - 1];
    return true;
}

bool is_stack_empty(stack_t* stack) {
    return stack == NULL || stack->top == 0;
}
