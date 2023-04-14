/* Code21-3 P360 */
/*  ulimit -s unlimited
    ./t_sigaltstack
 */

#define _GNU_SOURCE
#include <string.h>
#include <signal.h>
#include "../lib/tlpi_hdr.h"

static void sigsegvHandler(int sig)
{
    int x;

    printf("Caught signal %d (%s)\n",sig,strsignal(sig));
    printf("Top of handler stack near %10p\n",(void *)&x);
    fflush(NULL);

    _exit(EXIT_FAILURE);        /* Can`t return after SIGSEGV*/
}

/* A recursive function that overflows the stack */
static void overflowStack(int callNum)
{
    char a[100000]; /* Make this stack frame large */

    printf("Call %4d - top of stack near %10p\n",callNum,&a[0]);
    overflowStack(callNum +1);  /* recurrence */
}

int main(int argc,char *argv[])
{
    stack_t sigstack;
    struct sigaction sa;
    int j;

    printf("Top of standard stack is near %10p\n",(void *)&j);

    sigstack.ss_sp = malloc(SIGSTKSZ);
    if(sigstack.ss_sp == NULL)
        printf("malloc");
    sigstack.ss_size = SIGSTKSZ;
    sigstack.ss_flags = 0;
    if(sigaltstack(&sigstack,NULL) == -1)
        printf("sigaltstack");

    printf("Alternate stack is at %10p-%p\n",sigstack.ss_sp,(char *)sbrk(0)-1);

    sa.sa_handler = sigsegvHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_ONSTACK;       /* Handler uses alternate stack */
    if(sigaction(SIGSEGV,&sa,NULL) == -1)
        printf("sigaction");
    
    overflowStack(1);
}