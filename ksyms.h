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

struct elf32_sym {
    uint32_t name;
    uint32_t value;
    uint32_t size;
    uint8_t info;
    uint8_t other;
    uint16_t shndx;
};
typedef struct elf32_sym elf32_sym_t;

unsigned short is_ksyms_loaded();
void loadksyms(multiboot_elf_section_header_table_t *);
char *get_shdr_string(uint32_t);
