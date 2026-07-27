#include <fsl.h>

#include <pthread.h>
#include "../Packages/libweb/v2.0/src/currency.h"

void Counter(cThread *p)
{
	int num = *(int *)((int **)p->args)[0];
	_printf("Entered thread: %d\n", &num);
    for(int i = 0; i < 20; i++)
    {
		_printf("Thread: %d | Counter: %d\n", &p->TID, &i);
        _sleep(1);
    }
	ToggleComplete(p);
}

int main(void) 
{
    uninit_mem();
    set_heap_sz(_HEAP_PAGE_ * 25);
    init_mem();
    // Initalize a Thread Pool with 2 Concurrency (2 threads running @ once)
    ConcurrencyThread *c = CreatePool(5);
    string n = str_dup("skid\n");

    // Add 10 Threads
    for(int i = 0; i < 10; i++)
        AppendThread(c, StartThread(Counter, (void *[]){(void *)to_heap(&i, sizeof(i)), (void *)n, NULL}, 0));

    // Run the thread pool in the background
    pthread_create(&c->PoolThread, NULL, (void *)StartPool, (void *)c);

	_sleep(13);
    // Debugging - Checking Threads
    int i = 0;
    while(1) {
        int running = c->RunningThreads;
        if(c->RunningThreads > c->MAX_THREADS)
                println("[ - ] Max Threads Reached, Waiting...");

        if(running == 0)
            break;

        _printf("[ %d ]: Threads currently running %d/%d\n", (ptr)&i, (ptr)&running, (ptr)&c->RunningThreads);
        _sleep(1);
        i++;
    }

    println("[ + ] Completed, Press any key to exit\n");

    return 0;
}
