/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:37:34 by abnemili          #+#    #+#             */
/*   Updated: 2025/03/27 21:21:37 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_print_id(int nb)
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
		i += ft_putchar('-');
		nb = -nb;
	}
	if (nb > 9)
	{
		i += ft_print_id(nb / 10);
		i += ft_print_id(nb % 10);
	}
	else
	{
		i += ft_putchar(48 + nb);
	}
	return (i);
}

int	is_valide(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] >= '0' && av[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}
