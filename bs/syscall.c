void __syscall(long syscall, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6)
{
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