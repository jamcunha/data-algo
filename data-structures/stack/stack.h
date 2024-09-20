#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

#define STACK_INIT_CAPACITY 10

typedef struct {
    int *data;
    int top;
    int capacity;
} stack_t;

stack_t* stack_create(void);

void stack_push(stack_t *stack, int value);

void stack_pop(stack_t *stack);

int stack_top(stack_t *stack);

bool is_stack_empty(stack_t *stack);

void stack_destroy(stack_t *stack);

#endif // STACK_H
