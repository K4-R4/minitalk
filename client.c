#include "minitalk.h"

static volatile sig_atomic_t received;

static void    send_char(pid_t pid, unsigned char  c)
{
    unsigned char   mask;

    mask = 0b10000000;
    while (mask)
    {
        usleep(50);
        if (mask & c)
        {
            if (kill(pid, SIGUSR1) < 0)
                return;
        }
        else
        {
            if (kill(pid, SIGUSR2) < 0)
                return;
        }
        mask >>= 1;
        while (!(received == BIT_RECEIVED || received == MESSAGE_RECEIVED))
            pause();
    }
}

static void send_str(pid_t pid, char *c)
{
    size_t  index;
    size_t  len;

    index = 0;
    len = ft_strlen(c);
    while (index++ < len)
        send_char(pid, c[index]);
    send_char(pid, 0);
}

static void handler(int signal, siginfo_t *server, void *con)
{
    (void)server;
    (void)con;
    if (signal == SIGUSR1)
        received = BIT_RECEIVED;
    else if (signal == SIGUSR2)
        received = MESSAGE_RECEIVED;
}

int main(int argc, char **argv)
{
    struct sigaction    act;

    if (argc != 3)
    {
        ft_printf("Usage: ./client {pid} {message}\n");
        return (0);
    }
    ft_bzero(&act, sizeof(struct sigaction));
    act.sa_sigaction = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGUSR2, &act, NULL);
    send_str((pid_t)ft_atoi(argv[1]), argv[2]);
    if (received == MESSAGE_RECEIVED)
        ft_printf("The server acknowledged your message.\n");
    return 0;
}