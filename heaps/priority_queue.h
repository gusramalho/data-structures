#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define QUEUE_BLOCK 64

typedef struct queue_element {
    int key;
    void *value;
} QueueElement;

typedef struct priority_queue {
    QueueElement *data;
    int allocated_memory;
    int size;
} PriorityQueue;

PriorityQueue *new_max_priority_queue();

void insert(PriorityQueue *queue, int key, void *value_ptr);

void increase_key(PriorityQueue *queue, void *value_ptr, int new_key);

void *extract_max(PriorityQueue *queue);

void *max(PriorityQueue *queue);

int is_empty(PriorityQueue *queue);

#endif 
