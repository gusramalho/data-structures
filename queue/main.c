#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

void print_queue(Queue *queue) {
    if (is_empty(queue)) {
        printf("is empty");
        return;
    }

    printf("[");

    for (int i = 0; i < queue->allocated_memory; i++) {
        printf("%d", queue->value[i]);
        
        if (i != queue->allocated_memory - 1) printf(", ");
    }

    printf("]\n"); 
    printf(
        "First: %d\nLast:%d\nMem: %d\nSize: %d\n\n", 
        queue->first, 
        queue->last, 
        queue->allocated_memory,
        queue->size
    );
}

void test_dequeue_deallocation_memory_2() {
    Queue *q = new_queue();

    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    enqueue(q, 4);
    enqueue(q, 5);
    enqueue(q, 6);
    enqueue(q, 7);
    enqueue(q, 8);
    enqueue(q, 9);
    enqueue(q, 10);
    enqueue(q, 11);
    enqueue(q, 12);
    enqueue(q, 13);
    enqueue(q, 14);
    enqueue(q, 15);
    enqueue(q, 16);

    printf("Dequeuing %d\n", dequeue(q).result);
    printf("Dequeuing %d\n", dequeue(q).result);
    printf("Dequeuing %d\n", dequeue(q).result);
    printf("Dequeuing %d\n", dequeue(q).result);
    enqueue(q, 17);
    enqueue(q, 18);

    printf("Dequeuing %d\n", dequeue(q).result);
    printf("Dequeuing %d\n", dequeue(q).result);
    printf("Dequeuing %d\n", dequeue(q).result);
    printf("Dequeuing %d\n", dequeue(q).result);
    enqueue(q, 19);
    enqueue(q, 20);
    print_queue(q);
    printf("Dequeuing %d\n", dequeue(q).result);
    printf("Dequeuing %d\n", dequeue(q).result);
    printf("Dequeuing %d\n", dequeue(q).result);
    printf("Dequeuing %d\n", dequeue(q).result);

    print_queue(q);
}

void test_dequeue_deallocation_memory() {
    Queue *q = new_queue();

    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    enqueue(q, 4);
    enqueue(q, 5);
    enqueue(q, 6);
    enqueue(q, 7);
    enqueue(q, 8);
    enqueue(q, 9);
    enqueue(q, 10);
    enqueue(q, 11);
    enqueue(q, 12);
    enqueue(q, 13);
    enqueue(q, 14);
    enqueue(q, 15);
    enqueue(q, 16);

    printf("Dequeuing %d\n", dequeue(q).result);
    printf("Dequeuing %d\n", dequeue(q).result);
    printf("Dequeuing %d\n", dequeue(q).result);
    printf("Dequeuing %d\n", dequeue(q).result);
    printf("Dequeuing %d\n", dequeue(q).result);
    printf("Dequeuing %d\n", dequeue(q).result);

    print_queue(q);

    printf("Dequeuing %d\n", dequeue(q).result);
    printf("Dequeuing %d\n", dequeue(q).result);

    print_queue(q);
}

int test_enqueue() {
    Queue *q = new_queue();

    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    enqueue(q, 4);
    enqueue(q, 5);
    enqueue(q, 6);
    enqueue(q, 7);
    enqueue(q, 8);
    enqueue(q, 9);
    enqueue(q, 10);
    enqueue(q, 11);

    print_queue(q);

    printf("Dequeuing %d\n", dequeue(q).result);
    printf("Dequeuing %d\n", dequeue(q).result);

    print_queue(q);

    enqueue(q, 12);
    enqueue(q, 13);
    enqueue(q, 14);

    print_queue(q);

    enqueue(q, 15);
    enqueue(q, 16);
    enqueue(q, 17);
    enqueue(q, 18);
    printf("Dequeuing %d\n", dequeue(q).result);
    printf("Dequeuing %d\n", dequeue(q).result);
    printf("Dequeuing %d\n", dequeue(q).result);

    print_queue(q);

    enqueue(q, 19);
    enqueue(q, 20);

    print_queue(q);
    enqueue(q, 21);
    enqueue(q, 22);
    print_queue(q);
    printf("Dequeuing %d\n", dequeue(q).result);
    printf("Dequeuing %d\n", dequeue(q).result);
    printf("Dequeuing %d\n", dequeue(q).result);
    enqueue(q, 23);
    enqueue(q, 24);
    enqueue(q, 25);
    enqueue(q, 26);
    enqueue(q, 27);
    enqueue(q, 28);
    enqueue(q, 29);
    print_queue(q);
    printf("Dequeuing %d\n", dequeue(q).result);
    printf("Dequeuing %d\n", dequeue(q).result);
    printf("Dequeuing %d\n", dequeue(q).result);
    print_queue(q);
    enqueue(q, 30);
    enqueue(q, 31);
    enqueue(q, 32);
    printf("Dequeuing %d\n", dequeue(q).result);
    printf("Dequeuing %d\n", dequeue(q).result);
    enqueue(q, 33);
    enqueue(q, 34);
    print_queue(q);
    printf("Dequeuing %d\n", dequeue(q).result);
    printf("Dequeuing %d\n", dequeue(q).result);
    printf("Dequeuing %d\n", dequeue(q).result);
    printf("Dequeuing %d\n", dequeue(q).result);
    printf("Dequeuing %d\n", dequeue(q).result);
    print_queue(q);
    enqueue(q, 35);
    enqueue(q, 36);
    enqueue(q, 37);
    enqueue(q, 38);
    enqueue(q, 39);
    enqueue(q, 40);
    print_queue(q);
    enqueue(q, 41);
    enqueue(q, 42);
    enqueue(q, 43);
    print_queue(q);
    enqueue(q, 44);
    enqueue(q, 45);
    enqueue(q, 46);
    enqueue(q, 47);
    print_queue(q);

    while (!is_empty(q)) {
        printf("Dequeuing %d\n", dequeue(q).result);
    }

    return 0;
}

int main() {
    test_dequeue_deallocation_memory_2();
}
