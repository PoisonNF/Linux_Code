/* Code24-1 P428 */
/* ./t_fork */

#include "../lib/tlpi_hdr.h"

static int idata = 111; /* Allocated in data segment */

int main(int argc,char *argv[])
{
    int istack = 222;
    pid_t childPid;

    switch(childPid = fork())
    {
        case -1:
            printf("fork");
        
        case 0:
            idata *= 3;
            istack *=3;
            break;
        default:
            sleep(1);
            break;
    }

    /* Both parent and child come here */

    printf("PID=%ld %s idata=%d istack=%d\n",
        (long)getpid(),(childPid == 0)?"(child)":"(parent)",
        idata,istack);
      
    exit(EXIT_SUCCESS);
}