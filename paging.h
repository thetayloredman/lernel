#pragma once
#include <types.h>

// TODO: 4MB pages?
union page_directory_entry_32 {
    uint32_t value;
};
typedef union page_directory_entry_32 page_directory_entry_32_t;

union page_table_entry_32 {
    uint32_t value;
};
typedef union page_table_entry_32 page_table_entry_32_t;
