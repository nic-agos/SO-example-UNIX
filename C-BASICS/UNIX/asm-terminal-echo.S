
//neverending echo from the standard input to the standard output
//please compile with "gcc -c" and "ld" or with "-nostartfiles"

.file "asm-terminal-echo.S"
.text
.globl _start 
.type _start, @function

_start:
	sub $0x4, %rsp 		# reserve 4 bytes for hosting chars to read/write, %rsp is the stack pointer
	.loop:
	mov $0x0, %rax 		# from this line we pack registers for calling the read sycall (0 is read)
	mov $0x0, %rdi		# write 0 in %rdi, %rdi is the 1° paramether of syscall (source)
	mov %rsp, %rsi      # write &rsp in %rsi, %rsi is the 2° paramether of syscall (memory)
	mov $0x1, %rdx      # write 1 in %rdx, %rdx is the 3° paramether of syscall (# byte)
	syscall				# pass the control to SO (read)
	mov $0x1, %rax 		# %rax contains the code of the operation for the sycall (1 is write)
	mov $0x1, %rdi
	syscall				# pass the control to SO (write)
	jmp .loop

