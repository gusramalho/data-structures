#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct heap {
    int *data;
    int heap_size;
    int data_size;
} Heap;

Heap *new_max_heap(int *data, int length);

void max_heapify(Heap *heap, int index);

void heapsort(int *array, int length);

#endif // !HEAPSORT_H
