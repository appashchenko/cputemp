#ifndef SYSCALL_H
#define SYSCALL_H

#include <asm/unistd_64.h>

#define SYSCALL0(num)                                                          \
  ({                                                                           \
    long _ret;                                                                 \
    register long _num __asm__("rax") = (num);                                 \
                                                                               \
    __asm__ volatile("syscall\n"                                               \
                     : "=a"(_ret)                                              \
                     : "0"(_num)                                               \
                     : "rcx", "r8", "r9", "r10", "r11", "memory", "cc");       \
    _ret;                                                                      \
  })

#define SYSCALL1(num, arg1)                                                    \
  __extension__({                                                              \
    long _ret;                                                                 \
    register long _num __asm__("rax") = (num);                                 \
    register long _arg1 __asm__("rdi") = (long)(arg1);                         \
                                                                               \
    __asm__ volatile("syscall\n"                                               \
                     : "=a"(_ret)                                              \
                     : "r"(_arg1), "0"(_num)                                   \
                     : "rcx", "r8", "r9", "r10", "r11", "memory", "cc");       \
    _ret;                                                                      \
  })

#define SYSCALL2(num, arg1, arg2)                                              \
  ({                                                                           \
    long _ret;                                                                 \
    register long _num __asm__("rax") = (num);                                 \
    register long _arg1 __asm__("rdi") = (long)(arg1);                         \
    register long _arg2 __asm__("rsi") = (long)(arg2);                         \
                                                                               \
    __asm__ volatile("syscall\n"                                                   \
                 : "=a"(_ret)                                                  \
                 : "r"(_arg1), "r"(_arg2), "0"(_num)                           \
                 : "rcx", "r8", "r9", "r10", "r11", "memory", "cc");           \
    _ret;                                                                      \
  })

#define SYSCALL3(num, arg1, arg2, arg3)                                        \
  __extension__({                                                              \
    long _ret;                                                                 \
    register long _num __asm__("rax") = (num);                                 \
    register long _arg1 __asm__("rdi") = (long)(arg1);                         \
    register long _arg2 __asm__("rsi") = (long)(arg2);                         \
    register long _arg3 __asm__("rdx") = (long)(arg3);                         \
                                                                               \
    __asm__ volatile("syscall\n"                                               \
                     : "=a"(_ret)                                              \
                     : "r"(_arg1), "r"(_arg2), "r"(_arg3), "0"(_num)           \
                     : "rcx", "r8", "r9", "r10", "r11", "memory", "cc");       \
    _ret;                                                                      \
  })

#define SYSCALL4(num, arg1, arg2, arg3, arg4)                                  \
  __extension__({                                                              \
    long _ret;                                                                 \
    register long _num __asm__("rax") = (num);                                 \
    register long _arg1 __asm__("rdi") = (long)(arg1);                         \
    register long _arg2 __asm__("rsi") = (long)(arg2);                         \
    register long _arg3 __asm__("rdx") = (long)(arg3);                         \
    register long _arg4 __asm__("r10") = (long)(arg4);                         \
                                                                               \
    __asm__ volatile("syscall\n"                                               \
                     : "=a"(_ret), "=r"(_arg4)                                 \
                     : "r"(_arg1), "r"(_arg2), "r"(_arg3), "r"(_arg4),         \
                       "0"(_num)                                               \
                     : "rcx", "r8", "r9", "r11", "memory", "cc");              \
    _ret;                                                                      \
  })

#define SYSCALL5(num, arg1, arg2, arg3, arg4, arg5)                            \
  ({                                                                           \
    long _ret;                                                                 \
    register long _num __asm__("rax") = (num);                                 \
    register long _arg1 __asm__("rdi") = (long)(arg1);                         \
    register long _arg2 __asm__("rsi") = (long)(arg2);                         \
    register long _arg3 __asm__("rdx") = (long)(arg3);                         \
    register long _arg4 __asm__("r10") = (long)(arg4);                         \
    register long _arg5 __asm__("r8") = (long)(arg5);                          \
                                                                               \
    __asm__ volatile("syscall\n"                                               \
                     : "=a"(_ret), "=r"(_arg4), "=r"(_arg5)                    \
                     : "r"(_arg1), "r"(_arg2), "r"(_arg3), "r"(_arg4),         \
                       "r"(_arg5), "0"(_num)                                   \
                     : "rcx", "r9", "r11", "memory", "cc");                    \
    _ret;                                                                      \
  })

#endif
