/*

	Get Command Arguments From Linux
*/
#define NULL 0
#define CLIBP
int str_len();
void mem_cpy();
void __syscall(long syscall, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6);

void execute(char *app, char **args)
{
	if(!app || !args)
		return;

	int pid;
	__syscall(57, -1, -1, -1, -1, -1, -1);
	register long r asm("rax");
	pid = r;

	if(pid == 0)
	{
		__syscall(59, (long)app, (long)args, 0, -1, -1, -1);
	} else if(pid > 0) {
		__syscall(61, pid, 0, 0, -1, -1, -1);
	} else {
		__syscall(1, 1, (long)"fork error\n", 7, -1, -1, -1);
	}
}

void _mem_cpy(char *buffer, const char *data, int sz) {
	int len = str_len(buffer);
	for(int i = len; i < sz; i++) {
		buffer[i] = data[i];
	}
}

static void print(const char *buff) { __syscall(1, 1, (long)buff, str_len(buff), -1, -1, -1); }
static void printsz(const char *buff, int sz) { __syscall(1, 1, (long)buff, sz, -1, -1, -1); }
static void printc(const char ch) { char BUFF[2]; BUFF[0] = ch; BUFF[1] = '\n'; print(BUFF); }
static void printi(int num) { char BUFF[4]; BUFF[0] = '0' + num; BUFF[1] = '\n'; print(BUFF); }

int get_cmd_info(char *buffer) {
	__syscall(2, (long)"/proc/self/cmdline", 0, 0, -1, -1, -1);
	register long open asm("rax");
	if(open < 0)
		return -1;

	int fd = open;
	print("File Opened, FD: "), printi(fd);

	/* Get Content Length */
    char BUFF[255] = {0};
    __syscall(0, fd, (long)BUFF, 255, -1, -1, -1);

	_mem_cpy(buffer, BUFF, 255);
	__syscall(3, fd, -1, -1, -1, -1, -1);

	return 1;
}

typedef int pid_t;
int main()
{
	char BUFF[255] = {0};
	int count = get_cmd_info(BUFF);

	char *ptr = BUFF;
	int offset = 0, args = 0;
	for(int pos = 0, sz = 0; ((char *)(ptr + offset))[i] != NULL; i++, (pos = find_char(ptr + offset, '\0', args)), sz = str_len(ptr + offset)) {
		print(((char *)(ptr + offset))[i]);
		ptr += sz;
		args++;
	}
	printsz(BUFF, 255);

//	__syscall(1, 1, (long)BUFF, count, -1, -1, -1);

	execute("/usr/bin/touch", (char *[]){"/usr/bin/touch", "dickbob.txt", 0});
	__syscall(1, 1, (long)"Done\n", 5, -1, -1, -1);
	return 0;
}
