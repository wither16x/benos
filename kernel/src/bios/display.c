#include "bios/display.h"

void bios_clear_screen(void)
{
    __asm {
        xor ah, ah
        mov al, 3
        int 0x10
    }
}

void bios_teletype_putchar(char ch_)
{
    __asm {
        mov ah, 0x0e
        mov al, ch_
        xor bx, bx
        int 0x10
    }
}
