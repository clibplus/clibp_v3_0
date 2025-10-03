/*
*
*	[ clib+ ]
*
*	- A minimal C backend without GLIBC ( -nostdlib )
*	with only a heap allocator
*/
#pragma once

/*
    Auto Architecture Detection

    Disable by using DISABLE_AUTO_ARCH_DET
    followed by a specific architecture for compilation
*/
#if !defined(DISABLE_AUTO_ARCH_DET)
    #if defined(__i386__)
            #define ___x86___ "x86"
            #include "asm.h"
    #endif
    #if defined(__x86_64__)
            #define ___x86_64___
            #include "asm.h"
    #endif
#endif

#include "allocator.h"

/* Any Type */
typedef void *any;

/* Some Built-in Types */
#define NULL 0
#define bool int
#define true 1
#define false 0

typedef void none;
typedef char *str;
typedef void *fn_t;
typedef unsigned long size_t;
typedef unsigned long len_t;
typedef unsigned long pos_t;

void __syscall(long syscall, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6);

int get_args(char *argv[]);

/* Unviersal Memory Function(s) */
#if defined(_STANDARD_MEM_SZ_)
        #define _HEAP_PAGE_SZ_ 4096
#elif defined(_LARGE_MEM_SZ_)
        #define _HEAP_PAGE_SZ_ 4096 * 2
#endif

typedef void *heap_t;
typedef void *any;
typedef char *str;

extern heap_t _HEAP_;

none __exit(int code);
none printc(const char ch);
none printi(int num);
none _printi(int value);
none print(const str buff);
none printsz(const str buff, int sz);
none printa(const str *buff);
none err_n_exit(const str buff, int code);

/* Heap */
none memzero(any ptr, size_t);
int mem_cmp(any src, any ptr, size_t size);
none mem_cpy(any dest, any src, size_t size);
none mem_set(any ptr, char ch, size_t size);

/* Global Functions */
int get_input(str dest, len_t count);

#define CLIBP
#if defined(CLIBP)
	#define STR_H
	#define ARR_H
	#define FILE_H
#endif

#if defined(STR_H)
	len_t 	str_len(str buffer);
	int   	stra(str src, const str sub);
	bool	str_cmp(const str src, const str needle);
	pos_t 	find_char(const str buff, const char ch, int match);
	pos_t 	find_str(const str buff, const str needle);
#endif

#if defined(ARR_H)
	typedef none *arr;
	int 	arr_contains(arr args, str needle);
#endif

#if defined(FILE_H)
	typedef unsigned int fd_t;

	typedef enum FILE_MODE {
		O_RDONLY		= 0,
		O_WRONLY	    = 01,
		O_RDWR		    = 02,
		O_CREAT		   	= 0100,
		O_EXCL		   	= 0200,
		O_NOCTTY	   	= 0400,
		O_TRUNC		  	= 01000
	} FILE_MODE;

	fd_t	open_file(const char *filename, FILE_MODE mode);
	int		file_content_length(fd_t fd);
	int		file_read(fd_t fd, char *buffer, int sz);
	int		file_write(fd_t fd, const char *buffer, len_t len);
	void	file_close(fd_t fd);
#endif
