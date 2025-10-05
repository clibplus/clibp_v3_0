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

/* Some Built-in Types */
#define NULL 			0
#define bool 			int
#define true 			1
#define false 			0

typedef char 			i8;
typedef short 			i16;
typedef int 			i32;

typedef unsigned char 	u8;
typedef unsigned short 	u16;
typedef unsigned int	u32;

typedef void 			none;
typedef void 			*any;
typedef char 			*str;
typedef void 			*fn_t;

typedef unsigned long 	size_t;
typedef unsigned long 	len_t;
typedef unsigned long 	pos_t;

/* Heap Declaration */
typedef void 			*heap_t;
extern heap_t 			_HEAP_;

/* Global Function Declaraction */
void __syscall(long syscall, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6);

// Get Start-up App Cmdline Arguments
int 	get_args(char *argv[]);

none 	__exit(int code);
none 	printc(const char ch);
none 	printi(int num);
none 	_printi(int value);
none 	print(const str buff);
none 	printsz(const str buff, int sz);
none 	printa(const str *buff);
none 	err_n_exit(const str buff, int code);

/* General memory functions */
none 	memzero(any ptr, size_t);
int 	mem_cmp(any src, any ptr, size_t size);
none 	mem_cpy(any dest, any src, size_t size);
none 	mem_set(any ptr, char ch, size_t size);

int 	get_input(str dest, len_t count);

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
	typedef any *arr;
	int 	arr_contains(arr args, str needle);
#endif

#if defined(FILE_H)
	typedef unsigned int fd_t;

	typedef enum FILE_MODE {
		O_RDONLY		= 0,		// Read
		O_WRONLY	    = 01,		// Write
		O_RDWR		    = 02,		// Read-Write
		O_CREAT		   	= 0100,		// Create
		O_EXCL		   	= 0200,
		O_NOCTTY	   	= 0400,
		O_TRUNC		  	= 01000		// Truncate
	} FILE_MODE;

	/*
		[@DOC]
			fd_t open_file(const char *filename, FILE_MODE mode);

			Desc;
				open a file stream

			return;
				>0 on sucess
				-1 on fail
	*/
	fd_t	open_file(const char *filename, FILE_MODE mode);

	/*
		[@DOC]
			int file_content_size(fd_t fd);

			Desc;
				get file size

			return;
				>0 on success
				-1 on fail
	*/
	int		file_content_size(fd_t fd);

	/*
		[@DOC]
			int file_read(fd_t fd, char *buffer, int sz);

			Desc;
				get file content

			return;
				>0 on scuess
				<=0 on fail
	*/
	int		file_read(fd_t fd, char *buffer, int sz);

	/* file_read for unsigned char */
	#define file_uc_read(fd, buff, sz) file_read

	/*
		[@DOC]
			int file_write(fd_t fd, const char *buffer, len_t len);

			Desc;
				write to file

			return;
				>0 on success
				-1 on fail
	*/
	int		file_write(fd_t fd, const char *buffer, len_t len);

	/*
		[@DOC]
			int file_close(fd_t fd, const char *buffer, len_t len);

			Desc;
				close file
	*/
	void	file_close(fd_t fd);
#endif
