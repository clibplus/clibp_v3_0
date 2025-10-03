
#define _STANDARD_MEM_SZ_		// Standard Heap Cap
#define DISABLE_AUTO_ARCH_DET	// Disable Arch Auto Detection
#define ___x86___				// Force to use x86
#include "headers/clibp.h"		// Include CLIBP

/* Keep Types Stored */
#define SERVER_APP				// Keep All TYPES stored in metadata

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
	uninit_mem();
	__exit(0);
}
