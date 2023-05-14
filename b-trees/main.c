#include "disk_manager.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

#define DB_FILE "db_3_128.db"

void test_create_new_db() {
    DiskManager *dm = new_disk_manager(DB_FILE);

    PageDirectoryHeader *directory = (PageDirectoryHeader*) dm->page_directory->data;
    printf("PageDirectory(last_page: %d, next: %d)\n", directory->last_page, directory->next_page_directory);
    //Page *p = new_page(next_page_id(dm));
    //strcpy(page_content(p), "gustavo");
    //write_page(dm, p);
    //Page *p = read_page(dm, 1);

    //Page *p2 = new_page(2, BTREE_NODE);
    //strcpy(page_content(p2), "abcdef");
    //write_page(dm, p2);
}

void see_page_directory() {
    DiskManager *dm = new_disk_manager(DB_FILE);
    PageDirectoryHeader *directory = (PageDirectoryHeader*) dm->page_directory->data;
    printf("PageDirectory(last_page: %d, next: %d)\n", directory->last_page, directory->next_page_directory);

    PageDirectoryInfo *p_info = page_info(dm, 1);
    
    while (p_info->page_id != 0) {
        printf("PageInfo(id: %d, free_space: %d, type: %d)\n", 
                p_info->page_id,
                p_info->free_space,
                p_info->page_type
        );
        p_info++;
    }
}

typedef struct student {
    int id;
    char name[10];
} Student;

void test_write_student() {
    DiskManager *dm = new_disk_manager(DB_FILE);
    PageId id = next_page_id(dm);
    Page *p = new_page(id);

    Student s;
    s.id = 10924;
    strcpy(s.name, "Gustavo");
    memcpy(page_content(p), &s, sizeof(s));
    write_page(dm, p);
}

void test_read_student() {
    DiskManager *dm = new_disk_manager(DB_FILE);
    Page *p = read_page(dm, 5);

    Student s;
    memcpy(&s, p->data, sizeof(Student));

    printf("Student(id=%d, name=%s)", s.id, s.name);
}

void test_write_int_array() {
    int *slot = (int*) malloc(sizeof(int) * 5);
    slot[0] = 1234;
    slot[1] = 4334;
    slot[2] = 2222;
    slot[3] = 1111;
    slot[4] = 9090;

    DiskManager *dm = new_disk_manager(DB_FILE);
    Page *p = read_page(dm, 4);
    memcpy(p->data, slot, 5 * sizeof(int));
    write_page(dm, p);
}

void test_read_int_array() {
    int *slot = (int*) malloc(sizeof(int) * 5);

    DiskManager *dm = new_disk_manager(DB_FILE);
    Page *p = read_page(dm, 4);
    memcpy(slot, p->data, 5 * sizeof(int));

    for (int i = 0; i < 5; i++) {
        printf("%d\n", slot[i]);
    }
}

void test_blank_page() {
    DiskManager *dm = new_disk_manager(DB_FILE);
    PageId id = next_page_id(dm);
    printf("%d", id);
    Page *p = new_page(id);
    write_page(dm, p);
}

void test_reset_page(int page_id) {
    DiskManager *dm = new_disk_manager(DB_FILE);
    Page *p = new_page(page_id);
    write_page(dm, p);
}

void test_add_new_page() {
    DiskManager *dm = new_disk_manager(DB_FILE);

    PageId id = next_page_id(dm);
    Page *p = new_page(id);
    strcpy(page_content(p), "Pagina nova dois");
    write_page(dm, p);
}

void test_write_record() {
    DiskManager *dm = new_disk_manager(DB_FILE);
    Student s;

    s.id = 222344;
    strcpy(s.name, "12345689");

    insert_new_record(dm, &s, sizeof(s));
    //Page *p = read_page(dm, 1);
    //Student s;

    //s.id = 32445;
    //strcpy(s.name, "bla");

    //RecordId recordId = insert_record(p, &s, sizeof(s));

    //printf("RecordId(%d,%d)", recordId.page_id, recordId.slot_id);
    //write_page(dm, p);
}

void test_read_record() {
    DiskManager *dm = new_disk_manager(DB_FILE);
    Page *page = read_page(dm, 1);
    PageDataHeader *page_header = (PageDataHeader*) page->data;

    Student *students = (Student*) malloc(page_header->used_slots * sizeof(Student));
    int end = PAGE_SIZE;

    for (int i = 0; i < page_header->used_slots; i++) {
        Slot *slot = (Slot*) (page->data + sizeof(PageDataHeader) + i * sizeof(Slot));
        printf("start=%d / size=%d\n", slot->offset, slot->length);
        memcpy(students + i, page->data + slot->offset, slot->length);
        printf("Student(id=%d, name=%s)\n", students[i].id, students[i].name);
    }
}

int main() {
    test_read_record();
    return 0;
}

