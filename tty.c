#include <tty.h>

#include <vga.h>
#include <ports.h>

unsigned short *terminal_buffer;
unsigned int vga_row;
unsigned int vga_column;

unsigned int get_vga_index(void) {
    return (vga_row * VGA_COLUMNS) + vga_column;
}

void vga_scroll(void) {
    // Scroll the entire vga display down a column.

    // We will loop over every character except the first VGA_COLUMNS size.
    unsigned int newIndex = 0;
    for (unsigned int oldIndex = VGA_COLUMNS; oldIndex < VGA_BUFFER_SIZE; oldIndex++, newIndex++) {
        terminal_buffer[newIndex] = terminal_buffer[oldIndex];
    }
    // Write an empty line.
    for (; newIndex < VGA_BUFFER_SIZE; newIndex++) {
        terminal_buffer[newIndex] = 0;
    }

    // Subtract our row.
    vga_row--;
}

void disable_cursor(void) {
    // disables the flashing vga cursor thingy
    out(0x3D4, 0x0A);
    out(0x3D5, 0x20);
}

void putc_colored(char c, unsigned short color) {
    if (c == '\n') putc('\r');

    if (c == '\n') {
        vga_row++;
    } else if (c == '\r') {
        vga_column = 0;
    }
    else {
        terminal_buffer[get_vga_index()] = (unsigned short)c | color << 8;
        vga_column++;
        if (vga_column >= VGA_COLUMNS) {
            vga_column = 0;
            vga_row++;
        }
        if (vga_row >= VGA_ROWS) {
            vga_scroll();
        }
    }
}

void putc(char c) {
    putc_colored(c, WHITE);
}

void puts(const char *s) {
    int index = 0;
    while (s[index]) {
        putc(s[index]);
        index++;
    }
}

void clear(void) {
    for (int i = 0; i < VGA_BUFFER_SIZE; i++) {
        terminal_buffer[i] = 0;
    }
    vga_row = 0;
    vga_column = 0;
}

void tty_init(void) {
    terminal_buffer = (unsigned short *)VGA_ADDRESS;
    vga_row = 0;
    vga_column = 0;
}
