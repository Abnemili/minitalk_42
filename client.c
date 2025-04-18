/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:40:30 by abnemili          #+#    #+#             */
/*   Updated: 2025/03/27 20:50:58 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_msg(int pid, char byte)
{
	int	x;

	x = 8;
	while (x > 0)
	{
		if (byte & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		byte >>= 1;
		usleep(230);
		x--;
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	if (argc != 3 || is_valide(argv[1]) == 0 || argv[1][0] == '0')
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
