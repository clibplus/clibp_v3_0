#define CLIBP
#define FILE_H
#include "headers/stdlib/init.h"
#include "headers/x86_64.h"

typedef enum mmap_prot {
	__PROT_NONE__ 		= 0,
	__PROT_READ__ 		= 1,
	__PROT_WRITE__ 		= 2,
	__PROT_EXEC__ 		= 4
} mmap_prot;

typedef enum mmap_map {
	__MAP_SHARED__ 		= 1,
	__MAP_PRIVATE__		= 2,
	__MAP_FIXED__		= 16,
	__MAP_ANONYMOUS__ 	= 32
} mmap_map;

typedef struct {
	int 			size;
	int 			len;
	struct chunk 	*next;
} chunk;

any __heap__;
fd_t heapfd;
int DEBUG = 1;

__attribute__((constructor)) void init_heap()
{
	heapfd = _sys_open("__heap__", 2 | 0x40 | 0x400, 0);
	if(heapfd < 0)
		print("[ x ] Error, Unable to start heap...!\n");

	__heap__ = _mmap(0, 4096, __PROT_READ__ | __PROT_WRITE__, __MAP_SHARED__ | __MAP_ANONYMOUS__, heapfd, 0);
	if(__heap__ == ((void *)-1))
		err_n_exit("[ x ] Error, Unable to initialize heap....!\n", 1);

	memzero(__heap__, 4096);
	if(DEBUG)
		print("[ + ] Heap initialized....!\n");
}

__attribute__((destructor)) void unint_heap()
{
	_munmap((unsigned long)__heap__, 4096);
	print("[ + ] Heap Uninitialized....!\n");
}

any allocate(size_t sz, len_t len)
{
	if(!sz || !len)
		return NULL;
}

int sfind_char(const char *buffer, const char ch, int match)
{
    int count = -1;
    for(int i = 0; count != match; i++) {
        if(buffer[i] == ch)
            count++;
    }

    return count;
}

int main(int argc, char *argv[]) {
    int ARGC = 0;
    char *ARGV[50] = {0};

    char path[255] = {0};
    mem_cpy(path, "/proc/", 6);
    int sz = 6;
    
    register long sysnum asm("rax") = 39; // getpid
    asm volatile("syscall");

    register long ppid asm("rax"); // PID is now in rax

    // Optional: write PID to stdout
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

    stra(path, buf);
    path[sz] = '/';

    char *ending = "/cmdline";
    for(int i = 0; i < 8; i++)
        path[sz + i] = ending[i];

    print(path);

    char BUFFER[1024] = {0};
    fd_t fd = open_file(path, O_RDONLY);

    int y = file_read(fd, BUFFER, 1024);
    print("\n");
    print(BUFFER);
    _syscall(8, fd, y, 1);

    y = file_read(fd, BUFFER, 1024);
    print("\n");
    print(BUFFER);
    _syscall(0, 0, (long)path, 3);

    int pos, count = 0;
    while((pos = sfind_char(BUFFER, '\0', count)) != -1) {
        ARGV[count] = BUFFER + pos + 1;
        count++;
        ARGC++;
    }

    for(int i = 0; i < ARGC; i++) {
        print(ARGV[i]);
    }
	return 0;
}
