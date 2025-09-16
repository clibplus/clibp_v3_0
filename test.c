// /home/algo/.local/lib/python3.13/site-packages/keystone/libkeystone.so


extern int my_main();

// Separate Function due to ASM execution in precedure order
void _syscall(long syscall, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6) {
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

    _syscall(syscall,
        __main__.rdi,
        __main__.rsi,
        __main__.rdx,
        __main__.r10,
        __main__.r8,
        __main__.r9
    );
}

#define sys(syscall, ...) \
    _sys_(syscall, (x86_64_registers){ __VA_ARGS__ })

int main(void) {
    my_main();
    char BUFF[50] = {0};
    BUFF[0] = 'H';
    BUFF[1] = 'i';
    BUFF[2] = '\n';
    _syscall(1, 1, (long)BUFF, 3, -1, -1, -1);
    _syscall(60, 0, -1, -1, -1, -1, -1);
    // sys(1, .rdi = 1, .rsi = (long)BUFF, .rdx = 3);
    // sys(60, .rdi = 0);
    return 0;
}
