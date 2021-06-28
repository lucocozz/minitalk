/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 03:24:08 by lucocozz          #+#    #+#             */
/*   Updated: 2021/06/28 17:46:22 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_byte(pid_t pid, char byte)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((byte >> i) & 1)
		{
			if (kill(pid, SIGUSR1) == -1)
				exit_error("Error: sending byte.\n");
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				exit_error("Error: sending byte.\n");
		}
		i++;
		pause();
	}
}

static void	send_data(t_sending *server)
{
	int	i;

	i = 0;
	while (server->data[i])
		send_byte(server->pid, server->data[i++]);
	send_byte(server->pid, server->data[i]);
}

static void	get_data(t_sending *server, int argc, char **argv)
{
	if (argc != 3)
		exit_error("Usage: ./client [server_pid] [message]\n");
	if (ft_isnumber(argv[1]) == 0)
		exit_error("Error: invalide pid\n");
	server->pid = ft_atoi(argv[1]);
	server->data = argv[2];
}

static void	receive_signal(int signal)
{
	if (signal == SIGUSR1)
	{
		ft_putstr("Message received by server\n");
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char **argv)
{
	t_sending	server;

	signal(SIGUSR1, &receive_signal);
	signal(SIGUSR2, &receive_signal);
	get_data(&server, argc, argv);
	send_data(&server);
	pause();
	return (0);
}
