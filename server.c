<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 00:29:39 by aet-tass          #+#    #+#             */
/*   Updated: 2023/04/12 00:30:06 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int power_of_two(int base, int exponent)
{
    int result = 1;
    for (int i = 0; i < exponent; i++)
    {
        result *= base;
    }
    return result;
}

char create_char(int *bits, int size)
{
    char c = 0;
    for (int i = 0; i < size; i++)
    {
        if (bits[i] == 1)
        {
            c += power_of_two(2, size - i - 1);
        }
    }
    return c;
}

void handle_signal(int signal, siginfo_t *info, void *context)
{
    static int bit_buffer[8];
    static int buffer_index = 0;
    static int client_pid = 0;
    char character;

    if (client_pid != info->si_pid)
    {
        client_pid = info->si_pid;
        buffer_index = 0;
    }
    bit_buffer[buffer_index++] = (signal == SIGUSR1);
    if (buffer_index == 8)
    {
        character = create_char(bit_buffer, buffer_index);
        write(STDOUT_FILENO, &character, 1);
        buffer_index = 0;
    }
}

int main(int argc, char **argv)
{
    int pid;
    struct sigaction signal_action;

    if (argc != 1)
    {
        printf("Error: Incorrect number of arguments\n");
        return EXIT_FAILURE;
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

