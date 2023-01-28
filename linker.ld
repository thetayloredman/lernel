OUTPUT_FORMAT(elf32-i386)
ENTRY(_start)
SECTIONS {
    . = 1M;
    _physical_start = .;
    .phys.text BLOCK(4K) : ALIGN(4K) {
        *(.multiboot)
        *(.phys.text)
    }
    . = ALIGN(CONSTANT(COMMONPAGESIZE));
    .phys.data : { *(.phys.data) }
    .phys.bss  : { *(.phys.bss)  }

    . += 0xC0000000;

    .text ALIGN(4k) : AT(ADDR(.text) - 0xC0000000) { *(.text) }
    .data ALIGN(4k) : AT(ADDR(.data) - 0xC0000000) { *(.data) }
    .bss  ALIGN(4k) : AT(ADDR(.bss)  - 0xC0000000) { *(.bss)  }

    _physical_end = . - 0xC0000000;
}
