/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:23:02 by tkuramot          #+#    #+#             */
/*   Updated: 2023/07/02 14:07:03 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/include/ft_printf.h"
#include "minitalk.h"
#include <signal.h>
#include <sys/signal.h>
#include <unistd.h>

void	handler(int sig, siginfo_t *client, void *con)
{
	static unsigned char	mask = 0b10000000;
	static unsigned char	c;

	(void)con;
	if (sig == SIGUSR1 || sig == SIGUSR2)
	{
		if (sig == SIGUSR1)
			c |= mask;
		mask >>= 1;
		if (mask <= 0 && c)
		{
			ft_putchar_fd(c, STDOUT_FILENO);
			mask = 0b10000000;
			c = 0;
		}
		kill(client->si_pid, SIGUSR1);
	}
}

int	main(void)
{
	struct sigaction	act;

	ft_printf("PID: %d\n", getpid());
	ft_bzero(&act, sizeof(struct sigaction));
	act.sa_sigaction = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		;
	return (0);
}
