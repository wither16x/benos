#include "fs/fat12.h"
#include "bios/disk.h"
#include "lib/format.h"
#include "kernel.h"

#define OEM_LABEL_SIZE (8)
#define VOLUME_LABEL_SIZE (11)
#define FS_NAME_SIZE (8)

#pragma pack(push, 1)
struct info {
    ubyte_t jmp_nop[3];
    ubyte_t oem_label[OEM_LABEL_SIZE];
    uword_t bytes_per_sector;
    ubyte_t sectors_per_cluster;
    uword_t reserved_for_boot;
    ubyte_t number_of_fats;
    uword_t rootdir_entries;
    uword_t logical_sectors;
    ubyte_t media_byte;
    uword_t sectors_per_fat;
    uword_t sectors_per_track;
    uword_t head_count;
    udword_t hidden_sectors;
    udword_t large_sectors;
    uword_t driveno;
    ubyte_t signature;
    udword_t volume_id;
    ubyte_t volume_label[VOLUME_LABEL_SIZE];
    ubyte_t filesystem[FS_NAME_SIZE];
};
#pragma pack(pop)

int fat12_read_file(const char *filename, void *buf)
{
    static ubyte_t sector[512];
    struct info *inf = (struct info *)sector;
    int result = bios_read_sectors(inf, 1, 0, 0, 1, g_driveno);
    if (result == -1)
        return -1;

    inf->oem_label[OEM_LABEL_SIZE - 1] = '\0';
    inf->filesystem[FS_NAME_SIZE - 1] = '\0';
    inf->volume_label[VOLUME_LABEL_SIZE - 1] = '\0';

    printf("OEM label: %s\r\n", inf->oem_label);
    printf("Filesystem: %s\r\n", inf->filesystem);
    printf("Volume label: %s\r\n", inf->volume_label);
    printf("There are %d bytes per sector.\r\n", inf->bytes_per_sector);
    printf("Signature is 0x%x.\r\n", inf->signature);

    return 0;
}
