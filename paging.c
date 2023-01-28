#include <paging.h>
#include <paging-utils.h>

void map_page(uint32_t virtual, uint32_t physical, uint32_t flags) {
    uint32_t pdir = GET_PAGE_DIRECTORY_FROM_ADDRESS(virtual);
    uint32_t ptab = GET_PAGE_TABLE_FROM_ADDRESS(virtual);
    page_table_entry_32_t *page_table = GET_PAGE_TABLE_POINTER(pdir, ptab);

    page_table->value = physical | flags;
}

void unmap_page(uint32_t virtual) {
    uint32_t pdir = GET_PAGE_DIRECTORY_FROM_ADDRESS(virtual);
    uint32_t ptab = GET_PAGE_TABLE_FROM_ADDRESS(virtual);
    page_table_entry_32_t *page_table = GET_PAGE_TABLE_POINTER(pdir, ptab);

    page_table->value = 0;
}