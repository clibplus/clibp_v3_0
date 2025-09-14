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
	int sec, nsec;
} sleep_t;

typedef struct {
	int 			size;
	int 			len;
	struct chunk 	*next;
} chunk;

any __heap__;
static fd_t heapfd;
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

int main(int argc, char *argv[]) {
	char BUFFER[1024] = {0};
	int bytes = get_input(__heap__, 1024);
	_syscall(26, (unsigned long)__heap__, 4095, 4);

	sleep_t sleep = {1, 5000000};
	_syscall(77, (unsigned long)&sleep, 0, 0);
	print("Input: "), print(__heap__);

	char test[] = "Hello World\n";
	print(test);
	return 0;
}
