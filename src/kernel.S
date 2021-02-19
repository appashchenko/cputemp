.section .text
    .global _start, rdiv

    _start:
        pop %rdi
        mov %rsp,%rsi
        lea 8(%rsi,%rdi,8),%rdx
        and $-16,%rsp
        sub $8, %rsp

        call main

        movzb %al, %rdi
        mov $60,%rax
        syscall
        hlt
