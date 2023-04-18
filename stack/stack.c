#include "stack.h"

void debug(const char *log) {
    if (DEBUG_MODE) printf("%s\n", log);
}

Stack *new_stack() {
    Stack *stack = (Stack*) malloc(sizeof(Stack));

    stack->top = -1;
    stack->value = (int*) malloc(STACK_BLOCK * sizeof(int));
    stack->allocated_memory = STACK_BLOCK;

    return stack;
}

void push(Stack *stack, int data) {
    stack->top++;

    if (stack->top >= stack->allocated_memory) {
        debug("Alocando mais memoria...");
        stack->allocated_memory += STACK_BLOCK;
        stack->value = (int*) realloc(stack->value, stack->allocated_memory * sizeof(int));
    }

    stack->value[stack->top] = data;
}

int pop(Stack *stack) {
    int value = stack->value[stack->top];

    stack->top--;

    if (stack->top < stack->allocated_memory - STACK_BLOCK - 1) {
        debug("Desalocando memoria...");
        stack->allocated_memory -= STACK_BLOCK;
        stack->value = (int*) realloc(stack->value, stack->allocated_memory * sizeof(int));
    }

    return value;
}

int peek(Stack *stack) {
    return stack->value[stack->top];
}

int is_empty(Stack *stack) {
    return stack->top == -1;
}
