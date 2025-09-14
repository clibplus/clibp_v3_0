#define STR_H
#include "../headers/stdlib/init.h"
#include "../headers/x86_64.h"

none __exit(int code)
{
	_syscall(60, code, 0, 0);
}

none err_n_exit(const str buff, int code)
{
	if(buff)
		print(buff);

	_syscall(60, code, 0, 0);
}

int get_input(str dest, len_t count) {
	char BUFFER[count];
	int b = _sys_read(0, BUFFER, count);
	mem_cpy(dest, BUFFER, count);
}

none printc(const char ch)
{
	char BUFF[2] = {0};
	BUFF[0] = ch;
	print(BUFF);
}

none print(const str buff)
{
	_syscall(1, 1, (unsigned long)buff, str_len(buff));
}
