/* Code20-6 P342*/
/* ./sig_sender pid 10000000 10 2
*/

#include <signal.h>
#include "../lib/tlpi_hdr.h"

int main(int argc,char *argv[])
{
    int numSigs,sig,j;
    pid_t pid;

    if(argc < 4 || strcmp(argv[1],"--help") == 0)
        printf("%s pid num-sigs sig-num [sig-num-2]\n",argv[0]);
    
    pid = atol(argv[1]);

    numSigs = atoi(argv[2]);
    sig = atoi(argv[3]);

    /* Send signals to receiver */
    printf("%s:sending signal %d to process %ld %d times\n",
                argv[0],sig,(long)pid,numSigs);
    
    for(j=0;j<numSigs;j++)
        if(kill(pid,sig) == -1)
            printf("kill");
    
    /* If a fourth command-line argument was specified,send that signal */

    if(argc > 4)
        if(kill(pid,atoi(argv[4])) == -1)
            printf("kill");
    
    printf("%s :exiting\n",argv[0]);
    exit(EXIT_SUCCESS);
}