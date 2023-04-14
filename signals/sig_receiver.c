/* Code20-7 P343 */
/*
    ./sig_receiver 15 &
    ./sig_receiver &
*/

#define _GNU_SOURCE
#include <signal.h>
#include "./signal_functions.h"
//#include "../lib/tlpi_hdr.h"

static int sigCnt[NSIG];

/* Set nonzero if SIGINT is delivered */
static volatile sig_atomic_t gotSigint = 0; 

static void handler(int sig)
{
    if(sig == SIGINT)
        gotSigint = 1;
    else
        sigCnt[sig]++;
}

int main(int argc,char *argv[])
{
    int n,numSecs;
    sigset_t pendingMask,blockingMask,emptyMask;

    printf("%s:PID is %ld\n",argv[0],(long)getpid());

    for(n= 1;n<NSIG;n++)
        (void)signal(n,handler);    /* Same handler for all signals */

    if(argc > 1)
    {
        numSecs = atoi(argv[1]);

        sigfillset(&blockingMask);
        if(sigprocmask(SIG_SETMASK,&blockingMask,NULL) == -1)
            printf("sigprocmask");
        
        printf("%s:sleeping for %d seconds\n",argv[0],numSecs);
        sleep(numSecs);

        if(sigpending(&pendingMask) == -1)
            printf("sigpengding");
        
        printf("%s:pending signals are:\n",argv[0]);
        //PrintSigset(stdout,"\t\t",&pendingMask);

            int sig,cnt;

            cnt = 0;
            for(sig = 1;sig < NSIG;sig++)
            {
                if(sigismember(&pendingMask,sig))
                {
                    cnt++;
                    fprintf(stdout,"\t\t%d (%s)\n",sig,strsignal(sig));
                }
            }

            sigemptyset(&emptyMask);
            if(sigprocmask(SIG_SETMASK,&emptyMask,NULL) == -1)
                printf("sigprocmask");
                
    }

    while(!gotSigint)
        continue;

    for(n = 0;n<NSIG;n++)
        if(sigCnt[n] != 0)
            printf("%s:sinal %d caught %d time%s\n",
                    argv[0],n,sigCnt[n],(sigCnt[n] == 1)? "":"s");

    exit(EXIT_SUCCESS);
}