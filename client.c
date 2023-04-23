/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:49:29 by aet-tass          #+#    #+#             */
/*   Updated: 2023/04/23 18:56:31 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	encode_bit(char c, int i)
{
	return ((c >> i) & 1);
}

void	send_bit(int pid, int bit)
{
	if (bit == 0)
	{
		if (kill(pid, SIGUSR1) == -1)
		{
			printf("Invalid Pid\n");
			exit(1);
		}
	}
	else
	{
		if (kill(pid, SIGUSR2) == -1)
		{
			printf("Invalid Pid\n");
			exit(1);
		}
	}
	usleep(200);
}

void	send_encoded_message(int pid, char *message)
{
	int	bit;
	int	i;

	while (*message != '\0')
	{
		i = 7;
		while (i >= 0)
		{
			bit = encode_bit(*message, i);
			send_bit(pid, bit);
			i--;
		}
		usleep(100);
		message++;
	}
}

int	main(int argc, char *argv[])
{
	int	pid;

	if (argc != 3)
	{
		ft_printf("Usage: %s pid message\n", argv[0]);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		exit(1);
	else
		send_encoded_message(pid, argv[2]);
	return (0);
}
