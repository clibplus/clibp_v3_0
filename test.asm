section .const
    test "TEST"

section .var
    buffer 100, 0

label: 
	mov rax, 1
	mov rdi, 1
	lea rsi, [rel welcome]
	mov rdx, 17
	syscall