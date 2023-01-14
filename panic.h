#pragma once
#include <ints.h>
#include <regs.h>

char *hexify(char[10], uint32_t); // TODO: relocate to a new file
// TODO: format strings like printf?
void panic(const char *, cpu_registers_t *);
void oops(const char *, cpu_registers_t *);
void trace_stack(unsigned int);
void dump_registers(cpu_registers_t *);