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

    for (unsigned int oldIndex = VGA_COLUMNS; oldIndex < VGA_BUFFER_CHARS;
         oldIndex++, newIndex++) {
        terminal_buffer[newIndex] = terminal_buffer[oldIndex];
    }
    // Write an empty line.
    for (; newIndex < VGA_BUFFER_CHARS; newIndex++) {
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

void vga_putc_provider(char c, unsigned short color) {
    if (c == '\n') {
        vga_row++;
    } else if (c == '\r') {
        vga_column = 0;
    } else {
        // TODO: separate fg and bg colors
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

void vga_clear_provider(void) {
    // TODO: separate function to reset position?
    vga_row = 0;
    vga_column = 0;
    for (int i = 0; i < VGA_BUFFER_CHARS; i++) {
        terminal_buffer[i] = 0;
    }
}


void vga_init(void) {
    terminal_buffer = (unsigned short *)VGA_ADDRESS;
    vga_row = 0;
    vga_column = 0;
}
