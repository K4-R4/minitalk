#include "minitalk.h"

volatile sig_atomic_t bit;

void handler(int sig, siginfo_t *info, void *ucon)
{
    (void)info;
    (void)ucon;
    // static volatile sig_atomic_t c;
    static char c;
    if (sig == SIGUSR2)
        c = (c << 1) | 1;
    else
        c = (c << 1);
    bit++;
    if (bit == 8)
    {
        write(STDOUT_FILENO, (const void *)(&c), 1);
        bit = 0;
        c = 0;
    }
}

int main()
{
    struct sigaction    act;

    ft_bzero(&act, sizeof(struct sigaction));
    act.sa_sigaction = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGUSR2, &act, NULL);
	while(1)
		;
    return 0;
}