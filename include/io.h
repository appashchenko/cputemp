#ifndef IO_H
#define IO_H

#include "syscall.h"
#include "types.h"

#define O_RDONLY 0
#define O_WRONLY 1
#define O_RDWR 2
#define O_CREAT 0x40
#define O_EXCL 0x80
#define O_NOCTTY 0x100
#define O_TRUNC 0x200
#define O_APPEND 0x400
#define O_NONBLOCK 0x800
#define O_DIRECTORY 0x10000
#define O_NOATIME 0x1000000

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2


#ifndef AT_FDWCD
#define AT_FDCWD -100
#endif

#define DT_UNKNOWN 0
#define DT_FIFO 1
#define DT_CHR 2
#define DT_DIR 4
#define DT_BLK 6
#define DT_REG 8
#define DT_LNK 10
#define DT_SOCK 12


typedef unsigned int mode_t;

int open(const char* path, int flags, mode_t mode);
int close(int fd);
ssize_t read(int32_t fd, void* buf, size_t count);
ssize_t write(int fd, const void* buf, size_t count);
off_t lseek(int fd, off_t offset, int whence);

#endif
