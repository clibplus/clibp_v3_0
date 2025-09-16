extern int main(int argc, char **argv);

void __syscall(long syscall, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6);

int main(int argc, char *argv[]) {
    __syscall(1, 1, (long)argv[0], 1, -1, -1, -1);
    __syscall(1, 1, (long)"Hi\n", 3, -1, -1, -1);
}
