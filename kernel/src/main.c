#include "fs/fat12.h"
#include "lib/types.h"

ubyte_t g_driveno = 0;

void kmain(void)
{
    __asm mov [g_driveno], dl

    char buf[512];
    fat12_read_file("LICENSE TXT", buf);

    for (;;) {
        __asm {
            hlt
        };
    }
}
