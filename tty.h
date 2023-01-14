#pragma once

// TODO: printf
void put_newline(void);
void disable_cursor(void);
void puts(const char *);
void putc(char);
void putc_colored(char, unsigned short);
void clear(void);
void tty_init(void);
void vga_scroll(void);