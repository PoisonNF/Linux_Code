/* Code22-3 P382 */
/*  ./catch_rtsigs 60 &
*/

#define _GNU_SOURCE
#include <string.h>
#include <signal.h>
#include "../lib/tlpi_hdr.h"

static volatile int handlerSleepTime;
static volatile int sigCnt = 0;     /* Number of signals received */
static volatile int allDone = 0;

/* Handler for signals established using SA_SIGINFO */
static void siginfoHandler(int sig,siginfo_t *si,void *ucontext)
{
    if(sig == SIGINT || sig == SIGTERM)
    {
        allDone = 1;
        return;
    }

    sigCnt++;
    printf("caught signal %d\n",sig);

    printf("    si_signo=%d,si_code=%d (%s),",si->si_signo,si->si_code,
                (si->si_code == SI_USER)?"SI_USER":
                (si->si_code == SI_QUEUE)?"SI_QUEUE":
                "other");

    printf("si_value=%d\n",si->si_value.sival_int);
    printf("    si_pid=%ld,si_uid=%ld\n",(long)si->si_pid,(long)si->si_uid);

    sleep(handlerSleepTime);
}

int main(int argc,char *argv[])
{
    struct sigaction sa;
    int sig;
    sigset_t prevMask,blockMask;

    if(argc > 1 && strcmp(argv[1],"--help") == 0)
        printf("%s [block-time [handler-sleep-time]]\n",argv[0]);

    printf("%s:PID is %ld\n",argv[0],(long)getpid());
    handlerSleepTime = (argc > 2) ? atoi(argv[2]):1;

    sa.sa_sigaction = siginfoHandler;
    sa.sa_flags = SA_SIGINFO;
    sigfillset(&sa.sa_mask);

    for(sig = 1; sig < NSIG;sig++)
    {
        if(sig != SIGINT && sig != SIGQUIT)
            sigaction(sig,&sa,NULL);
    }

    if(argc > 1)
    {
        sigfillset(&blockMask);
        sigdelset(&blockMask,SIGINT);
        sigdelset(&blockMask,SIGTERM);

        if(sigprocmask(SIG_SETMASK,&blockMask,&prevMask) == -1)
            printf("sigprocmask");

        printf("%s:signals blocked - sleeping %s seconds\n",argv[0],argv[1]);
        sleep(atoi(argv[1]));
        printf("%s:sleep complete\n",argv[0]);

        if(sigprocmask(SIG_SETMASK,&prevMask,NULL) == -1)
            printf("sigprocmask");
    }

    while(!allDone)
        pause();
}
