#include <tty.h>

#include <vga.h>
#include <ports.h>

void (*tty_putc_provider)(char, unsigned short);
void (*tty_clear_provider)(void);

void putc(char c) {
    if (c == '\n') putc('\r');
    tty_putc_provider(c, WHITE);
}

void puts(const char *s) {
    int index = 0;

    while (s[index]) {
        putc(s[index]);
        index++;
    }
}

void clear(void) {
    tty_clear_provider();
}


void tty_init(void) {
    // nop
}

void tty_set_provider(void (*putc_new)(char, unsigned short), void (*clear_new)(void)) {
    tty_putc_provider = putc_new;
    tty_clear_provider = clear_new;
}