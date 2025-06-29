#ifndef DISK_H
#define DISK_H

#include <stdint.h>

#define DISK_TYPE_REAL 0

struct disk {
    int type;
    int sector_size;
    int id;
    int fs_private;
    struct filesystem* filesystem;
};

int disk_read_block(struct disk* disk, int lba, int total, void* buf);
struct disk* disk_get(int index);
int disk_read_sector(int lba, int total, void* buf);

#endif
