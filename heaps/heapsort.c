#include "heapsort.h"

int parent_of(int index) {
    return ((index + 1) / 2) - 1;
}

int right_of(int index) {
    return (index + 1) * 2;
}

int left_of(int index) {
    return ((index + 1) * 2) - 1;
}

Heap *new_max_heap(int *data, int length) {
    Heap *heap = (Heap*) malloc(sizeof(Heap));

    heap->data = data;
    heap->heap_size = length;
    heap->data_size = length;

    for (int i = (length / 2) - 1; i >= 0; i--) {
        max_heapify(heap, i);
    }

    return heap;
}

void max_heapify(Heap *heap, int index) {
    int largest = index;

    int right = right_of(index);
    int left = left_of(index);

    if (left < heap->heap_size && heap->data[left] > heap->data[largest]) {
        largest = left;
    }

    if (right < heap->heap_size && heap->data[right] > heap->data[largest]) {
        largest = right;
    }
    
    if (largest != index) {
       int temp = heap->data[index]; 

       heap->data[index] = heap->data[largest];
       heap->data[largest] = temp;

       max_heapify(heap, largest);
    }
}


void heapsort(int *array, int length) {
    Heap *max_heap = new_max_heap(array, length);
    
    while (max_heap->heap_size > 0) {
        int temp = max_heap->data[max_heap->heap_size - 1];

        max_heap->data[max_heap->heap_size - 1] = max_heap->data[0];
        max_heap->data[0] = temp;
        max_heap->heap_size--;

        max_heapify(max_heap, 0);
    }

    free(max_heap);
}
