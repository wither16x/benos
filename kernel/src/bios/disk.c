#include "bios/disk.h"

int bios_reset_disk(ubyte_t driveno)
{
    int err = 0;

    __asm {
        xor ax, ax
        mov dl, driveno
        int 0x13
        sbb ax, ax
        mov err, ax
    }

    return err;
}

int bios_read_sectors(void *buf, ubyte_t count, ubyte_t cylinder, ubyte_t head,
    ubyte_t sector, ubyte_t driveno)
{
    int err = 0;
    ubyte_t ch_ = cylinder & 0xff;
    ubyte_t cl_ = (sector & 0x3f) | ((cylinder >> 2) & 0xc0);

    __asm {
        push es
        push ds
        pop es
        mov bx, buf
        mov al, count
        mov ch, ch_
        mov cl, cl_
        mov dh, head
        mov dl, driveno
        mov ah, 0x02
        int 0x13
        sbb ax, ax
        mov err, ax
        pop es
    }

    return err;
}
