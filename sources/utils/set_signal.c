/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 15:56:29 by lucocozz          #+#    #+#             */
/*   Updated: 2021/07/04 22:49:44 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	set_signal(struct sigaction *act, int sig,
	void (*handler)(int, siginfo_t *, void *))
{
	act->sa_flags = SA_SIGINFO | SA_NODEFER;
	act->sa_sigaction = handler;
	sigaction(sig, act, NULL);
}
