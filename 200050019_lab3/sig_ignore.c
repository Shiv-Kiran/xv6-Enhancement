#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h> // for signal

// typedef void (*sighandler_t)(int);
// sighandler_t signal (int signum, sighandler_t handler);
// man 2 signal man 7 signal
// we can read signals using signal(int signum, sighandler_t handler);
// writing signals are done by kill(), raise(), tgkill(),
// waiting for signal to be caught pause() - suspends execution until any signal is caught.

void sig_handler(int signum)
{
    fprintf(stdout, "Hello There \n");
    // exit(0);
}

void sig_handler1(int signum)
{
    // exit(0);
    fprintf(stdout, "Well Hello there \n");
}

int main1()
{
    signal(SIGINT, sig_handler); // Register signal handler
    // This automatically creates SIG_IGN and then does its thing
    signal(SIGINT, sig_handler1); // last sequence in the signal is taking care.
    printf("Process ID is: %d \n", getpid());
    for (int i = 1;; i++)
    { // Infinite loop
        printf("%d : Inside main function\n", i);
        sleep(3); // Delay for 1 second
    }
    return 0;
}

int main()
{
    fprintf(stdout, "Process ID is : %d \n", (int)getpid());
    fflush(stdout);
    // signal(SIGINT, sig_handler);
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler1); // kill pid
    // SIGKILL, SIGABRT cannot be changed
    // kill -9 pid    kill -SIGABRT 30823
    while (1)
    {
        sleep(3);
        fprintf(stdout, "Waiting... \n");
    }
    return 0;
}
