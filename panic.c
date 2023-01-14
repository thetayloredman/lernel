#include <panic.h>

#include <tty.h>
#include <types.h>
#include <stackframe.h>
#include <regs.h>
#include <ksyms.h>

char *hexify(char result[10], uint32_t v) {
    result = "0x00000000"; // length of 0x00000000 = 10

    if (v == 0) {
        return result;
    }
    
    // This is basically hex-only itoa(). We will modulo 16 the value
    // and set the next value in index to that, then bit shift over 4 and repeat.
    int outIndex = 9;
    
    while (v != 0) {
        int digit = v % 16;
        if (digit < 10) {
            result[outIndex] = '0' + digit;
        } else {
            result[outIndex] = 'a' + (digit - 10);
        }
        v = v >> 4;
        outIndex--;
    }

    return result;
}

void trace_stack(unsigned int max) {
    unsigned short ksyms_are_loaded = is_ksyms_loaded();
    if (ksyms_are_loaded) puts("Call stack:\n");
    else puts("Call stack (ksyms unavailable):\n");
    struct stackframe *stack;
    char result[10];
    asm("mov %%ebp, %0" : "=r"(stack));
    // we stop when we hit NULL  vvvvvvvv, this is set in boot.asm
    for (unsigned int frame = 0; stack && (frame < max); frame++) {
        // TODO: symbol lookup
        if(frame==0) puts("-> ");
        else puts("   ");
        puts(hexify(result, stack->eip));
        if (ksyms_are_loaded) {
            elf32_shdr_t *sym = lookup_ksym_by_address(stack->eip);
            if (sym) {
                puts(" (");
                puts(elf_shdr_string(sym->name));
                puts(")");
            } else {
                puts(" (unknown)");
            }
        }
        puts("\n");
        stack = stack->ebp;
    }
}

// Takes an input rname and outputs code to print it
// Requires the following variables to be set already:
//   char buff[10];
//   cpu_registers_t *regs;
// The parameters are as follows:
// - prefix_string: the string to print before the register name
// - rname: the name of the register (no quotes)
#define DO_PRINT_REGISTER(prefix_string, rname) \
    puts(prefix_string #rname ":"); \
    puts(hexify(buff, regs->rname));

void dump_registers(cpu_registers_t *regs) {
    char buff[10];
    DO_PRINT_REGISTER(" ", eax);
    DO_PRINT_REGISTER("  ", ebx);
    DO_PRINT_REGISTER("  ", ecx);
    DO_PRINT_REGISTER("  ", edx);
    DO_PRINT_REGISTER("  ", esp);
    puts("\n");
    DO_PRINT_REGISTER(" ", ebp);
    DO_PRINT_REGISTER("  ", esi);
    DO_PRINT_REGISTER("  ", edi);
    DO_PRINT_REGISTER("  ", eip);
    DO_PRINT_REGISTER("   ", cs);
    puts("\n");
    DO_PRINT_REGISTER("  ", ds);
    DO_PRINT_REGISTER("   ", es);
    DO_PRINT_REGISTER("   ", fs);
    DO_PRINT_REGISTER("   ", gs);
    DO_PRINT_REGISTER("   ", ss);
    puts("\n\n");
    puts("EFLAGS: ");
    puts(hexify(buff, regs->eflags));
    puts("\n\n");
}

void panic(const char *message, cpu_registers_t *regs) {
    puts("panic(): ");
    puts(message);
    puts("\n");

    // TODO: cpu type and stuff

    dump_registers(regs);

    // TODO: pick a more specific limit value
    trace_stack(5);

    puts("end kernel panic: ");
    puts(message);
    puts("\nhalting system.");
    asm("cli");
    asm("hlt");
}

void oops(const char *message, cpu_registers_t *regs) {
    puts("oops(): ");
    puts(message);
    puts("\n");

    // TODO: cpu type and stuff

    dump_registers(regs);

    // TODO: pick a more specific limit value
    trace_stack(5);

    puts("end oops: ");
    puts(message);
    puts("\n");
}
