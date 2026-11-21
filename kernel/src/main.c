#include "lib/display.h"

void kmain(void)
{
    print("Hello by OpenWatcomV2!");

    for (;;) {
        __asm {
            hlt
        };
    }
}
