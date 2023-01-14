#include <vga.h>
#include <tty.h>
#include <config.h>
#include <ports.h>
#include <multiboot.h>
#include <panic.h>
#include <regs.h>
#include <ksyms.h>

void main(uint32_t multiboot_magic, multiboot_info_t *multiboot) {
    tty_init();
    disable_cursor();
    clear();

    // before we can do anything with symbols, we must first
    // make the check that we're using multiboot
    if (multiboot_magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        cpu_registers_t *regs;
        init_regs(regs);
        panic("We were not loaded by a Multiboot-compliant boot-loader!", regs);
        return;
    }

    // TODO: check bit 5 is set (ELF) in multiboot->flags before we do this
    loadksyms(&multiboot->u.elf_sec);

    puts("main: hello from main()\n");
    cpu_registers_t *regs;
    init_regs(regs);
    panic("unable to find epic memes", regs);
    return;
}
