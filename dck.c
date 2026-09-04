#include <fsl.h>

int entry()
{
	long long v = 0;
	mem_cpy(&v, "Hello World!\n", 13);
	((char *)&v)[12] = '\0';
	_printf("-> %s", (ptr)&v);
	return 0;
}
