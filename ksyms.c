#include <ksyms.h>

#include <multiboot.h>
#include <config.h>
#include <paging.h>
#include <paging-utils.h>

#ifdef LERNEL_KSYMS_ENABLED

uint32_t num;
elf32_shdr_t *elf_shdr;
unsigned short ksyms_loaded = 0;

void loadksyms(multiboot_elf_section_header_table_t *sht) {
    // FIXME: Once our PMM is done, this should be finished as well
    // FIXME: Ksyms facility disabled until the above is done

    // num = sht->num;
    // elf_shdr = (elf32_shdr_t *)sht->addr;
    // ksyms_loaded = 1;
}

unsigned short is_ksyms_loaded() {
    return ksyms_loaded;
}

elf32_sym_t *get_ksym_by_address(uint32_t addr) {
    if (!is_ksyms_loaded()) {
        return NULL;
    }

    void *candidate = NULL;
    int offset = -1;

    for (int i = 0; i < num; i++) {
        if (elf_shdr[i].type == 2) {
            elf32_sym_t *sym_table = (elf32_sym_t *)elf_shdr[i].addr;

            for (int j = 0; j < elf_shdr[i].size / sizeof(elf32_sym_t); j++) {
                if ((offset == -1 || (addr - sym_table[j].value) < offset)) {
                    candidate = &sym_table[j];
                    offset = addr - sym_table[j].value;
                }
            }
        }
    }

    if (candidate) {
        return (elf32_sym_t *)candidate;
    }

    return NULL;
}

char *get_shdr_string(uint32_t index) {
    if (!is_ksyms_loaded()) {
        return NULL;
    }

    for (int i = 0; i < num; i++) {
        if (elf_shdr[i].type == 3) {
            return (char *)elf_shdr[i].addr + index;
        }
    }

    return NULL;
}

#endif
