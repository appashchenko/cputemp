#ifndef SIGNAL_H
#define SIGNAL_H

#include "asm-generic/signal-defs.h"

#define SIGHUP 1
#define SIGINT 2
#define SIGQUIT 3
#define SIGILL 4
#define SIGTRAP 5
#define SIGABRT 6
#define SIGIOT 6
#define SIGBUS 7
#define SIGFPE 8
#define SIGKILL 9
#define SIGUSR1 10
#define SIGSEGV 11
#define SIGUSR2 12
#define SIGPIPE 13
#define SIGALRM 14
#define SIGTERM 15
#define SIGSTKFLT 16
#define SIGCHLD 17
#define SIGCONT 18
#define SIGSTOP 19
#define SIGTSTP 20
#define SIGTTIN 21
#define SIGTTOU 22
#define SIGURG 23
#define SIGXCPU 24
#define SIGXFSZ 25
#define SIGVTALRM 26
#define SIGPROF 27
#define SIGWINCH 28
#define SIGIO 29
#define SIGPOLL SIGIO
/* #define SIGLOST		29 */
#define SIGPWR 30
#define SIGSYS 31
#define SIGUNUSED 31

#define ENOSYS 38
#define NSIG 64
#define NSIG_BPW 64
#define NSIG_WORDS (NSIG / NSIG_BPW)
#define NSIG_BYTES (NSIG_WORDS * 8)

#define SIGINT 2
#define SIGTERM 15

#ifndef SA_ONESHOT
#define SA_ONESHOT 0
#endif
#ifndef SA_NOMASK
#define SA_NOMASK 0
#endif
#ifndef SA_INTERRUPT
#define SA_INTERRUPT 0
#endif

#define ENOSYS 38
#define NSIG 64
#define NSIG_BPW 64
#define NSIG_WORDS (NSIG / NSIG_BPW)
#define NSIG_BYTES (NSIG_WORDS * 8)

#define SIGINT 2
#define SIGTERM 15

#ifndef SA_ONESHOT
#define SA_ONESHOT 0
#endif
#ifndef SA_NOMASK
#define SA_NOMASK 0
#endif
#ifndef SA_INTERRUPT
#define SA_INTERRUPT 0
#endif
#ifndef SA_RESTART
#define SA_RESTART 0x00000002
#endif

#ifndef STUB
#define STUB(act, sigsetsize) (sigsetsize)
#endif

#ifndef SA_RESTORER
#define SET_SA_RESTORER(kact, act)
#define RESET_SA_RESTORER(act, kact)
#endif

typedef void __signalfn_t(int);
typedef __signalfn_t *sighandler_t;
typedef void __restorefn_t(void);
typedef __restorefn_t *sigrestore_t;

typedef union sigval {
  int sival_int;
  void* sival_ptr;
} sigval_t;

typedef struct {
  unsigned long sig[NSIG_WORDS];
} sigset_t;

typedef struct siginfo {
  union {
    struct {
      int si_signo;
      int si_code;
      int si_errno;
      union __sifields {
        /* kill() */
        struct {
          int _pid;          /* sender's pid */
          unsigned int _uid; /* sender's uid */
        } _kill;

        /* POSIX.1b timers */
        struct {
          int _tid;         /* timer id */
          int _overrun;     /* overrun count */
          sigval_t _sigval; /* same as below */
          int _sys_private; /* not to be passed to user */
        } _timer;

        /* POSIX.1b signals */
        struct {
          int _pid;          /* sender's pid */
          unsigned int _uid; /* sender's uid */
          sigval_t _sigval;
        } _rt;

        /* SIGCHLD */
        struct {
          int _pid;          /* which child */
          unsigned int _uid; /* sender's uid */
          int _status;       /* exit code */
          long long _utime;
          long long _stime;
        } _sigchld;

        /* SIGILL, SIGFPE, SIGSEGV, SIGBUS, SIGTRAP, SIGEMT */
        struct {
          void* _addr; /* faulting insn/memory ref. */

#define __ADDR_BND_PKEY_PAD                                                    \
  (__alignof__(void*) < sizeof(short) ? sizeof(short) : __alignof__(void*))
          union {
            /*
             * used when si_code=BUS_MCEERR_AR or
             * used when si_code=BUS_MCEERR_AO
             */
            short _addr_lsb; /* LSB of the reported address */
            /* used when si_code=SEGV_BNDERR */
            struct {
              char _dummy_bnd[__ADDR_BND_PKEY_PAD];
              void* _lower;
              void* _upper;
            } _addr_bnd;
            /* used when si_code=SEGV_PKUERR */
            struct {
              char _dummy_pkey[__ADDR_BND_PKEY_PAD];
              unsigned int _pkey;
            } _addr_pkey;
          };
        } _sigfault;

        /* SIGPOLL */
        struct {
          long _band; /* POLL_IN, POLL_OUT, POLL_MSG */
          int _fd;
        } _sigpoll;

        /* SIGSYS */
        struct {
          void* _call_addr;   /* calling user insn */
          int _syscall;       /* triggering system call number */
          unsigned int _arch; /* AUDIT_ARCH_* of syscall */
        } _sigsys;
      } _sifields;
    };
    int _si_pad[32];
  };
} siginfo_t;

typedef struct {
  sighandler_t sa_handler;
  void (*sa_sigaction)(int, struct siginfo*, void*);
  sigset_t sa_mask;
  unsigned long sa_flags;
  void (*sa_restorer)(void);
} sigaction_t;


static inline void sigemptyset(sigset_t* set) {
  set->sig[0] = 0;
}

static inline void sigaddset(sigset_t* set, int _sig) {
  unsigned long sig = _sig - 1;
  set->sig[0] |= 1UL << sig;
}

int sigaction(int sig, sigaction_t* act, sigaction_t* oact);
#endif
