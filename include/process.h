#ifndef PROCESS_H
#define PROCESS_H

#include "system.h"

//typedef struct {
//    unsigned long fds_bits[4];
//} fd_set;

typedef struct {
  uint32_t fd32[32];
} fd_set;

typedef signed int pid_t;

typedef struct {
  long tv_sec;
  long tv_usec;
} timeval;

pid_t getpid(void);
long sleep(unsigned int seconds, unsigned int useconds);
int kill(pid_t pid, int signal);
int raise(int signal);

#endif
