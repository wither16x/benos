#include "fs/fat12.h"
#include "lib/types.h"
#include "lib/format.h"

ubyte_t g_driveno = 0;

void kmain(void)
{
    __asm mov [g_driveno], dl

    printf("Executing program...\r\n");

    int result = fat12_read_file("hello.bin", (void *)0x8000);
    if (result == -1) {
        printf("File not found\r\n");
        goto hang;
    }

    void (*entry)() = (void (*)())0x8000;
    entry();

    printf("Program terminated.\r\n");

hang:
    for (;;) {
        __asm {
            hlt
        };
    }
}
