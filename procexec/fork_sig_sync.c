/* Code24-6 P437 */
/* ./fork_sig_sync */

#define _GNU_SOURCE
#include <signal.h>
#include "../time/curr_time.h"
#include "../lib/tlpi_hdr.h"

#define SYNC_SIG SIGUSR1

static void handler(int sig)
{

}

int main(int argc,char *argv[])
{
    pid_t childPid;
    sigset_t blockMask,origMask,emptyMask;
    struct sigaction sa;

    setbuf(stdout,NULL);

    sigemptyset(&blockMask);
    sigaddset(&blockMask,SYNC_SIG);
    if(sigprocmask(SIG_BLOCK,&blockMask,&origMask) == -1)
        printf("sigprocmask");
    
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = handler;
    if(sigaction(SYNC_SIG,&sa,NULL) == -1)
        printf("sigaction");
    
    switch(childPid = fork())
    {
        case -1:
            printf("fork");
        
        case 0:
            /* Child does some required action here */
            printf("[%s %ld]Child started - doing some work\n",
                    currTime("%T"),(long)getpid());
            sleep(2);

            /* And then signals parent that it's done */

            printf("[%s %ld]Child about to signal parent\n",
                    currTime("%T"),(long)getpid());
            if(kill(getppid(),SYNC_SIG) == -1)
                printf("kill");

            /* Now child can do other things */

            _exit(EXIT_SUCCESS);

        default:
            /* Parent may do some work here,and waits for child
                to complete the required action */
            printf("[%s %ld]Parent about to wait for signal\n",
                    currTime("%T"),(long)getpid());
            sigemptyset(&emptyMask);
            if(sigsuspend(&emptyMask) == -1 && errno != EINTR)
                printf("sigsuspend");
            printf("[%s %ld]Parent got signal\n",currTime("%T"),
                        (long)getpid());
            
            /* If required,return signal mask to its original state */

            if(sigprocmask(SIG_SETMASK,&origMask,NULL) == -1)
                printf("sigprocmask");
            
            exit(EXIT_SUCCESS);

    }
}