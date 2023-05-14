#include "disk_manager.h"
#include <stdio.h>
#include <string.h>

Page *new_page(PageId id) {
    Page *p = (Page*) malloc(sizeof(Page));

    p->data = (char*) malloc(PAGE_SIZE * sizeof(char));
    p->id = id;

    return p;
}

char *page_content(Page *page) {
    return page->data;
}

PageDirectory *new_page_directory() {
    PageDirectory *p = (PageDirectory*) malloc(sizeof(PageDirectory));
    p->data = (char*) malloc(PAGE_SIZE);
    return p;
}

void write_page_directory(DiskManager *self) {
    FILE *file = fopen(self->filename, "rb+");
    fwrite(self->page_directory->data, sizeof(PageId), PAGE_SIZE, file);
    fclose(file);
}

PageDirectory *read_page_directory(const char *filename) {
    PageDirectory *pd = new_page_directory();

    FILE *file = fopen(filename, "rb");

    if (file != NULL) {
        fread(pd->data, sizeof(char), PAGE_SIZE, file);
    } else {
        file = fopen(filename, "w");
        fclose(file);
    }

    return pd;
}

Page *read_page(DiskManager *self, PageId page_id) {
    long offset = page_id * PAGE_SIZE;
    FILE *file = fopen(self->filename, "rb");

    Page *p = new_page(page_id);

    fseek(file, offset, SEEK_SET);
    fread(p->data, sizeof(char), PAGE_SIZE, file);

    fclose(file);
    return p;
}

PageDirectoryInfo *page_info(DiskManager *self, PageId page_id) {
    return (PageDirectoryInfo*)
        (self->page_directory->data + sizeof(PageDirectoryHeader) 
            + sizeof(PageDirectoryInfo) * (page_id - 1)); 
}

PageId next_page_id(DiskManager *dm) {
    PageDirectoryHeader *header = (PageDirectoryHeader*) 
        dm->page_directory->data;

    header->last_page++;

    PageDirectoryInfo *p_info = page_info(dm, header->last_page);

    p_info->page_id = header->last_page;
    p_info->page_type = DATA_PAGE;
    p_info->free_space = PAGE_SIZE;

    FILE *file = fopen(dm->filename, "rb+");

    fwrite(dm->page_directory->data, sizeof(char), PAGE_SIZE, file);
    fclose(file);

    return header->last_page;
}

void delete_page(DiskManager *dm, PageId page_id) {
    // TODO
}

void write_page(DiskManager *self, Page *page) {
    long offset = page->id * PAGE_SIZE;
    printf("nova pagina offset %ld", offset);
    FILE *file = fopen(self->filename, "rb+");

    fseek(file, offset, SEEK_SET);
    fwrite(page->data, sizeof(char), PAGE_SIZE, file);

    RecordSize free_space = calc_data_page_free_space(page);
    PageDirectoryInfo *p_info = page_info(self, page->id);
    p_info->free_space = free_space;

    fseek(file, 0, SEEK_SET);
    fwrite(self->page_directory->data, sizeof(char), PAGE_SIZE, file);

    fclose(file);
}

DiskManager *new_disk_manager(const char *filename) {
    DiskManager *dm = (DiskManager*) malloc(sizeof(DiskManager));
    dm->filename = filename;
    PageDirectory *pd = read_page_directory(dm->filename);
    dm->page_directory = pd;

    return dm;
}

Page *find_free_page(DiskManager *self, RecordSize size) {
    PageDirectoryInfo *p_info = page_info(self, 1);
    
    while (p_info->free_space < size && p_info->page_id != 0) {
        p_info++;
    } // TODO: Fix page overflow

    if (p_info->page_id > 0) {
        return read_page(self, p_info->page_id);
    }

    return NULL;
}

RecordSize calc_data_page_free_space(Page *page) {
    PageDataHeader *header = (PageDataHeader*) page->data;

    RecordSize length = header->last_slot ? header->last_slot : PAGE_SIZE;
    RecordSize slot_size = header->used_slots * sizeof(Slot);

    return length - sizeof(PageDataHeader) - slot_size;
} 

RecordId insert_new_record(DiskManager *self, void *record, RecordSize size) {
    Page *page = find_free_page(self, size);
    
    if (!page) {
        page = new_page(next_page_id(self));
    }

    RecordId record_id = insert_record(page, record, size);
    
    write_page(self, page);

    return record_id;
}

RecordId insert_record(Page *p, void *record, RecordSize size) {
    PageDataHeader *header = (PageDataHeader*) p->data; 

    RecordId recordId;
    recordId.page_id = p->id;

    SlotOffset last_slot = header->last_slot;

   // printf("last_slot=%d / used=%d", header->last_slot, header->used_slots);

    if (!header->used_slots) { 
        memcpy(p->data + PAGE_SIZE - size, record, size);
        header->last_slot = PAGE_SIZE - size;
    } else {
        memcpy(p->data + last_slot - size, record, size);
        header->last_slot = last_slot - size;
    }
    
    Slot *slot = (Slot*) 
        (p->data + sizeof(PageDataHeader) + header->used_slots * sizeof(Slot));

    slot->offset = header->last_slot;
    slot->length = size;

    recordId.slot_id = header->used_slots;
    header->used_slots++;

    return recordId;
}
 
