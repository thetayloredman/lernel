#pragma once

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef uint32_t uintptr_t;
extern uintptr_t _physical_start;
extern uintptr_t _physical_end;

#define NULL (void *)0
