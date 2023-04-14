/* Code20-4 P338 */

#define _GNU_SOURCE
#include <string.h>
#include <signal.h>
#include "signal_functions.h"
//#include "../lib/tlpi_hdr.h"

void         /* Print list of signals within a signal set */
PrintSigset(FILE *of,const char *prefix,const sigset_t *sigset)
{
    int sig,cnt;

    cnt = 0;
    for(sig = 1;sig < NSIG;sig++)
    {
        if(sigismember(sigset,sig))
        {
            cnt++;
            fprintf(of,"%s%d (%s)\n",prefix,sig,strsignal(sig));
        }
    }

    if(cnt == 0)
        fprintf(of,"%s<empty signal set>\n",prefix);
}

int        /* Print mask of blocked signals for this process */
PrintSigMask(FILE *of,const char *msg)
{
    sigset_t currMask;

    if(msg != NULL)
        fprintf(of,"%s",msg);
    
    if(sigprocmask(SIG_BLOCK,NULL,&currMask) == -1)
        return -1;
    
    PrintSigset(of,"\t\t",&currMask);

    return 0;
}

int     /* print signals currently pending for this process */
PrintPendingSigs(FILE *of,const char *msg)
{
    sigset_t pendingSigs;

    if(msg != NULL)
        fprintf(of,"%s",msg);

    if(sigpending(&pendingSigs) == -1)
        return -1;
    
    PrintSigset(of,"\t\t",&pendingSigs);

    return 0;
}

