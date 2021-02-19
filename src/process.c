#include "../include/process.h"

static int errno = 0;
#define SET_ERRNO(v)                                                           \
  do {                                                                         \
    errno = (v);                                                               \
  } while (0)

static pid_t __sys_getpid(void) {
  return (pid_t)SYSCALL0(__NR_getpid);
}

static int __sys_kill(pid_t pid, int signal) {
  return (int)SYSCALL2(__NR_kill, pid, signal);
}

static int __sys_select(int nfds, fd_set* rfds, fd_set* wfds, fd_set* efds,
                        timeval* timeout) {
  return (int)SYSCALL5(__NR_select, nfds, rfds, wfds, efds, timeout);
}

pid_t getpid(void) {
  pid_t ret = __sys_getpid();

  if (ret < 0) {
    SET_ERRNO(-ret);
    ret = -1;
  }
  return ret;
}

int kill(pid_t pid, int signal) {
  int ret = __sys_kill(pid, signal);

  if (ret < 0) {
    SET_ERRNO(-ret);
    ret = -1;
  }
  return ret;
}

int raise(int signal) {
  return kill(getpid(), signal);
}

long sleep(unsigned int seconds, unsigned int useconds) {
  timeval timeout = {seconds, useconds};

  if (__sys_select(0, 0, 0, 0, &timeout) < 0)
    return timeout.tv_sec + timeout.tv_usec;
  else
    return 0;
}
