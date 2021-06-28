/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 03:14:42 by lucocozz          #+#    #+#             */
/*   Updated: 2021/06/28 18:45:44 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define _DEFAULT_SOURCE
# define _XOPEN_SOURCE 700

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>

typedef struct s_sending
{
	pid_t		pid;
	char		*data;
}				t_sending;

int		ft_putstr(char const *s);
int		ft_strlen(const char *s);
void	ft_putnbr(int nb);
int		ft_isnumber(char const *s);
void	exit_error(char const *str);
int		ft_atoi(const char *str);

#endif
