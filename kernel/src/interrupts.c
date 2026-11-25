#include "interrupts.h"

extern void handle_interrupt(void);

void install_int_benos(void)
{
    unsigned old_seg = 0;
    unsigned old_off = 0;

    __asm {
        cli
        xor ax, ax
        mov es, ax

        mov  ax, es:[BENOS_INTNO * 4]
        mov  old_off, ax
        mov  ax, es:[BENOS_INTNO * 4 + 2]
        mov  old_seg, ax

        mov  word ptr es:[BENOS_INTNO * 4], offset handle_interrupt
        mov  es:[BENOS_INTNO * 4 + 2], cs
        sti
    }
}
