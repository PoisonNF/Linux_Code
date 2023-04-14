/* Code20-2 P332 */
/* ./intquit
    ctrl + c
    ctrl + \
*/

#include <signal.h>
#include "../lib/tlpi_hdr.h"

static void sigHandler(int sig)
{
    static int count = 0;
    /* Unsafe: uses non-async-signal-safe functions
        printf(),exit() */

    if(sig == SIGINT)
    {
        count ++;
        printf("Caught SIGINT (%d)\n",count);
        return;     /* Resume execution at point of interruption */
    }

    /* Must be SIGQUIE -print a message */
    else if(sig == SIGQUIT)
    {
        printf("Caught SIGQUIT - that`s all folks!\n");
        exit(EXIT_SUCCESS);
    }

}

int main(int argc,char *argv[])
{
    /* Establish same handler for SIGINT and SIGQUIT */

    if(signal(SIGINT,sigHandler) == SIG_ERR)
        printf("signal");
    if(signal(SIGQUIT,sigHandler) == SIG_ERR)
        printf("signal");
    
    while(1)
    {
        pause();
    }
}