/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:00:02 by abnemili          #+#    #+#             */
/*   Updated: 2025/03/27 21:21:49 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
