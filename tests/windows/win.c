#include <fsl_win.h>

int main()
{
	char v[30] = {0};
	mem_cpy(v, "Hello World!", 12);
	printf("-> %s", v);
	return 0;
}
