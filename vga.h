#pragma once

#define VGA_ADDRESS 0xc00b8000
#define PHYS_VGA_ADDRESS 0xb8000

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define PURPLE 5
#define BROWN 6
#define GRAY 7
#define DARK_GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_CYAN 11
#define LIGHT_RED 12
#define LIGHT_PURPLE 13
#define YELLOW 14
#define WHITE 15

#define VGA_ROWS 25
#define VGA_COLUMNS 80

#define VGA_BUFFER_CHARS VGA_ROWS * VGA_COLUMNS
// * 2 for 2 bytes each
#define VGA_BUFFER_SIZE VGA_BUFFER_CHARS * 2

void disable_cursor(void);
void vga_putc_provider(char c, unsigned short color);
void vga_clear_provider(void);
void vga_init(void);