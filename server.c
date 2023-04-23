/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 05:21:19 by aet-tass          #+#    #+#             */
/*   Updated: 2023/04/23 18:24:09 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	conv_to_char(int *bits, int size)
{
	char	c;
	int		i;
	int		exponent;
	int		base;
	int		result;

	c = 0;
	i = 0;
	while (i < size)
	{
		if (bits[i] == 1)
		{
			exponent = size - i - 1;
			base = 2;
			result = 1;
			while (exponent > 0)
			{
				result *= base;
				exponent--;
			}
			c += result;
		}
		i++;
	}
	return (c);
}

void	update_buffer(int signal, int *bit_buffer, int *buffer_index)
{
	if (signal == SIGUSR1)
	{
		bit_buffer[*buffer_index] = 0;
	}
	else
	{
		bit_buffer[*buffer_index] = 1;
	}
	(*buffer_index)++;
}

void	handle_signal(int signal, siginfo_t *info, void *context)
{
	static int	bit_buffer[8];
	static int	buffer_index;
	static int	client_pid;
	char		character;

	(void)context;
	buffer_index = 0;
	client_pid = 0;
	if (client_pid != info->si_pid)
	{
		client_pid = info->si_pid;
		buffer_index = 0;
	}
	update_buffer(signal, bit_buffer, &buffer_index);
	if (buffer_index == 8)
	{
		character = conv_to_char(bit_buffer, buffer_index);
		write(1, &character, 1);
		buffer_index = 0;
	}
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	signal_action;

	(void)argv;
	if (argc != 1)
	{
		printf("Error: Incorrect number of arguments\n");
		return (1);
	}
	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	signal_action.sa_sigaction = &handle_signal;
	signal_action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &signal_action, NULL);
	sigaction(SIGUSR2, &signal_action, NULL);
	while (1)
	{
		pause();
	}
}
