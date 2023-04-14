/* Code21-2 P356 */
/*  ./sigmask_siglongjmp
    ./sigmask_siglongjmp x
*/

#define _GNU_SOURCE /* Get strsignal() declaration from <string.h> */
#include <string.h>
#include <setjmp.h>
#include <signal.h>
#include "../lib/tlpi_hdr.h"
#include "signal_functions.h"


/* Set to 1 once "env" buffer has been initialized by [sig]setjmp() */
static volatile sig_atomic_t canJmp = 0;

#ifdef USE_SIGSETJMP
static sigjmp_buf senv;
#else 
static jmp_buf env;
#endif

static void handler(int sig)
{
    printf("Received signal %d(%s),signal mask is:\n",sig,strsignal(sig));
    PrintSigMask(stdout,NULL);

    if(!canJmp)
    {
        printf("'env' buffer not yet set,doing a simple return\n");
        return;
    }

#ifdef USE_SIGSETJMP
    siglongjmp(senv,1);
#else 
    longjmp(env,1);
#endif
}

int main(int argc,char *argv[])
{
    struct sigaction sa;

    PrintSigMask(stdout,"Signal mask at startup:\n");

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    if(sigaction(SIGINT,&sa,NULL) == -1)
        printf("sigaction");

#ifdef USE_SIGSETJMP
    printf("Calling sigsetjmp()\n");
    if(sigsetjmp(senv,1) == 0)
#else 
    printf("Calling setjmp()\n");
    if(setjmp(env) == 0)
#endif    
        canJmp = 1;         /* Executed after [sig]setjmp() */
    
    else
        PrintSigMask(stdout,"After jump from handler,signal mask is:\n");

    for(;;)
        pause();
}
