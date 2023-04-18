#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

#define QUEUE_BLOCK 4
#define DEBUG_MODE 1 

typedef struct queue_result {
    int result;
    int has_error;
} QueueResult;

QueueResult queue_result(int result);

QueueResult queue_underflow();

typedef struct queue {
    int *value;
    int allocated_memory;
    int first;
    int last;
    int size;
} Queue;

Queue *new_queue();

QueueResult enqueue(Queue *queue, int data);

QueueResult dequeue(Queue *queue);

int is_empty(Queue *queue);

#endif // !QUEUE_H
