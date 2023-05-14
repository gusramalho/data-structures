#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 256

typedef unsigned int PageId;
typedef unsigned short SlotId;
typedef unsigned short SlotOffset;
typedef unsigned short RecordSize;
typedef char PageType;

#define DATA_PAGE 0x01
#define DIRECTORY_PAGE 0x02

typedef struct record_id {
    PageId page_id;
    SlotId slot_id;
} RecordId;

typedef struct slot {
    SlotOffset offset; 
    RecordSize length; 
} Slot;

typedef struct page {
    PageId id;
    char *data;
} Page;

typedef struct page_header {
    unsigned short used_slots;
    SlotOffset last_slot;
} PageDataHeader;

typedef struct buffer_pool {
    int size;
    Page *pages;
} BufferPool;

typedef struct page_directory {
    char *data;
} PageDirectory;

typedef struct page_directory_header {
    PageId last_page;
    PageId next_page_directory;
} PageDirectoryHeader;

typedef struct page_directory_info {
    PageId page_id;
    PageType page_type;
    RecordSize free_space;
} PageDirectoryInfo;

typedef struct disk_manager {
    const char *filename;
    BufferPool page_buffer;
    PageDirectory *page_directory;
} DiskManager;

PageDirectory *new_page_directory();

Page *new_page(PageId id);

PageId next_page_id(DiskManager *dm);

void delete_page(DiskManager *dm, PageId page_id);

char *page_content(Page *page);

Page *read_page(DiskManager *self, PageId page_id);

void write_page(DiskManager *self, Page *page);

DiskManager *new_disk_manager(const char *filename);

void write_page_directory(DiskManager *self);

PageDirectory *read_page_directory(const char *filename);

char used_slots(Page *p);

char last_slot_used_offset(Page *p);

RecordId insert_new_record(DiskManager *self, void *record, RecordSize size);

RecordId insert_record(Page *p, void *record, RecordSize size);

PageDirectoryInfo *page_info(DiskManager *self, PageId page_id);

RecordSize calc_data_page_free_space(Page *page);

