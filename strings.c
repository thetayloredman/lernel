#include <strings.h>

void strcpy(char *dest, const char *src) {
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
}

unsigned int strlen(const char *s) {
    unsigned int count = 0;

    while (*s++)
        count++;

    return count;
}

void strncpy(char *dest, const char *src, unsigned int n) {
    while (n-- && *src) {
        *dest++ = *src++;
    }
    *dest = '\0';
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 && *s2 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

int strncmp(const char *s1, const char *s2, unsigned int n) {
    while (n-- && *s1 && *s2 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}
