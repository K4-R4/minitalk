#include "minitalk.h"

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
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        ft_printf("Usage: ./client {pid} {message}\n");
        return (0);
    }
    send_str((pid_t)ft_atoi(argv[1]), argv[2]);
    return 0;
}