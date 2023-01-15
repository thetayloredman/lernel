#include <panic.h>

#include <tty.h>
#include <types.h>
#include <stackframe.h>
#include <regs.h>
#include <ksyms.h>
#include <strings.h>

char *hexify_double(char result[10], uint32_t v) {
    strcpy(result, "0x00000000");

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

char *hexify_word(char result[6], uint16_t v) {
    strcpy(result, "0x0000");

    if (v == 0) {
        return result;
    }

    int outIndex = 5;

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
    unsigned short ksyms_loaded = is_ksyms_loaded();
    if (ksyms_loaded) puts("Call stack:\n");
    else puts("Call stack (no symbol table information available):\n");
    struct stackframe *stack;
    char result[10];
    asm("mov %%ebp, %0" : "=r"(stack));
    // we stop when we hit NULL  vvvvvvvv, this is set in boot.asm
    for (unsigned int frame = 0; stack && (frame < max); frame++) {
        if(frame==0) puts("-> ");
        else puts("   ");
        puts(hexify_double(result, stack->eip));
        if (ksyms_loaded) {
            elf32_sym_t *sym = get_ksym_by_address(stack->eip);
            if (sym) {
                puts(" (");
                puts((char *)(get_shdr_string(sym->name)));
                puts("+");
                uint32_t diff = stack->eip - sym->value;
                if (diff > 0xFFFF) {
                    char smaller_buffer[6];
                    puts(hexify_double(smaller_buffer, diff));
                } else {
                    puts(hexify_word(result, diff));
                }
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
// - rtype: word or double, no quotes (which hexify func to use)
#if defined(LERNEL_PANIC_DUMP_REGISTERS) || defined(LERNEL_OOPS_DUMP_REGISTERS)
#   define DO_PRINT_REGISTER(prefix_string, rname, rtype) \
        puts(prefix_string #rname ":"); \
        puts(hexify_##rtype(buff, regs->rname));

    void dump_registers(cpu_registers_t *regs) {
        char buff[10];
        DO_PRINT_REGISTER(" ", eax, double);
        DO_PRINT_REGISTER("  ", ebx, double);
        DO_PRINT_REGISTER("  ", ecx, double);
        DO_PRINT_REGISTER("  ", edx, double);
        DO_PRINT_REGISTER("  ", esp, double);
        puts("\n");
        DO_PRINT_REGISTER(" ", ebp, double);
        DO_PRINT_REGISTER("  ", esi, double);
        DO_PRINT_REGISTER("  ", edi, double);
        DO_PRINT_REGISTER("  ", eip, double);
        DO_PRINT_REGISTER("   ", cs, word);
        puts("\n");
        DO_PRINT_REGISTER("  ", ds, word);
        DO_PRINT_REGISTER("       ", es, word);
        DO_PRINT_REGISTER("       ", fs, word);
        DO_PRINT_REGISTER("       ", gs, word);
        DO_PRINT_REGISTER("       ", ss, word);
        puts("\n\n");
        puts("EFLAGS: ");
        puts(hexify_double(buff, regs->eflags));
        puts("\n\n");
    }
#endif

void panic(const char *message, cpu_registers_t *regs) {
    puts("panic(): ");
    puts(message);
    puts("\n");

    // TODO: cpu type and stuff

#   ifdef LERNEL_PANIC_DUMP_REGISTERS
        dump_registers(regs);
#   endif

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

#   ifdef LERNEL_OOPS_DUMP_REGISTERS
        dump_registers(regs);
#   endif

    // TODO: pick a more specific limit value
    trace_stack(5);

    puts("end oops: ");
    puts(message);
    puts("\n");
}
