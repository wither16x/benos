#ifndef BIOS_DISK_H_
#define BIOS_DISK_H_

#include "lib/types.h"

int bios_reset_disk(ubyte_t driveno);
int bios_read_sectors(void *buf, ubyte_t count, ubyte_t cylinder, ubyte_t head,
    ubyte_t sector, ubyte_t driveno);

#endif /* BIOS_DISK_H_ */
