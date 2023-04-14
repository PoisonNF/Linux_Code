/* Code 20-1 P331 */
/* ./ouch
    ctrl+c
*/

#include <signal.h>
#include "../lib/tlpi_hdr.h"

static void sigHandler(int sig)
{
    printf("Ouch!\n");      /* Unsafe (see Section 21.1.2) */
}

int main(int argc,char *argv[])
{
    int j;

    if(signal(SIGINT,sigHandler) == SIG_ERR)
        printf("signal");
    
    for(j = 0;;j++)
    {
        printf("%d\n",j);
        if(j > 4)  j = -1;
        sleep(3);
    }
}
