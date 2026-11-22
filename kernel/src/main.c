#include "fs/fat12.h"
#include "lib/types.h"
#include "lib/format.h"

ubyte_t g_driveno = 0;

void kmain(void)
{
    __asm mov [g_driveno], dl

    for (;;) {
        __asm {
            hlt
        };
    }
}
