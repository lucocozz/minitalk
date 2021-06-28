/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 03:24:44 by lucocozz          #+#    #+#             */
/*   Updated: 2021/06/28 17:46:29 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	set_signal(struct sigaction *siga, int sign,
	void (*handler)(int, siginfo_t *, void *))
{
	siga->sa_flags = SA_SIGINFO | SA_NODEFER;
	siga->sa_sigaction = handler;
	sigaction(sign, siga, NULL);
}

static char	get_byte(int signal)
{
	static int	i = 0;
	static char	byte = 0;

	if (i == 8)
	{
		i = 0;
		byte = 0;
	}
	if (signal == SIGUSR1)
		byte |= (1 << i);
	else if (signal == SIGUSR2)
		byte |= (0 << i);
	i++;
	if (i == 8)
		return (byte);
	else
		return (NO_BYTE);
}

static void	receive_data(int signal, siginfo_t *info, void *data)
{
	char		byte;

	(void)data;
	byte = get_byte(signal);
	if (byte != NO_BYTE)
	{
		write(1, &byte, 1);
		if (byte == 0)
		{
			if (kill(info->si_pid, SIGUSR1) == -1)
				exit_error("Error: can't send response to client\n");
			write(1, "\n", 1);
		}
	}
	if (kill(info->si_pid, SIGUSR2) == -1)
		exit_error("Error: can't send response to client\n");
}

int	main(void)
{
	struct sigaction	sigusr1;
	struct sigaction	sigusr2;

	ft_putnbr(getpid());
	set_signal(&sigusr1, SIGUSR1, &receive_data);
	set_signal(&sigusr2, SIGUSR2, &receive_data);
	while (1)
		pause();
	return (0);
}
