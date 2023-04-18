#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

#define STACK_BLOCK 4
#define DEBUG_MODE 1

typedef struct stack {
    int *value;
    int allocated_memory;
    int top;
} Stack;

Stack *new_stack();

void push(Stack *stack, int data);

int pop(Stack *stack);

int peek(Stack *stack);

int is_empty(Stack *stack);

#endif
