#pragma once

typedef unsigned long size_t;

#if defined(_STANDARD_MEM_SZ_)
	#define _HEAP_PAGE_SZ_ 4096
#elif defined(_LARGE_MEM_SZ_)
	#define _HEAP_PAGE_SZ_ 4096 * 2
#elif defined(_SMALL_EMBBED_SYSTEM)
	/* 2 KB */
	#define _HEAP_PAGE_SZ_ 1024 * 2
#elif defined(_MID_EMBBED_SYSTEM_)
	/* 8 KB */
	#define _HEAP_PAGE_SZ_ 1024 * 8
#elif defined(_LARGE_EMBBED_SYSTEM_)
	/* 32 KB */
	#define _HEAP_PAGE_SZ_ 1024 * 32
#elif defined(_MAX_ARDUINO_CHIP_)
	/* 256 KB */
	#define _HEAP_PAGE_SZ_ 1024 * 256
#endif

typedef struct {
	int 	size;
	size_t 	length;
	int 	id;
} __meta__;

extern int HEAP_META_SZ;

typedef void *heap_t;
typedef void *any;
typedef char *str;

extern heap_t _HEAP_;
extern int HEAP_DEBUG;

void init_mem();
void uninit_mem();
int __get_total_mem_used__(void);
any allocate(int sz, int len);
int __get_size__(any ptr);
int __is_heap_init__();
void pfree(any ptr);
__meta__ *__get_meta__(any ptr);
