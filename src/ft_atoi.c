/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloudifa <mloudifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:28:06 by mloudifa          #+#    #+#             */
/*   Updated: 2024/06/21 14:46:03 by mloudifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

static long long	spaces_len(const char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i] == '\t' || nptr[i] == '\r' || nptr[i] == ' '
		|| nptr[i] == '\n' || nptr[i] == '\v' || nptr[i] == '\f')
		i++;
	return (i);
}

static long long	sign_checker(const char *nptr)
{
	int	i;

	i = spaces_len(nptr);
	if (nptr[i] == '-')
		return (-1);
	return (1);
}

long long	ft_atoi(char *nptr)
{
	int		i;
	int		sign;
	long	num;

	i = spaces_len(nptr);
	sign = sign_checker(nptr);
	num = 0;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * num);
}
