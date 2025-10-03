#define CLIBP
#define __X86_64_SYSCALLS__
#define _STANDARD_MEM_SZ_
#include "headers/stdlib/init.h"
#include "headers/registers.h"
#include "headers/x86_64.h"
#include "headers/allocator.h"
#include "headers/stdlib/init.h"
#define SERVER_APP

void entry()
{
	HEAP_DEBUG = 1;
	init_mem();
    if(!__is_heap_init__())
    {
        print("ERROR\n");
    }

	fd_t fd = open_file("t.c", O_RDONLY);
	if(fd <= 0)
	{
		print("[ x ] Error, Unable to open file...!\n");
		__exit(1);
	}

	print("[ + ] Open File: "), printi(fd), print("\n");
	int size = file_content_length(fd);
    print("Content Length: "), _printi(size), print("\n");

	print("Allocating....\n");
	str test = allocate(0, size + 1);
    if(test == NULL) {
        print("[ - ] Error, Unable to allocate memory...!\n");
		__exit(1);
    }
    print("[ + ] Reading....\n");
	file_read(fd, test, size);

	int c = str_len(test);
	print("Len: "), printi(c);

	print(test), print("\n");


	// if(__is_ptr_heap__(test))
	// {
	// 	print("Heap Detected\n");
	// }

	pfree(test);
	__exit(0);
	uninit_mem();
}
