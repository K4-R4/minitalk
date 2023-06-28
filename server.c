#include "minitalk.h"

volatile sig_atomic_t bit;

void handler(int sig, siginfo_t *info, void *con)
{
    static unsigned char mask = 0b10000000;
    static unsigned char c;

    (void)info;
    (void)con;
    if (sig == SIGUSR1)
        c |= mask;
    mask >>= 1;
    if (mask <= 0)
    {
        ft_putchar_fd(c, STDOUT_FILENO);
        mask = 0b10000000;
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