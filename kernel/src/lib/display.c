#include "lib/display.h"
#include "bios/display.h"

void putchar(char ch)
{
    bios_teletype_putchar(ch);
}

void print(const char *str)
{
    while (*str)
        putchar(*str++);
}
