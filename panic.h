#pragma once

#include <regs.h>
#include <types.h>
#include <config.h>

char *hexify_word(char[6], uint16_t); // TODO: relocate to a new file
char *hexify_double(char[10], uint32_t); // TODO: relocate to a new file
// TODO: format strings like printf?
void panic(const char *, cpu_registers_t *);
void oops(const char *, cpu_registers_t *);

#if defined(LERNEL_PANIC_DUMP_STACK) || defined(LERNEL_OOPS_DUMP_STACK)
    void trace_stack(unsigned int);
#endif

#if defined(LERNEL_PANIC_DUMP_REGISTERS) || defined(LERNEL_OOPS_DUMP_REGISTERS)
    void dump_registers(cpu_registers_t *);
#endif