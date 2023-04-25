#include <stdio.h>
#include <stdlib.h>

#include "heapsort.h"

void print_array(int *array, int length) {
    for (int i = 0; i < length; i++) {
        printf(
            "%d%s",
            array[i],
            i < length- 1 ? ", " : ""
        );
    }
}

void print_heap(Heap *heap) {
    printf("Heap.size: %d\n", heap->heap_size);
    printf("Heap.data_size: %d\n", heap->data_size);
    printf("Heap.data: [");

    print_array(heap->data, heap->heap_size); 

    printf("]\n\n");
}

void test_sort(int *array, int length) {
    printf("Original: [");
    print_array(array, length);
    printf("]\n");
    heapsort(array, length);
    printf("Sorted: [");
    print_array(array, length);
    printf("]\n");
}

int main() {
    int a1[5] = { 4, 1, 5, 2, 8 };
    int a2[8] = { 4, 20, 15, 1, 50, 100, 30, 1 };
    int a3[1] = { 2 };
    int a4[0] = { };
    int a5[10] = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
    int a6[10] = { 1, 2, 3, 4, 7, 8, 9, 10, 14, 16 };

    test_sort(a1, 5);
    test_sort(a2, 8);
    test_sort(a3, 1);
    test_sort(a4, 0);
    test_sort(a5, 10);
    test_sort(a6, 10);
}
