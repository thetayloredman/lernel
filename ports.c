#include <ports.h>
#include <types.h>

void out(unsigned short port, uint8_t byte) {
    asm volatile ("out %0, %1"::"a" (byte), "Nd"(port));
}

uint8_t in(unsigned short port) {
    uint8_t byte;
    asm volatile ("in %1, %0":"=a" (byte):"Nd"(port));
    return byte;
}