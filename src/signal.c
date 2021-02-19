#include "../include/signal.h"
#include "../include/memory.h"
#include "../include/syscall.h"
#include <asm-generic/errno-base.h>

static int errno = 0;
#define SET_ERRNO(v)                                                           \
  do {                                                                         \
    errno = (v);                                                               \
  } while (0)

int __kernel_sigaction(int sig, const sigaction_t* act, sigaction_t* oact) {
  int result;

  sigaction_t kact = {0}, koact = {0};

  if (act) {
    kact.sa_handler = act->sa_handler;
    memcpy(&kact.sa_mask, &act->sa_mask, sizeof(sigset_t));
    kact.sa_flags = act->sa_flags;
    SET_SA_RESTORER(&kact, act);
  }

  /* XXX The size argument hopefully will have to be changed to the
     real size of the user-level sigset_t.  */
  result = (int)SYSCALL4(__NR_rt_sigaction, sig, act ? &kact : NULL,
                         oact ? &koact : NULL, STUB(act, NSIG_BYTES));

  if (oact && result >= 0) {
    oact->sa_handler = koact.sa_handler;
    memcpy(&oact->sa_mask, &koact.sa_mask, sizeof(sigset_t));
    oact->sa_flags = koact.sa_flags;
    RESET_SA_RESTORER(oact, &koact);
  }
  return result;
}

int sigaction(int sig, sigaction_t* act, sigaction_t* oact) {
  if (sig <= 0 || sig >= NSIG) {
    SET_ERRNO(EINVAL);
    return -1;
  }

  return __kernel_sigaction(sig, act, oact);
}

sighandler_t signal(int sig, sighandler_t handler) {
  sigaction_t act, oact;

  if (handler == SIG_ERR || sig < 1 || sig >= NSIG) {
    SET_ERRNO(EINVAL);
    return SIG_ERR;
  }

  act.sa_handler = handler;
  memset(&act.sa_mask, 0, sizeof(act.sa_mask));
  act.sa_flags = SA_ONESHOT | SA_NOMASK | SA_INTERRUPT;
  act.sa_flags &= ~SA_RESTART;
  if (sigaction(sig, &act, &oact) < 0) {
    return SIG_ERR;
  }

  return oact.sa_handler;
}
