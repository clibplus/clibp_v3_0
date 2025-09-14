global _sys_read
global _sys_write
global _sys_open
global _sys_close
global _mmap
global _munmap
global _syscall

section .text

_syscall:
	mov rax, rdi
	mov rdi, rsi
	mov rsi, rdx
	mov rdx, rcx
	syscall
	ret

_sys_read:
	mov rax, 0
	syscall
	ret

_sys_write:
	mov rax, 1
	syscall
	ret

_sys_open:
	mov rax, 2
	syscall
	ret

_sys_close:
	mov rax, 3
	syscall
	ret

_mmap:
	mov rax, 9
	mov r10, rcx
	syscall
	ret

_munmap:
	mov rax, 11
	syscall
	ret
