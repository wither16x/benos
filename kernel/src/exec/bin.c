#include "exec/bin.h"
#include "fs/fat12.h"
#include "lib/format.h"

int execute_bin(const char *pathname)
{
    if (fat12_read_file(pathname, (void *)BIN_ADDRESS) == -1) {
        printf("File not found: %s\r\n", pathname);
        return -1;
    }

    void (*entry)() = (void (*)())BIN_ADDRESS;
    entry();

    return 0;
}
