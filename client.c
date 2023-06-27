#include "minitalk.h"

// SIGUSR1 is 0 and SIGUSR2 is 1
static void    send_char(pid_t pid, unsigned char  c)
{
    int             bit;
    int             i;

    i = 0;
    while (i < 8)
    {
        usleep(1000);
        bit = (c >> i) & 0b00000001;
        if (kill(pid, SIGUSR1 + bit) == -1)
            return;
        i++;
    }
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        ft_printf("Usage: ./client {pid} {string}\n");
        return (0);
    }
    while (*argv[2]++)
    {
        send_char((pid_t)ft_atoi(argv[1]), *argv[2]);
    }
    return 0;
}