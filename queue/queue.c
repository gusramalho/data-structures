#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

int is_new(Queue *queue) {
    return queue->first == -1 && queue->last == -1;
}

QueueResult queue_result(int data) {
    QueueResult result;
    result.result = data;
    result.has_error = 0;
    return result;
}

QueueResult queue_underflow() {
    QueueResult result;
    result.has_error = 1;
    return result;
}

Queue *new_queue() {
    Queue *queue = (Queue*) malloc(sizeof(Queue));

    queue->first = -1;
    queue->last = -1;
    queue->size = 0;
    queue->value = (int*) malloc(QUEUE_BLOCK * sizeof(int));
    queue->allocated_memory = QUEUE_BLOCK;

    return queue;
}

QueueResult enqueue(Queue *queue, int data) {
    if (is_empty(queue)) {
        queue->first = 0;
        queue->last = 0;
        queue->size++;
        queue->value[0] = data;

        return queue_result(data);
    }

    if (queue->size >= queue->allocated_memory) {
        printf("Alocando memoria...\n");
        int previous_allocated_memory = queue->allocated_memory;

        queue->allocated_memory += QUEUE_BLOCK; 
        queue->value = (int*) realloc(queue->value, queue->allocated_memory * sizeof(int));

        if (queue->last < queue->first) {
            if (queue->last < previous_allocated_memory - queue->first) {
                int shifted_idx;

                for (int i = 0; i <= queue->last; i++) {
                    shifted_idx = i + queue->size;
                    shifted_idx = shifted_idx < queue->allocated_memory 
                        ? shifted_idx : i - QUEUE_BLOCK; 

                    queue->value[shifted_idx] = queue->value[i]; 
                }

                queue->last = shifted_idx;
            } else {
                for (int i = previous_allocated_memory - 1; i >= queue->first; i--) {
                    queue->value[i + QUEUE_BLOCK] = queue->value[i]; 
                }
                
                queue->first += QUEUE_BLOCK;
            }
        }     
    }

    int next_idx = (queue->last + 1) % queue->allocated_memory;

    queue->value[next_idx] = data;
    queue->last = next_idx;
    queue->size++;

    return queue_result(data);
}

QueueResult dequeue(Queue *queue) {
    if (is_empty(queue)) {
        return queue_underflow();
    }

    int value = queue->value[queue->first];
    int next_first = (queue->first + 1) % queue->allocated_memory;

    queue->first = next_first;
    queue->size--;

    if (queue->allocated_memory - queue->size >= 2 * QUEUE_BLOCK) {
        printf("============ Desalocando memoria...");

        if (queue->last >= queue->first) {
            for (int i = queue->first; i <= queue->last; i++) {
                queue->value[i - queue->first] = queue->value[i];
            }

            queue->last -= queue->first;
            queue->first = 0;
        } else {
            for (int i = queue->first; i < queue->allocated_memory; i++) {
                queue->value[i - QUEUE_BLOCK] = queue->value[i];
            }

            queue->first -= QUEUE_BLOCK;
        }

        queue->allocated_memory -= QUEUE_BLOCK;
        queue->value = (int*) realloc(queue->value, queue->allocated_memory * sizeof(int));
    }

    return queue_result(value);
}

int is_empty(Queue *queue) {
    return queue->size == 0;
}
