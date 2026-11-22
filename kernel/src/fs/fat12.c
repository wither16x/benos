/* Dirty FAT12 driver for BenOS */

#include "fs/fat12.h"
#include "bios/disk.h"
#include "lib/format.h"
#include "lib/string.h"
#include "lib/memory.h"
#include "lib/pointers.h"
#include "kernel.h"

#define OEM_LABEL_SIZE (8)
#define VOLUME_LABEL_SIZE (11)
#define FS_NAME_SIZE (8)

/* End Of Directory */
#define EOD (0x00)
#define REMOVED (0xe5)
#define VOLUME_LABEL (0x18)

#define FILENAME_LENGTH (11)
#define SECTOR_SIZE (512)
#define ENTRY_SIZE (32)
/* End Of Cluster */
#define EOC (0x0fff)

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

static struct info bpb;
static ubyte_t fat_buf[SECTOR_SIZE * 12];

static int read_lba(ubyte_t *buf, uword_t lba)
{
    uword_t sector = (lba % bpb.sectors_per_track) + 1;
    uword_t tmp = lba / bpb.sectors_per_track;
    uword_t head = tmp % bpb.head_count;
    uword_t cylinder = tmp / bpb.head_count;
    return bios_read_sectors(buf, 1, cylinder, head, sector, g_driveno);
}

static uword_t next_cluster(uword_t clusterno)
{
    uword_t off = clusterno + clusterno / 2;
    uword_t v = *(uword_t *)&fat_buf[off];
    return (clusterno & 1) ? (v >> 4) : (v & EOC);
}

static inline bool_t same_filenames(const char *name1, const char *name2)
{
    return memcmp(name1, name2, FILENAME_LENGTH) == 0;
}

static int copy_bpb(ubyte_t *buf)
{
    if (bios_read_sectors(buf, 1, 0, 0, 1, g_driveno) == -1)
        return -1;
    memcpy(&bpb, buf, sizeof(bpb));

    /* also check this since we are here */
    if (bpb.sectors_per_fat > 12)
        return -1;

    return 0;
}

/* Convert a standard filename to a 8.3 filename */
static char *convert_filename(char *filename)
{
    static char new_filename[FILENAME_LENGTH];
    int len = strlen(filename);

    int dot_pos = 0;
    for (; dot_pos < len && filename[dot_pos] != '.'; dot_pos++);

    if (dot_pos == 0 || dot_pos > 8)
        return NULL;
    if (dot_pos < len && len - dot_pos - 1 > 3)
        return NULL;

    for (int i = 0; i < FILENAME_LENGTH; i++)
        new_filename[i] = ' ';

    memmove(new_filename, filename, dot_pos);
    if (dot_pos < len)
        memmove(new_filename + 8, filename + dot_pos + 1, len - dot_pos - 1);

    for (int i = 0; i < FILENAME_LENGTH; i++) {
        if (islower(new_filename[i]))
            new_filename[i] = to_upper(new_filename[i]);
    }

    return new_filename;
}

int fat12_read_file(const char *filename, void *buf)
{
    static ubyte_t sector_buf[SECTOR_SIZE];
    static ubyte_t dir_buf[SECTOR_SIZE];

    if (copy_bpb(sector_buf) == -1)
        return -1;

    filename = convert_filename((char *)filename);

    uword_t fat_start = bpb.reserved_for_boot;
    uword_t root_start = fat_start + bpb.number_of_fats * bpb.sectors_per_fat;
    uword_t root_sectors = (bpb.rootdir_entries * ENTRY_SIZE + bpb.bytes_per_sector - 1)
        / bpb.bytes_per_sector;
    uword_t data_start = root_start + root_sectors;

    for (uword_t s = 0; s < bpb.sectors_per_fat; s++) {
        if (read_lba(fat_buf + s * SECTOR_SIZE, fat_start + s) == -1)
            return -1;
    }

    uword_t first_cluster = 0;
    int found = 0;

    for (uword_t sect = 0; sect < root_sectors && !found; sect++) {
        if (read_lba(dir_buf, root_start + sect) == -1)
            return -1;

        for (uword_t i = 0; i < SECTOR_SIZE; i += ENTRY_SIZE) {
            if (dir_buf[i] == EOD)
                return -1;
            if (dir_buf[i] == REMOVED)
                continue;
            if (dir_buf[i + FILENAME_LENGTH] & VOLUME_LABEL)
                continue;

            if (same_filenames(&dir_buf[i], filename)) {
                first_cluster = *(uword_t *)&dir_buf[i + 26];
                found = 1;
                break;
            }
        }
    }

    if (!found)
        return -1;

    ubyte_t *dest = (ubyte_t *)buf;
    uword_t cluster = first_cluster;

    while (cluster >= 2 && cluster < 0xff7) {
        uword_t lba = data_start + (cluster - 2) * bpb.sectors_per_cluster;

        for (ubyte_t i = 0; i < bpb.sectors_per_cluster; i++) {
            if (read_lba(dest, lba + i) == -1)
                return -1;
            dest += bpb.bytes_per_sector;
        }

        cluster = next_cluster(cluster);
    }

    return 0;
}
