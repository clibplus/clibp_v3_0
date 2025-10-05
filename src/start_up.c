#include "../headers/clibp.h"

static void _mem_cpy(char *dest, const char *buffer, int len)
{
    for(int i = 0; i < len; i++)
    {
        dest[i] = buffer[i];
    }
}

static int _str_len(const char *buffer)
{
    int count = 0;
    for(int i = 0; buffer[i] != '\0'; i++)
    {
        count++;
    }

    return count;
}

static int get_cmd_info(char *buffer) {
    _syscall(2, (long)"/proc/self/cmdline", 0, 0);
    register long open asm("rax");
    if(open <= 0)
    {
        return -1;
    }
    
    int fd = open;
    char BUFFER[255] = {0};
    _syscall(0, fd, (long)BUFFER, 255);
    register long bts asm("rax");

    int bytes = bts;
    _mem_cpy(buffer, BUFFER, bytes);

    _syscall(3, fd, 0, 0);
    return bytes;
}

static int _count_char(const char *buffer, const char ch, int sz) {
    int count = 0;
    for(int i = 0; i < sz; i++)
        if(buffer[i] == ch)
            count++;

    return count;
}

static int _find_char(const char *buffer, const char ch, int sz, int match) {
    int count = 0;
    for(int i = 0; i < sz; i++) {
        if(buffer[i] == ch)
            count++;

        if(count == match)
            return i;
    }

    return -1;
}

int get_pid() {
    _syscall(39, 0, 0, 0);
    volatile register long sys asm("rax");

    return sys;
}

int get_args(char *argv[]) {
    int args = 0;
    char BUFFER[1024] = {0};
    int count = get_cmd_info(BUFFER);

    char *ptr = BUFFER;
    int test = _count_char(BUFFER, '\0', count);

    for(int i = 0, match = 0, last = 0; i < test; i++) {
        int pos = _find_char(ptr, '\0', count, match++);
        if(pos == -1)
            break;

        argv[args++] = (char *)(ptr + (pos + 1));
    }

    return args;
}

