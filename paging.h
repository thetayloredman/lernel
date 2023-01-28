#pragma once
#include <types.h>

// some helpful macros
// TODO: add more
#define PAGE_PRESENT 0x1
#define PAGE_WRITE 0x2
#define PAGE_USER 0x4

// and we also define a little macro we can use to access a specific page table entry
// because we mapped them into our address space
// we can use the virtual address to access them, remember:
// 1111111111 XXXXXXXXXX 00YYYYYYYYYY
// constant   pdir ent     ptab ent
#define PAGE_DIRECTORY_POINTER 0xFFC00000
#define GET_PAGE_TABLE_POINTER(pdir, ptab) ((page_table_entry_32_t *)(PAGE_DIRECTORY_POINTER + (pdir * 0x1000) + (ptab * 0x4)))
#define GET_PAGE_DIRECTORY_FROM_ADDRESS(address) ((address >> 22) & 0x3FF)
#define GET_PAGE_TABLE_FROM_ADDRESS(address) ((address >> 12) & 0x3FF)

union page_directory_entry_32 {
    uint32_t value;
};
typedef union page_directory_entry_32 page_directory_entry_32_t;

union page_table_entry_32 {
    uint32_t value;
};
typedef union page_table_entry_32 page_table_entry_32_t;

void map_page(uint32_t, uint32_t, uint32_t);
void unmap_page(uint32_t);