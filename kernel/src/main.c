#include "lib/types.h"
#include "lib/format.h"
#include "exec/bin.h"

ubyte_t g_driveno = 0;

void kmain(void)
{
    __asm mov [g_driveno], dl

    printf("Executing program...\r\n");
    execute_bin("hello.bin");
    printf("Program terminated.\r\n");

    for (;;) {
        __asm {
            hlt
        };
    }
}
