#include <stdio.h>
#include <stdlib.h>

#include "priority_queue.h"

typedef struct student {
    int id;
    char *name;
} Student;

Student student(int id, char *name) {
    Student s;
    s.id = id;
    s.name = name;
    return s;
}

void print_array(QueueElement *array, int length) {
    for (int i = 0; i < length; i++) {
        if (array[i].value == NULL) {
            printf("NULL");
            continue;
        }

        Student *value = (Student*) array[i].value;

        printf(
            "{key: %d, value: (id: %d, name: %s)}%s",
            array[i].key,
            value->id,
            value->name,
            i < length- 1 ? ", " : ""
        );
    }
}

void print_heap(PriorityQueue *queue) {
    printf("Queue.size: %d\n", queue->size);
    printf("Queue.allocated_memory: %d\n", queue->allocated_memory);
    printf("Queue.data: [");

    print_array(queue->data, queue->size); 

    printf("]\n\n");
}

int main() {
    Student s1 = student(1, "Gustavo");
    Student s2 = student(2, "Test");
    Student s3 = student(3, "Blabla");
    Student s4 = student(4, "ASDOF");
    Student s5 = student(4, "OPA");
    Student s6 = student(8, "ultimo");

    PriorityQueue *q = new_max_priority_queue();
    
    insert(q, 1, &s1);
    insert(q, 2000, &s5);
    insert(q, -1, &s6);
    insert(q, 100, &s2);
    insert(q, 1000, &s3);
    insert(q, 1001, &s4);

    increase_key(q, &s1, 3000);

    while (!is_empty(q)) {
        Student *s = (Student*) extract_max(q);

        printf("Extracted: (%d, %s)\n", s->id, s->name);
    }

    print_heap(q);

    return 0;
}
