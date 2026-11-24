#include "lib/types.h"
#include "lib/format.h"
#include "exec/bin.h"

ubyte_t g_driveno = 0;
extern void handle_interrupt(void);

void kmain(void)
{
    __asm mov [g_driveno], dl

    // Install the handler for INT 0x80
    __asm {
        cli
        xor ax, ax
        mov es, ax

        mov  ax, es:[0x80 * 4]
        mov  old_off, ax
        mov  ax, es:[0x80 * 4 + 2]
        mov  old_seg, ax

        mov  word ptr es:[0x80 * 4], offset handle_interrupt
        mov  es:[0x80 * 4 + 2], cs
        sti
    }

    printf("Executing program...\r\n");
    execute_bin("hello.bin");
    printf("Program terminated.\r\n");

    for (;;) {
        __asm {
            hlt
        }
    }
}
