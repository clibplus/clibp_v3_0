long _sys_read(unsigned int fd, char *buff, unsigned long count);
long _sys_write(unsigned int fd, const char *buff, unsigned long count);
long _sys_open(const char *filename, int flags, int mode);
long _sys_close(unsigned int fd);
void __syscall(long syscall, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6);

#define NULL 0

int __ARGS__ = 0;
char *__ARGV__[100] = {0};

static int str_len(const char *buff) {
    int count = 0;
    for(int i = 0; buff[i] != '\0'; i++)
        count++;

    return count;
}

static void mem_cpy(char *dest, const char *buff, int sz) {
    for(int i = 0; i < sz; i++) {
        dest[i] = buff[i];
    }
}

static void stra(int start, char *dest, const char *buff, int sz) {
    for(int i = 0; i < sz; i++) {
        dest[start + i] = buff[i];
    }
}

static int open_file(const char *filename, char *mode)
{
    int fd = _sys_open(filename, 0, 0);
    if(fd < 0)
        return -1;

    return fd;
}

static int file_read(int fd, char *buffer, int sz)
{
    return _sys_read(fd, buffer, sz);
}

static int file_write(int fd, const char *buffer, int len)
{
    return _sys_write(fd, buffer, len);
}

static void file_close(int fd)
{
    _sys_close(fd);
}

int count_char(const char *buffer, const char ch)
{
    int count = -1;
    for(int i = 0; buffer[i] != '\0'; i++) {
        if(buffer[i] == ch)
            count++;
    }

    return count;
}

int _count_char(const char *buffer, int len, const char ch) {
	int count = 0;
	for(int i = 0; i < len; i++) {
		if(buffer[i] == ch)
			count++;
	}

	return count;
}

int find_char(const char *buffer, int len, int start, const char ch, int match) {
	if(!buffer || len == 0)
		return -1;

	int count = 0;
	for(int i = start; i < len; i++) {
		if(buffer[i] == ch)
			count++;

		if(count == match)
			return i;
	}

	return -1;
}

void print(const char *buff)
{
	__syscall(1, 1, (unsigned long)buff, str_len(buff), -1, -1, -1);
}

int get_pid() {
	register long p asm("rax") = 39;
	asm volatile("syscall");

	register long pd asm("rax");
	int pid = pd;

	return pid;
}

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
    } else {                                                                                                                                                __syscall(1, 1, (long)"fork error\n", 7, -1, -1, -1);
    }
}

// TODO; Optimize
void _start() {
    int ARGC = 0;
    char *ARGV[50] = {0};

    char path[255] = {0};
    mem_cpy(path, "/proc/", 6);
    int sz = 6;

    register long sysnum asm("rax") = 39;
    asm volatile("syscall");

    register long ppid asm("rax");

    char buf[255] = {0};
    int len = 0;
    long tmp = ppid;
    do {
        path[sz + len++] = '0' + tmp % 10;
        tmp /= 10;
    } while(tmp);

    for (long i = 0; i < len / 2; i++) {
        char t = path[sz + i];
        path[sz + i] = path[sz + len - i - 1];
        path[sz + len - i - 1] = t;
    }
    sz += len;

    stra(sz, path, buf, len);

    char *ending = "/cmdline";
    for(int i = 0; i < 8; i++)
        path[sz + i] = ending[i];

    char BUFF[1024] = {0};
    int fd = open_file(path, "r");
    int y = file_read(fd, BUFF, 1024);

	char *ptr = BUFF;

	int offset = 0;
	for(int i = 0; i < 3; i++) {
		int next = str_len(ptr) + 1;
//		mem_cpy(__ARGV__[i], ptr, next);
		__ARGS__++;
		ptr += next;
	}

	for(int i = 0; i < __ARGS__; i++) {
		__syscall(1, 1, (long)__ARGV__[i], 10, -1, -1, -1);
	}

    int sec_offset = str_len(ptr); // arg1
    ptr += sec_offset + 1;

    char SRC_CODE_FILE[20] = {0};
    mem_cpy(SRC_CODE_FILE, ptr, str_len(BUFF));
    int src_len = str_len(SRC_CODE_FILE);

	int sec = str_len(ptr) + 1;
	ptr += sec;
	sec = str_len(ptr) + 1;
	ptr += sec;

    char OUTPUT[10] = {0};
    mem_cpy(OUTPUT, ptr, sec);

    if(SRC_CODE_FILE[src_len - 1] == 'c') {
		print("[ + ] Compiling: "), print(SRC_CODE_FILE), print(" to ");
		print(OUTPUT), print("....!\n");

		char COPY[255] = {0};
		mem_cpy(COPY, SRC_CODE_FILE, src_len);
		COPY[src_len - 1] = 'o';

        char *n[9] = {"/usr/bin/gcc", "-c", SRC_CODE_FILE, "-o", COPY, "-L", "build/syscall.o", "-nostdlib", NULL};
//        register long rax asm("rax") = 59;
//        register long rdi asm("rdi") = (long)"/usr/bin/gcc";
//        register long rsi asm("rsi") = (long)n;
//        register long rdx asm("rdx") = (long)0;
		execute(n[0], n);

        asm("syscall");
		register int ret asm("rax");
		if(ret < 0)
			__syscall(1, 1, (long)"Execve Error\n", 12, -1, -1, -1);
    }

	SRC_CODE_FILE[src_len - 1] = 'o';
    char *n[7] = {"/usr/bin/ld", "-o", OUTPUT, SRC_CODE_FILE, "build/lib.o", "build/syscall.o", NULL};
//    register long rax asm("rax") = 59;
//    register long rdi asm("rdi") = (long)"/usr/bin/ld";
//    register long rsi asm("rsi") = (long)n;
//    register long rdx asm("rdx") = (long)0;
	execute(n[0], n);

	asm("syscall");
	register long ret asm("rax");
	if(ret < 0)
		__syscall(1, 1, (long)"Execve Error\n", 12, -1, -1, -1);
	path[0] = '0' + ret;
	path[1] = '\0';
	print(path);


    __syscall(60, 0, -1, -1, -1, -1, -1);
}
