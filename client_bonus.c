/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 17:22:26 by aet-tass          #+#    #+#             */
/*   Updated: 2023/04/23 18:59:10 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
void	message_check(int sig, siginfo_t *check, void *message)
{
	(void)check;
	(void)message;
	if (sig == SIGUSR1)
		ft_printf("\nmessage well recieved");
}
int encode_bit(char c, int i)
{
    return (c >> i) & 1;
}

void send_bit(int pid, int bit)
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

void send_encoded_message(int pid, char *message)
{
    int bit;

    while (*message != '\0')
    {
        int i = 7;
        while (i >= 0)
        {
            bit = encode_bit(*message, i);
            send_bit(pid, bit);
            i--;
        }
        usleep(100);
        message++;
    }
	kill('\0', SIGUSR1);
}


int main(int argc, char *argv[])
{
    int pid;
	struct	sigaction	check;

	check.sa_sigaction = &message_check;
	check.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &check, NULL);

    if (argc != 3)
    {
        ft_printf("Usage: %s pid message\n", argv[0]);
        return 1;
    }

    pid = ft_atoi(argv[1]);
	if (pid <= 0)
		exit(1);
	else
    	send_encoded_message(pid, argv[2]);

    return 0;
}
