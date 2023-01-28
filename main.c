#include <vga.h>
#include <tty.h>
#include <config.h>
#include <ports.h>
#include <multiboot.h>
#include <panic.h>
#include <regs.h>
#include <ksyms.h>
#include <paging.h>
#include <paging-utils.h>

extern uint32_t boot_eax;
extern multiboot_info_t *boot_ebx;

void main() {
    // FIXME: This is a workaround until I can figure out why
    // for some reason, passing the arguments onto the stack
    // to main() is resulting in clobbered values. For now,
    // we just store them as space in .bss.
    uint32_t multiboot_magic=boot_eax;
    multiboot_info_t *multiboot=boot_ebx;

    // Before we do anything else, let's map in the VGA buffer to 0xc00b8000
    map_page(0xc00b8000, 0xb8000, PAGE_PRESENT | PAGE_WRITE);
    flush_tlb();

    tty_init();
    vga_init();
    tty_set_provider(&vga_putc_provider, &vga_clear_provider);
    disable_cursor();
    clear();
    // TODO: loglevels?
    puts("early vga console ready\n");

    // before we can do anything with symbols, we must first
    // make the check that we're using multiboot
    if (multiboot_magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        cpu_registers_t regs;

        init_regs(&regs);
        panic
            ("We were not loaded by a Multiboot-compliant boot-loader!",
             &regs);
        return;
    }

    // Now that we've confirmed that we're using multiboot, we can
    // now map the Multiboot info structure into memory.
    // We'll map it in at 0xc0000000, which is right at the beginning of our space.
    // Refresher on the space we have in use:
    // 0xc00b8000 - 0xc00b9000: VGA buffer
    // 0xc0100000 and on: kernel code
    
    map_page(0xc0000000, (uint32_t)multiboot, PAGE_PRESENT);
    flush_tlb();
    multiboot = (multiboot_info_t *)0xc0000000;

    // Now, it's time to begin setting up our VMM and PMM.

#ifdef LERNEL_KSYMS_ENABLED
    if ((multiboot->flags & MULTIBOOT_INFO_ELF_SHDR) == MULTIBOOT_INFO_ELF_SHDR) {
        loadksyms(&multiboot->u.elf_sec);
        puts("ksyms loaded\n");
    } else
        puts("ksyms not available\n");
#endif

    // Once we're done with the multiboot information structure, we unmap it from memory.
    unmap_page(0xc0000000);
    flush_tlb();

    cpu_registers_t regs;

    init_regs(&regs);
    panic("unimplemented", &regs);
}
