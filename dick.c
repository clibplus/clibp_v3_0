#include <fsl.h>

void *create_anonymous_struct(int *sizes)
{
    int total_size = 0;
    for(int i = 0; sizes[i] != 0; i++) total_size += sizes[i];

    void *p = allocate(0, total_size + 1);

    return p;
}

int entry()
{
    void *p = create_anonymous_struct((int []){
        sizeof(char *),
        sizeof(int),
    });

    struct __attribute__((packed)) {
        char *name; int age;
    } *ptr = p;

    ptr->name = allocate(0, 10);
    mem_cpy(ptr->name, "test\n", 5);

    print(ptr->name);
    return 0;
}