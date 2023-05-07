/* Code24-5 P435 */
/* ./fork_whos_on_first 100 */

#include <sys/wait.h>
#include "../lib/tlpi_hdr.h"

int main(int argc,char *argv[])
{
    int numChildren,j;
    pid_t childPid;

    if(argc > 1 && strcmp(argv[1],"--help") == 0)
        printf("%s [num-children]\n",argv[0]);
    
    numChildren = (argc > 1)?atoi(argv[1]):1;

    setbuf(stdout,NULL);

    for(j = 0;j < numChildren;j++)
    {
        switch(childPid = fork())
        {
            case -1:
                printf("fork");
            case 0:
                printf("%d child\n",j);
                _exit(EXIT_SUCCESS);
            default:
                printf("%d parent\n",j);
                wait(NULL);
        }
    }

    exit(EXIT_SUCCESS);
}