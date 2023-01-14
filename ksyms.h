#pragma once
#include <multiboot.h>
#include <types.h>

struct elf32_shdr {
    uint32_t name; // index into the string table
    uint32_t type;
    uint32_t flags;
    uint32_t addr; // address in memory
    uint32_t offset;
    uint32_t size; // section's size in bytes
    uint32_t link;
    uint32_t info;
    uint32_t addralign;
    uint32_t entsize;
};
typedef struct elf32_shdr elf32_shdr_t;

void loadksyms(multiboot_elf_section_header_table_t *);