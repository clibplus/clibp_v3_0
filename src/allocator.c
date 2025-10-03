#define _STANDARD_MEM_SZ_

#include "../headers/clibp.h"

heap_t _HEAP_ = NULL;
static int used_mem = 0;
int HEAP_DEBUG = 0;

void init_mem() {
	__syscall(_SYS_MMAP, 0, _HEAP_PAGE_SZ_, 0x01 | 0x02, 0x02 | 0x20, -1, 0);
	register long ret asm("rax");
	_HEAP_ = (heap_t)ret;
	if(_HEAP_ < 0)
	{
		print("[ - ] Error, Unable to initialize heap....!\n");
	}

	if(HEAP_DEBUG)
		print("[ + ] HEAP INITIALIZED!\n");
}

void uninit_mem() {
	_syscall(11, _HEAP_PAGE_SZ_, 0, 0);
}

int __get_total_mem_used__(void) { return used_mem; }
int __is_heap_init__() { return (_HEAP_ ? 1 : 0); }

static int find_space(int space)
{
    for (int num = 0; num < _HEAP_PAGE_SZ_ - space - 1; num++)
	{
        int free = 1;
        for (int i = 0; i < space; i++)
		{
            if (((char *)_HEAP_)[num + i] != '\0')
			{
                free = 0;
                break;
            }
        }

        if (free)
		{
            return num;
        }
    }

    return -1;
}

any allocate(int sz, int len) {
	if(!len)
		return NULL;

	int space_left = _HEAP_PAGE_SZ_ - used_mem;
	if(space_left < 10) {
		print("[ x ] Error, You cannot create a heap chunk!\n");
		return NULL;
	}

	int mem = (!sz ? len : sz * len) + 4;
	if(space_left < mem)
		return NULL;

	int spot = find_space(mem);
	if(spot == -1)
	{
		print("[ - ] Unable to find space for chunk!\n");
		return NULL;
	}
	any ptr = _HEAP_ + spot;
	((char *)ptr)[0] = sz;
	((char *)ptr)[1] = len;
	((char *)ptr)[2] = 0;

	used_mem += mem;
	mem_set((any)ptr + 4, '-', mem - 4);
	((char *)ptr + 4)[0] = '\0';
	return (any)(ptr + 4);
}

int __get_size__(any ptr)
{
	return !((char *)ptr - 4)[0] ? ((char *)ptr - 4)[1] : ((char *)ptr - 4)[0] * ((char *)ptr - 4)[1];
}

void pfree(any ptr) {
	any original = (char *)ptr - 4;
	int sz = ((char *)ptr - 4)[0];
	int len = ((char *)ptr - 4)[1];
	print("Chunk Size: "), _printi(len);
	mem_set(original, 0, (!sz ? len : sz * len) + 4);
	used_mem -= (!sz ? len : sz * len) + 4;
}
