#include <ksyms.h>

#include <multiboot.h>

multiboot_elf_section_header_table_t *mb_elf_section_header_table;
elf32_shdr_t *elf_shdr;
char *elf_shdr_strings;
unsigned short ksyms_loaded = 0;

void loadksyms(multiboot_elf_section_header_table_t *sht) {
    mb_elf_section_header_table = sht;
    elf_shdr = (elf32_shdr_t *)mb_elf_section_header_table->addr;
    elf_shdr_strings = (char *)elf_shdr[mb_elf_section_header_table->shndx].addr;
    ksyms_loaded = 1;
}

unsigned short is_ksyms_loaded() {
    return ksyms_loaded;
}
