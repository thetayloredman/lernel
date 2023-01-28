#pragma once

// TODO: printf
void puts(const char *);
void putc(char);
void clear(void);
void tty_init(void);
void tty_set_provider(void (*putc_provider)(char, unsigned short), void (*clear_provider)(void));