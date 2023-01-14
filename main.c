#include <vga.h>
#include <tty.h>
#include <config.h>
#include <ports.h>
#include <multiboot.h>
#include <panic.h>
#include <regs.h>

void main() {
    struct multiboot_header *multiboot;
    asm("mov %%eax, %0" : "=r"(multiboot));
    tty_init();
    disable_cursor();
    clear();
    puts("main: hello from main()\n");
    cpu_registers_t *regs;
    init_regs(regs);
    panic("unable to find epic memes", regs);
    return;
}
