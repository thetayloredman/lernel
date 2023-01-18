#pragma once

#define VGA_ADDRESS 0xB8000

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

// * 2 for 2 bytes each
#define VGA_BUFFER_SIZE VGA_ROWS * VGA_COLUMNS * 2
