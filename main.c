#include <vga.h>
#include <tty.h>
#include <config.h>
#include <ports.h>
#include <multiboot.h>
#include <panic.h>
#include <regs.h>
#include <ksyms.h>

void main() {
    multiboot_info_t *multiboot;
    asm("mov %%eax, %0" : "=r"(multiboot));
    // TODO: check bit 5 is set (ELF) in multiboot->flags
    loadksyms(&multiboot->u.elf_sec);
    tty_init();
    disable_cursor();
    clear();
    puts("main: hello from main()\n");
    cpu_registers_t *regs;
    init_regs(regs);
    panic("unable to find epic memes", regs);
    return;
}
