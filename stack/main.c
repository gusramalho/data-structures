#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void print_stack(Stack *stack) {
    if (is_empty(stack)) {
        printf("is empty");
        return;
    }

    printf("[");

    for (int i = 0; i <= stack->top; i++) {
        printf("%d", stack->value[i]);
        
        if (i != stack->top) printf(", ");
    }

    printf("]\n"); 
    printf("Top: %d\nMem: %d\n\n", stack->top, stack->allocated_memory);
}

int main() {
    Stack *stack = new_stack();

    push(stack, 5);
    push(stack, 7);
    push(stack, 8);

    push(stack, 9);
    print_stack(stack);
    push(stack, 9);
    print_stack(stack);


    printf("Popping: %d\n", pop(stack));
    print_stack(stack);
    push(stack, 10);
    print_stack(stack);
    printf("Popping: %d\n", pop(stack));
    print_stack(stack);
    printf("Popping: %d\n", pop(stack));
    print_stack(stack);

    while (!is_empty(stack)) {
        printf("Popping: %d\n", pop(stack));
        print_stack(stack);
    }

    return 0;
}
