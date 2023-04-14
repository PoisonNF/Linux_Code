/* Code22-5 P385 */
/* ./t_sigsuspend
 */

#define _GNU_SOURCE
#include <string.h>
#include <signal.h>
#include <time.h>
#include "signal_functions.h"
#include "../lib/tlpi_hdr.h"

static volatile sig_atomic_t gotSigquit = 0;

static void handler(int sig)
{
    printf("Caught signal %d (%s)\n",sig,strsignal(sig));

    if(sig == SIGQUIT)
        gotSigquit = 1;
}

int main(int argc,char *argv[])
{
    int loopNum;
    time_t startTime;
    sigset_t origMask,blockMask;
    struct sigaction sa;

    PrintSigMask(stdout,"Initial signal mask is:\n");

    sigemptyset(&blockMask);
    sigaddset(&blockMask,SIGINT);
    sigaddset(&blockMask,SIGQUIT);
    if(sigprocmask(SIG_BLOCK,&blockMask,&origMask) == -1)
        printf("sigprocmask - SIG_BLOCK");
    
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    if(sigaction(SIGINT,&sa,NULL) == -1)
        printf("sigaction1");
    if(sigaction(SIGQUIT,&sa,NULL) == -1)
        printf("sigaction2");

    for(loopNum = 1;!gotSigquit;loopNum ++)
    {
        printf(" === LOOP %d\n",loopNum);

        PrintSigMask(stdout,"Starting critical section,signal mask is:\n");
        for(startTime = time(NULL);time(NULL) < startTime +4;)
            continue;
        
        PrintPendingSigs(stdout,"Before sigsuspend() - pending signals:\n");
        if(sigsuspend(&origMask) == -1 && errno != EINTR)
            printf("sigsuspend");
    }

    if(sigprocmask(SIG_SETMASK,&origMask,NULL) == -1)
        printf("sigprocmask - SIG_SETMASK");

    PrintSigMask(stdout,"=== Exited loop\nRestored signal mask to:\n");

    exit(EXIT_SUCCESS);
}