/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 17:50:56 by lucocozz          #+#    #+#             */
/*   Updated: 2021/06/26 15:29:14 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_print_nb(int nb)
{
	char	value;

	if (nb > 0)
	{
		ft_print_nb(nb / 10);
		value = nb % 10 + '0';
		write(1, &value, 1);
	}
}

void	ft_putnbr(int nb)
{
	if (nb == 0)
		write(1, "0", 1);
	if (nb < 0)
	{
		write(1, "-", 1);
		nb *= -1;
	}
	if (nb == -2147483648)
	{
		write(1, "2", 1);
		nb = 147483648;
	}
	ft_print_nb(nb);
	write(1, "\n", 1);
}
