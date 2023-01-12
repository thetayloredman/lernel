#pragma once

#define VGA_ADDRESS 0xB8000

#define BLACK 0
#define GREEN 2
#define RED 4
#define YELLOW 14
#define WHITE_COLOR 15

#define VGA_ROWS 25
#define VGA_COLUMNS 80

// * 2 for 2 bytes each
#define VGA_BUFFER_SIZE VGA_ROWS * VGA_COLUMNS * 2