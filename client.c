#include "minitalk.h"

void    receiver(void handler(int, siginfo_t *, void *))
{
    struct sigaction    act;

    bzero(&act, sizeof(struct sigaction));
    act.sa_sigaction = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGUSR2, &act, NULL);
}

int main(int argc, char **argv)
{
    (void)argc;
    kill((pid_t)atoi(argv[1]), SIGSEGV);
    return 0;
}