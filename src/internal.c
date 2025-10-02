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

none printnum(int num)
{
	char BUFF[100] = {0};
	int temp = num;
}

none printc(const char ch)
{
	char BUFF[2] = {0};
	BUFF[0] = ch;
	print(BUFF);
}

none printi(int num)
{
	char BUFF[5] = {0};
	BUFF[0] = '0' + num;
	print(BUFF);
}

none _printi(int num)
{
	int temp = num, c = 0;
	char BUFF[500] = {0};
	while(temp)
	{
		BUFF[c++] = '0' + (temp % 10);
		temp /= 10;
	}

	for(int i = 0; i < c; i++)
	{
		char t = BUFF[i], n = BUFF[--c];
		BUFF[i] = n;
		BUFF[c] = t;
	}

	print(BUFF);
}

none print(const str buff)
{
	_syscall(1, 1, (unsigned long)buff, str_len(buff));
}
