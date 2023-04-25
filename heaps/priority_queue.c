#include "priority_queue.h"

int parent_of(int index) {
    return ((index + 1) / 2) - 1;
}

int right_of(int index) {
    return (index + 1) * 2;
}

int left_of(int index) {
    return ((index + 1) * 2) - 1;
}

QueueElement queue_node(int key, void *data) {
    QueueElement node;
    node.key = key;
    node.value = data;
    return node;
}

int find_index(PriorityQueue *queue, void *value_ptr) {
    for (int i = 0; i < queue->size; i++) {
        if (queue->data[i].value == value_ptr) {
            return i;
        }
    }

    return -1;
}

void max_heapify(PriorityQueue *queue, int index) {
    int largest = index;

    int right = right_of(index);
    int left = left_of(index);

    if (left < queue->size && queue->data[left].key > queue->data[largest].key) {
        largest = left;
    }

    if (right < queue->size && queue->data[right].key > queue->data[largest].key) {
        largest = right;
    }
    
    if (largest != index) {
       QueueElement temp = queue->data[index]; 

       queue->data[index] = queue->data[largest];
       queue->data[largest] = temp;

       max_heapify(queue, largest);
    }
}

PriorityQueue *new_max_priority_queue() {
    PriorityQueue *queue = (PriorityQueue*) malloc(sizeof(PriorityQueue));

    queue->data = (QueueElement*) malloc(QUEUE_BLOCK * sizeof(QueueElement));
    queue->allocated_memory = QUEUE_BLOCK;
    queue->size = 0;

    return queue;
}

void insert(PriorityQueue *queue, int key, void *value_ptr) {
    QueueElement new_item = queue_node(INT_MIN, value_ptr);

    queue->data[queue->size] = new_item;
    queue->size++;
    
    increase_key(queue, value_ptr, key);
}

void increase_key(PriorityQueue *queue, void *value_ptr, int new_key) {
   int value_index = find_index(queue, value_ptr);

   if (new_key <= queue->data[value_index].key) {
       return;
   }

   queue->data[value_index].key = new_key;

   while (value_index > 0 && queue->data[parent_of(value_index)].key < queue->data[value_index].key) {
       QueueElement temp = queue->data[value_index];

       queue->data[value_index] = queue->data[parent_of(value_index)];
       queue->data[parent_of(value_index)] = temp;

       value_index = parent_of(value_index);
   }
}

void *extract_max(PriorityQueue *queue) {
    void *result = max(queue);

    queue->size--;

    queue->data[0] = queue->data[queue->size];
    max_heapify(queue, 0);

    return result;
}

void *max(PriorityQueue *queue) {
    return queue->data[0].value;
}

int is_empty(PriorityQueue *queue) {
    return queue->size == 0;
}
