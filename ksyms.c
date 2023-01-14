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

char *elf_shdr_string(uint32_t index) {
    return elf_shdr_strings + index;
}

elf32_shdr_t *lookup_ksym_by_address(uint32_t address) {
    puts(mb_elf_section_header_table->num);
    for (int i = 0; i < mb_elf_section_header_table->num; i++) {
        if (elf_shdr[i].type == 2) { // SHT_SYMTAB
            for (int j = 0; j < elf_shdr[i].size / elf_shdr[i].entsize; j++) {
                elf32_shdr_t *sym = (elf32_shdr_t *)(elf_shdr[i].addr + (j * elf_shdr[i].entsize));
                if (sym->type == 0x2) { // STT_FUNC
                    if (sym->addr == address) {
                        return sym;
                    }
                }
            }
        }
    }
    return NULL;
}