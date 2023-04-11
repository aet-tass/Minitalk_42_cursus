#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

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

    pid = atoi(argv[1]);

    send_message(pid, argv[2]);

    return 0;
}

