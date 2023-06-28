#include "minitalk.h"

volatile sig_atomic_t bit;

void handler(int sig, siginfo_t *info, void *con)
{
    static int bit = -1;
    static unsigned char c;

    (void)info;
    (void)con;
    if (bit < 0)
        bit = 7;
    if (sig == SIGUSR1)
        c |= (1 << bit);
    bit--;
    if (bit < 0 && c)
    {
        ft_putchar_fd(c, STDOUT_FILENO);
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