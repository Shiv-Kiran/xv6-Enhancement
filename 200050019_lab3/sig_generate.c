#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

// int kill(pid, int signum); to send the signal

int main(int argc, char *argv[])
{
    // printf("Number of arguments : %d \n", argc);
    // for (int i = 0; i < argc; i++)
    // {
    //     printf("%s \n", argv[i]);
    // }
    pid_t p = atoi(argv[1]);
    // scanf("%d", &p);
    printf("Sending SIGNINT to process %d \n", p);
    int res = kill(p, SIGINT);
    printf("Return value from the process %d \n", res);
    printf("Sending SIGTERM to process %d \n", p);
    res = kill(p, SIGTERM);
    printf("Return value from the process %d \n", res);

    printf("Sending SIGKILL to process %d \n", p);
    res = kill(p, SIGKILL);
    printf("Return value from the process %d \n", res);
}