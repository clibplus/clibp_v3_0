#include <fsl.h>

int entry()
{
    int test = 0;
    while(1)
    {
        long n = __syscall__((long)&test, sizeof(test), 0, -1, -1, -1, _SYS_GETRANDOM);
        _printf("%d\n", (ptr)&test);
        _sleep(1);
    }
    return 0;
}