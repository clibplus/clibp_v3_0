/*
*
*	[ clib+ ]
*
*	- A minimal C backend without GLIBC ( -nostdlib )
*	with only a heap allocator
*/
#pragma once

#include "../x86_64.h"

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

#define ARCH_SYSCALL
#if defined(ARCH_SYSCALL) && defined(__x86__)
		#include "../x86.h"
#elif defined(ARCH_SYSCALL) && defined(__x86_64__)
		#include "../x86_64.h"
#endif

none __exit(int code);
none printc(const char ch);
none print(const str buff);
none err_n_exit(const str buff, int code);

/* Heap */
none memzero(any ptr, size_t);
none mem_cpy(any dest, any src, size_t size);
none mem_set(any ptr, char ch, size_t size);

/* Global Functions */
int get_input(str dest, len_t count);

#if defined(CLIBP)
	#define STR_H
#endif

#if defined(STR_H)
	len_t 	str_len(str buffer);
	bool 	str_cmp(const str src, const str needle);
	pos_t 	find_char(const str buff, const char ch, int match);
	pos_t 	find_str(const str buff, const str needle);
#endif

#if defined(ARR_H)
	typedef none *arr;
#endif

#if defined(FILE_H)
	typedef unsigned int fd_t;
#endif
