/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:40:59 by abnemili          #+#    #+#             */
/*   Updated: 2025/03/27 21:21:44 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_msg(int signal)
{
	static unsigned char	c;
	static int				i;

	if (signal == SIGUSR1)
		c = c | (1 << i);
	else if (signal == SIGUSR2)
		c = c | (0 << i);
	i++;
	if (i == 8)
	{
		if (c == '\0')
		{
			write(1, "\n", 1);
			c = 0;
			i = 0;
		}
		else
		{
			write(1, &c, 1);
			c = 0;
			i = 0;
		}
	}
}

int	main(void)
{
	int	pid;

	pid = getpid();
	write(1, "\033[1;32m", 8);
	ft_print_id(pid);
	write(1, "\n", 1);
	write(1, "\033[1;33mwaiting for the message....\n\033[0m", 40);
	signal(SIGUSR1, handle_msg);
	signal(SIGUSR2, handle_msg);
	while (1)
		;
	return (0);
}
