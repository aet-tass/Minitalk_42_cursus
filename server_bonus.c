/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 17:22:55 by aet-tass          #+#    #+#             */
/*   Updated: 2023/04/23 18:24:27 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minitalk.h"

char conv_to_char(int *bits, int size)
{
    char c = 0;
    int i = 0;
    while (i < size)
    {
        if (bits[i] == 1)
        {
            int exponent = size - i - 1;
            int base = 2;
            int result = 1;
            while (exponent > 0)
            {
                result *= base;
                exponent--;
            }
            c += result;
        }
        i++;
    }
    return c;
}


void update_buffer(int signal, int* bit_buffer, int* buffer_index)
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

void handle_signal(int signal, siginfo_t *info, void *context)
{
	(void )context;
    static int bit_buffer[8];
    static int buffer_index = 0;
    static int client_pid = 0;
    char character;

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


int main(int argc, char **argv)
{
	(void)argv;
    int pid;
    struct sigaction signal_action;

    if (argc != 1)
    {
        ft_printf("Error: Incorrect number of arguments\n");
        return (1);
    }
    pid = getpid();
    printf("Server PID: %d\n", pid);
    signal_action.sa_sigaction = &handle_signal;
    signal_action.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &signal_action, NULL);
    sigaction(SIGUSR2, &signal_action, NULL);
    while (1)
    {
        pause();
    }
}
