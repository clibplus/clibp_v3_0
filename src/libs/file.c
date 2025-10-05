#include "../../headers/clibp.h"

fd_t open_file(const char *filename, FILE_MODE mode)
{
    int fd = _sys_open(filename, mode, 0);
    if(fd == -2)
		print("[ - ] Error, No file or directory\n");

    if(fd < 0)
        return -1;

    return fd;
}

int file_content_size(fd_t fd)
{
	_syscall(_SYS_LSEEK, fd, 0, 2);
	register long sz asm("rax");
	int size = sz;

	_syscall(_SYS_LSEEK, fd, 0, 0);
	return size;
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
