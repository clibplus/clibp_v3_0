#define CLIBP
#define FILE_H
#include "headers/stdlib/init.h"
#include "headers/x86_64.h"

void __syscall(long, long, long, long, long, long, long);

int main(int argc, char *argv[]) {
	__syscall(1, 1, (long)argv[0], 5, -1, -1, -1);
	return 1;
}
