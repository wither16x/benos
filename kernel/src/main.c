#include "lib/types.h"
#include "lib/format.h"
#include "exec/bin.h"
#include "interrupts.h"

ubyte_t g_driveno = 0;

void kmain(void)
{
    __asm mov [g_driveno], dl
    printf("Saved boot drive number: 0x%x.\r\n", g_driveno);

    install_int_benos();
    printf("Installed INT 0x80.\r\n");

    printf("Executing program...\r\n");
    execute_bin("hello.bin");
    printf("Program terminated.\r\n");

    for (;;) {
        __asm {
            hlt
        }
    }
}
