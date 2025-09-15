#include "../headers/stdlib/init.h"

none memzero(any ptr, size_t size)
{
	mem_set(ptr, 0, size);
}

none mem_cpy(any dest, any src, size_t size)
{
	for(int i = 0; i < size; i++)
	{
		((char *)dest)[i] = ((char *)src)[i];
	}
}

none mem_set(any ptr, char ch, size_t size)
{
	for(int i = 0; i < size; i++)
	{
		((char *)ptr)[i] = ch;
	}
}
