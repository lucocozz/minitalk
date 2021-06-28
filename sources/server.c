/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 03:24:44 by lucocozz          #+#    #+#             */
/*   Updated: 2021/06/28 23:45:32 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	set_signal(struct sigaction *act, int sig,
	void (*handler)(int, siginfo_t *, void *))
{
	act->sa_flags = SA_SIGINFO;
	act->sa_sigaction = handler;
	sigaction(sig, act, NULL);
}

static void	receive_byte(int signal, siginfo_t *info, void *data)
{
	static int	i = 0;
	static char	byte = 0;

	(void)data;
	if (signal == SIGUSR1)
		byte |= (1 << i);
	i++;
	if (i == 8)
	{
		if (byte == '\0')
		{
			write(1, "\n", 1);
			if (kill(info->si_pid, SIGUSR1) == -1)
				exit_error("Error: can't send response to client\n");
		}
		else
			write(1, &byte, 1);
		i = 0;
		byte = 0;
	}
	if (kill(info->si_pid, SIGUSR2) == -1)
		exit_error("Error: can't send response to client\n");
}

int	main(void)
{
	struct sigaction	sigusr1;
	struct sigaction	sigusr2;

	ft_putnbr(getpid());
	set_signal(&sigusr1, SIGUSR1, &receive_byte);
	set_signal(&sigusr2, SIGUSR2, &receive_byte);
	while (1)
		pause();
	return (0);
}
