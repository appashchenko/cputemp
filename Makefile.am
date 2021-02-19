bin_PROGRAMS = cputemp
cputemp_CFLAGS = -std=c11 -Wall -Wextra -Werror \
-nostdlib -ffreestanding -I$(top_srcdir)/include\
-fno-asynchronous-unwind-tables -fno-ident -lgcc \
-Wno-gnu-statement-expression
cputemp_SOURCES = \
    src/io.c \
    src/kernel.S \
    src/main.c \
    src/memory.c \
    src/process.c \
    src/signal.c \
    src/string.c \
include_HEADERS = \
    include/io.h \
    include/kernel.h \
    include/memory.h \
    include/process.h \
    include/signal.h \
    include/system.h \
    include/syscall.h \
    include/types.h

