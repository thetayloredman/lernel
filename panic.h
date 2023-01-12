#pragma once
#include <ints.h>

char *hexify(char[10], uint32_t); // TODO: relocate to a new file
// TODO: format strings like printf?
void panic(const char *);
void oops(const char *);
void trace_stack(unsigned int);
void dump_registers(void);