#pragma once

typedef struct {
	int sec, nsec;
} sleep_t;

extern void _syscall(long sys, long arg1, long arg2, long arg3);
extern long _sys_read(unsigned int fd, char *buff, unsigned long count);
extern long _sys_write(unsigned int fd, const char *buff, unsigned long count);
extern long _sys_open(const char *filename, int flags, int mode);
extern long _sys_close(unsigned int fd);
extern void *_mmap(unsigned long addr, unsigned long len, unsigned long prot, unsigned long flags, unsigned long fd, unsigned long off);
extern void _munmap(unsigned long addr, unsigned long len);
extern void _sys_nanosleep(sleep_t *rqtp, sleep_t *rmtp);
