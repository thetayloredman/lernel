#include <ports.h>

void out(unsigned short port, char byte) {
    asm volatile ("out %0, %1"::"a" (byte), "Nd"(port));
}
