#define CLIBP
#define __X86_64_SYSCALLS__
#include "headers/stdlib/init.h"
#include "headers/registers.h"
#include "headers/x86_64.h"

#define SERVER_APP

int main(int argc, char *argv[])
{
    init_mem();
    if(!__is_heap_init__())
    {
        print("ERROR\n");
    }
	fd_t fd = open_file("fag.c", O_RDONLY);
	if(fd < 0)
	{
		print("[ x ] Error, Unable to open file...!\n");
		return 1;
	}

	print("[ + ] Open File: "), printi(fd), print("\n");
	int size = file_content_length(fd);
    print("Content Length: "), _printi(size), print("\n");

	str test = allocate(0, size);
    if(test == NULL) {
        print("[ - ] Error, Unable to allocate memory...!\n");
        return 1;
    }
	file_read(fd, test, size);
	print(test), print("\n");


	// if(__is_ptr_heap__(test))
	// {
	// 	print("Heap Detected\n");
	// }

	pfree(test);
    uninit_mem();
	return 0;
}
