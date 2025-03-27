/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloudifa <mloudifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:33:51 by mloudifa          #+#    #+#             */
/*   Updated: 2024/06/29 15:34:57 by mloudifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"
#include <unistd.h>

void	send_msg(int pid, char c)
{
	int	i;

	i = 8;
	while (i > 0)
	{
		if (c & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		c >>= 1;
		usleep(200);
		i--;
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	if (argc != 3 || parsing(argv[1]) == 0 || argv[1][0] == '0')
	{
		write(1, "\033[1;31m", 8);
		write(1, "Usage!: ./client [PID_SERVER] [STRING_TO_PASS]\n\033[0m", 52);
	}
	else
	{
		pid = ft_atoi(argv[1]);
		if (pid == -1)
			return (0);
		i = 0;
		while (argv[2][i])
		{
			send_msg(pid, argv[2][i]);
			i++;
		}
		send_msg(pid, '\0');
	}
	return (0);
}
