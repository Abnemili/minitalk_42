/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_i_d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloudifa <mloudifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:36:47 by mloudifa          #+#    #+#             */
/*   Updated: 2024/06/29 15:39:40 by mloudifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

int	ft_print_c(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_print_i_d(int nb)
{
	int	i;

	i = 0;
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (nb < 0)
	{
		i += ft_print_c('-');
		nb = -nb;
	}
	if (nb > 9)
	{
		i += ft_print_i_d(nb / 10);
		i += ft_print_i_d(nb % 10);
	}
	else
	{
		i += ft_print_c(48 + nb);
	}
	return (i);
}
