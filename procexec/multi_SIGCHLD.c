/* Code26-5 P460 */
/* ./multi_SIGCHLD 1 2 4 */

#define _GNU_SOURCE
#include <signal.h>
#include <sys/wait.h>
#include "print_wait_status.h"
#include "../time/curr_time.h"
#include "../lib/tlpi_hdr.h"

static volatile int numLiveChildren = 0;

static void sigchldHandler(int sig)
{
    int status,savedErrno;
    pid_t childPid;

    savedErrno = errno; /* In case we modify 'errno' */

    printf("%s handler:Caught SIGCHLD\n",currTime("%T"));

    while((childPid = waitpid(-1,&status,WNOHANG)) > 0)
    {
        printf("%s handler:Reaped child %ld - ",
                    currTime("%T"),(long)childPid);
        
        printWaitStatus(NULL,status);
        numLiveChildren--;
    }

    if(childPid == -1 && errno != ECHILD)
        printf("waitpid");
    
    sleep(5);   /* Artificially lengthen execution of handler */
    printf("%s handler:returning\n",currTime("%T"));

    errno = savedErrno;
}


int main(int argc,char *argv[])
{
    int j,sigCnt;
    sigset_t blockMask,emptyMask;
    struct sigaction sa;

    if(argc < 2 || strcmp(argv[1],"--help") == 0)
        printf("%s child-sleep-time...\n",argv[0]);
    
    setbuf(stdout,NULL);

    sigCnt = 0;
    numLiveChildren = argc - 1;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = sigchldHandler;

    if(sigaction(SIGCHLD,&sa,NULL) == -1)
        printf("sigaction");
    
    /* Block SIGCHLD */
    sigemptyset(&blockMask);
    sigaddset(&blockMask,SIGCHLD);
    if(sigprocmask(SIG_SETMASK,&blockMask,NULL) == -1)
        printf("sigprocmask");

    for(j = 1;j < argc ;j++)
    {
        switch (fork())
        {
        case -1:
            printf("fork");
            exit(EXIT_FAILURE);
        case 0:
            sleep(atoi(argv[j]));
            printf("%s Child %d (PID=%ld) exiting\n",
                    currTime("%T"),j,(long)getpid());
            _exit(EXIT_SUCCESS);
        default:
            break;
        }
    }

    sigemptyset(&emptyMask);
    while(numLiveChildren > 0)
    {
        if(sigsuspend(&emptyMask) == -1 && errno != EINTR)
            printf("sigsuspend");
        sigCnt++;
    }

    printf("%s All %d children have terminated;SIGCHLD was caught"
           " %d times\n",currTime("%T"),argc-1,sigCnt);
    
    exit(EXIT_SUCCESS);

}