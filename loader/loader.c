/*
*
*   [ CLIBP LINKER ]
*
*   GCC-CLIBP LOADER
*
*/
// Load/Declare Function
extern void main();

// Declare External Functions
static void _stra(int start, char *dest, const char *buff, int sz) {
    for(int i = 0; i < sz; i++) {
        dest[start + i] = buff[i];
    }
}

void __syscall(long syscall, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6);

void mem_cpy(char *dest, char *src, int size)
{
	for(int i = 0; i < size; i++)
	{
		((char *)dest)[i] = ((char *)src)[i];
	}
}

int ofile(const char *filename, int mode)
{
    __syscall(2, (long)filename, (long)mode, 0, -1, -1, -1);
    register long fd asm("rax");
    if(fd < 0)
        return -1;

    return fd;
}

int ofread(int fd, char *buffer, int sz)
{
    __syscall(0, (long)fd, (long)buffer, (long)sz, -1, -1, -1);
    register long ret asm("rax");
    return ret;
}

int ofwrite(int fd, const char *buffer, int len)
{
    __syscall(1, (long)fd, (long)buffer, (long)len, -1, -1, -1);
    register long ret asm("rax");
    return ret;
}

void ofclose(int fd)
{
    __syscall(3, fd, -1, -1, -1, -1, -1);
}

void _start() {
    int ARGC = 0;
    char *ARGV[50] = {0};

    char path[255] = {0};
    mem_cpy(path, "/proc/", 6);
    int sz = 6;
    
    register long sysnum asm("rax") = 39;
    asm volatile("syscall");

    register long ppid asm("rax");

    char buf[255] = {0};
    int len = 0;
    long tmp = ppid;
    do {
        path[sz + len++] = '0' + tmp % 10;
        tmp /= 10;
    } while(tmp);
    
    for (long i = 0; i < len / 2; i++) {
        char t = path[sz + i];
        path[sz + i] = path[sz + len - i - 1];
        path[sz + len - i - 1] = t;
    }
    sz += len;
    path[sz] = '\0';

    _stra(sz, path, buf, len);
    path[sz] = '/';

    char *ending = "/cmdline";
    for(int i = 0; i < 8; i++)
        path[sz + i] = ending[i];

    char BUFF[1024] = {0};
    int fd = ofile(path, 0);

    int y = ofread(fd, BUFF, 1024);
    __syscall(8, fd, y, 1, -1, -1, -1);

    main(ARGC, ARGV);
    ofclose(fd);
}
