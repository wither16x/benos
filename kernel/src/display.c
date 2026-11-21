#include "display.h"

void putchar(char ch_)
{
    __asm {
        mov ah, 0x0e
        mov al, ch_
        xor bx, bx
        int 0x10
    }
}

void print(const char *str)
{
    while (*str)
        putchar(*str++);
}
