/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c             ########    ## #     ##    ##             ## ##     */
/*                                                    +:+ +:+         +:+     */
/*   By: aet-tass <aet-tass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:49:29 by aet-tass          #+#    #+#             */
/*   Updated: 2023/04/14 05:19:15 by aet-tass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void send_message(int pid, char *message)
{
    int bit;

    while (*message != '\0') 
    {
        int i;
       	i = 7;
        while (i >= 0)
       	{
            bit = (*message >> i) & 1;
            if (bit == 0)
                kill(pid, SIGUSR1);
            else
                kill(pid, SIGUSR2);
            usleep(200);
            i--;
        }
        usleep(100);
        message++;
    }
}

int main(int argc, char *argv[])
{
    int pid;

    if (argc != 3)
    {
        printf("Usage: %s pid message\n", argv[0]);
        return 1;
    }

    pid = ft_atoi(argv[1]);

    send_message(pid, argv[2]);

    return 0;
}
