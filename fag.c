#include "headers/stdlib/init.h"

extern void main();

void _syscall(long, long, long, long);
int get_args(char *argv[]);

void main() {
    char *argv[100] = {0};
    int args = get_args(argv);
	print(argv[0]), print("\n");
    _syscall(1, 1, (long)"Hi\n", 3);
    _syscall(60, 0, 0, 0);
}
