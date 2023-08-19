/* tour.c
 * To learn the basic signal handling in c
 * Can send the interrupt signal via Ctrl-c in a terminal.
 *
 * Complete TODO items for this question
 */

#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM_FRIEND 5 // Number of friends visiting the Dinosaurs Park

int friend_count = 0; // Current count of friends completed the tour

// TODO: Add a signal handling function which handle SIGINT and SIGCHLD signals
void handler(int signum)
{
    fprintf(stdout, "You have interruped the tour.  signal called is : %d \n", signum);
}

// END TODO
int main(int argc, char *argv[])
{

    printf("Welcome to the Dinosaurs Park.\n");

    /*
     * TODO: add struct/calls to sigaction() to handle SIGINT and SIGCHLD.
     * Use sigaction() and associated structs.
     * Ensure that the flag SA_RESTART is set as well to ensure system calls are automatically restarted.
     */
    //  The  sigaction()  system call is used to change the action taken by a process on receipt of a specific signal.
    /*
    struct sigaction {
               void     (*sa_handler)(int);  // pointer to function whch handles sign
               void     (*sa_sigaction)(int, siginfo_t *, void *);
     then sa_sigaction (instead of sa_handler) specifies the signal-handling function for signum.
               sigset_t   sa_mask;
               int        sa_flags;
               void     (*sa_restorer)(void);
    };
    */
    struct sigaction act;
    act.sa_handler = &handler;
    // act.sa_handler = SIG_IGN;
    act.sa_flags = 0;
    // sigsuspend(&act.sa_mask);
    // sigfillset(&act.sa_mask);
    sigprocmask(SIG_SETMASK, &act.sa_mask, NULL);
    // act.sa_mask = SIGINT;
    // Registering SIGINT handler.
    if (sigaction(SIGINT, &act, NULL) == -1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // while(1){
    // if (act.sa_handler == SIG_IGN)
    //     printf("SIGCHLD being ignored \n");
    // else if (info.sa_handler == SIG_DFL)
    //     printf("SIGCHL")

    // }

    // struct sigaction(){
    //     signal(SIGINT, handler);
    //     signal(SIGCHLD, handler);
    // };

    // END TODO
    int par_pid = getpid();
    printf("The Process ID of Dinosaurs Park: %d \n", getpid());
    for (size_t friend = 1; friend <= NUM_FRIEND; friend ++)
    {
        if (fork() == 0)
        {
            setpgid(getpid(), par_pid);
            // TODO Note that, you must carefully place the various children in different process groups
            //  that is different from the default process group of its parent
            // say, using the setpgid system call.

            //   int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

            /*
            Sleep is an interruptible function. If a signal handler runs while your thread is in it, the sleep is going to abort. So then you proceed to the next kill, which is going to indirectly cause another SIGCHLD which will most likely happen when your next iteration's sleep, resulting in several skipped sleeps.
            */

            if (sigaction(SIGINT, &act, NULL) == -1)
            {
                perror("sigaction");
                exit(EXIT_FAILURE);
            }
            // if (act.sa_handler == SIG_IGN)
            //     printf("There are still %d people left \n", NUM_FRIEND - friend);
            sleep(2 * friend); // sleep emulates "touring" time

            printf("Friend #%zu with process ID - %d has completed the tour. with parent as %d \n", friend, getpid(), getppid());
            exit(0);
            // END TODO
        }
        else
        {
            wait(NULL);
        }
    }
    printf("All 5 friends have completed the tours. \nThank you for visiting the Dinosaurs Park \n");

    for (;;)
        pause(); // wait for all friends to complete tour
    return 0;
}
