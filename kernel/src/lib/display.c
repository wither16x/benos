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

void print_until(const char *str, unsigned int limit)
{
    for (unsigned int i = 0; i < limit; i++)
        putchar(str[i]);
}
