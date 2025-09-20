void ___syscall(long syscall, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6) {
    register long sys asm("rax") = syscall;

    register long a1 asm("rdi") = arg1;
    if(!arg2 == -1)
    {
        asm("syscall");
        return;
    }

    register long a2 asm("rsi") = arg2;
    if(!arg3 == -1)
    {
        asm("syscall");
        return;
    }

    register long a3 asm("rdx") = arg3;
    if(!arg4 == -1)
    {
        asm("syscall");
        return;
    }

    register long a4 asm("r10") = arg4;
    if(!arg5 == -1)
    {
        asm("syscall");
        return;
    }

    register long a5 asm("r8") = arg5;
    if(arg6 == -1)
    {
        asm("syscall");
        return;
    }

    register long a6 asm("r9") = arg6;
    asm("syscall");
}

typedef struct {
    long rdi;
    long rsi;
    long rdx;
    long r10;
    long r8;
    long r9;
} x86_64_registers;

x86_64_registers __main__;
void set_struct() { __main__ = (x86_64_registers){-1}; }

void _sys_(long syscall, x86_64_registers regs) {
    set_struct();
    if(regs.rdi > -1)
        __main__.rdi = regs.rdi;

    if(regs.rsi > -1)
        __main__.rsi = regs.rsi;

    if(regs.rdx > -1)
        __main__.rdx = regs.rdx;

    if(regs.r10 > -1)
        __main__.r10 = regs.r10;

    if(regs.r8 > -1)
        __main__.r8 = regs.r8;

    if(regs.r9 > -1)
        __main__.r9 = regs.r9;

    ___syscall(syscall,
        __main__.rdi,
        __main__.rsi,
        __main__.rdx,
        __main__.r10,
        __main__.r8,
        __main__.r9
    );
}

int __get_return__() {
    register long ret asm("rax");
    int r = ret;
    return r;
}

/*
    
    #define sys(syscall, ...)
    
    - Execute Syscalls Using Optional Registers
*/
#define sys(syscall, ...) \
    _sys_(syscall, (x86_64_registers){ __VA_ARGS__ })

static int str_len(const char *restrict buffer) {
    int count = 0;
    for(int i = 0; buffer[i] != '\0'; i++)
        count++;

    return count;
}

/*
    void print(const char *restrict buffer)

    - Output a buffer to stdout
*/
void print(const char *buffer) {
    sys(1, .rdi = 1, .rsi = (long)buffer, .rdx = str_len(buffer));
}

struct {
	void (*log) (const char *);
} console = {
	.log = print
};

int main(void) {
	console.log("Hi\n");
    char BUFF[50] = {0};
    BUFF[0] = 'H';
    BUFF[1] = 'i';
    BUFF[2] = '\n';
    sys(1, .rdi = 1, .rsi = (long)BUFF, .rdx = 3);

    char fag[5] = "fag.c";
    sys(2, .rdi = (long)fag, .rsi = 0, .rdx = 0);
    register long ret asm("rax");
    int fd = ret;
    if(fd < 0)
    {
        sys(1, .rdi = 1, .rsi = (long)"Error\n", .rdx = 6);
        return 1;
    }

    if(fd > 9) {
        print("OVER\n");
    }
    BUFF[0] = '0' + fd;
    BUFF[1] = '\n';
    
    sys(1, .rdi = 1, .rsi = (long)"Opened File @ ", .rdx = 14);
    sys(1, .rdi = 1, .rsi = (long)BUFF, .rdx = 2);

    return 0;
}
