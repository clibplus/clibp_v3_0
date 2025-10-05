global _sys_read
global _sys_write
global _sys_open
global _sys_close
global _mmap
global _munmap
global _syscall
global _sys_nanosleep

section .text

_syscall:
	mov eax, ebx
	mov ebx, ecx
	mov ecx, edx
	mov edx, esi
	int 80h
	ret

_sys_read:
	mov eax, 3
	int 80h
	ret

_sys_write:
	mov eax, 4
	int 80h
	ret

_sys_open:
	mov eax, 5
	int 80h
	ret

_sys_close:
	mov eax, 6
	int 80h
	ret

_mmap:
	mov eax, 90
	int 80h
	ret

_munmap:
	mov eax, 91
	int 80h
	ret

_sys_nanosleep:
	mov eax, 162
	int 80h
	ret
