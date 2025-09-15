#define CLIBP
#include "../../headers/stdlib/init.h"

fd_t open_file(const char *filename, FILE_MODE mode)
{
    fd_t fd = _sys_open(filename, mode, 0);
    if(fd < 0)
        return -1;

    return fd;
}

int file_read(fd_t fd, char *buffer, int sz)
{
    return _sys_read(fd, buffer, sz);
}

int file_write(fd_t fd, const char *buffer, len_t len)
{
    return _sys_write(fd, buffer, len);
}

void file_close(fd_t fd)
{
    _sys_close(fd);
}