#include "../include/io.h"
#include "../include/system.h"

static int errno = 0;
#define SET_ERRNO(v)                                                           \
  do {                                                                         \
    errno = (v);                                                               \
  } while (0)

static ssize_t __sys_read(int fd, void* buf, size_t count) {
  return SYSCALL3(__NR_read, fd, buf, count);
}

ssize_t __sys_write(int32_t fd, const void* buf, size_t count) {
  return SYSCALL3(__NR_write, fd, buf, count);
}

static int32_t __sys_open(const char* path, int32_t flags, mode_t mode) {
  return (int)SYSCALL4(__NR_openat, AT_FDCWD, path, flags, mode);
}

static int32_t __sys_close(int32_t fd) {
  return (int32_t)SYSCALL1(__NR_close, fd);
}

off_t __sys_lseek(int fd, off_t offset, int whence) {
  return (int)SYSCALL3(__NR_lseek, fd, offset, whence);
}

int open(const char* path, int flags, mode_t mode) {
  int ret = __sys_open(path, flags, mode);

  if (ret < 0) {
    SET_ERRNO(-ret);
    ret = -1;
  }
  return ret;
}

int close(int fd) {
  int ret = __sys_close(fd);

  if (ret < 0) {
    SET_ERRNO(-ret);
    ret = -1;
  }
  return ret;
}

ssize_t read(int32_t fd, void* buf, size_t count) {
  ssize_t ret = __sys_read(fd, buf, count);

  if (ret < 0) {
    SET_ERRNO((int32_t)-ret);
    ret = -1;
  }
  return ret;
}

ssize_t write(int fd, const void* buf, size_t count) {
  ssize_t ret = __sys_write(fd, buf, count);

  if (ret < 0) {
    SET_ERRNO((int)-ret);
    ret = -1;
  }
  return ret;
}

off_t lseek(int fd, off_t offset, int whence) {
  off_t ret = __sys_lseek(fd, offset, whence);

  if (ret < 0) {
    SET_ERRNO((int)-ret);
    ret = -1;
  }
  return ret;
}
