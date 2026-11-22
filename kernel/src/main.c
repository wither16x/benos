#include "fs/fat12.h"
#include "lib/types.h"
#include "lib/format.h"

ubyte_t g_driveno = 0;

void kmain(void)
{
    __asm mov [g_driveno], dl

    static char buf[2048];
    int result = fat12_read_file("LICENSE TXT", buf);
    if (result == -1)
        printf("Failed to read file.\r\n");
    printf("%s", buf);

    for (;;) {
        __asm {
            hlt
        };
    }
}
