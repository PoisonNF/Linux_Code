/* Code26-3 P453 */
/*  ./child_status 23

    ./child_status &
    kill -STOP pid
    kill -CONF pid
    kill -ABRT pid
    ls -l core

    ulimit -c unlimited
    ./child_status &
    kill -ABRT pid
    ls -l core
 */

#include <sys/wait.h>
#include "print_wait_status.h"
#include "../lib/tlpi_hdr.h"

int main(int argc,char *argv[])
{
    int status;
    pid_t childPid;

    if(argc > 1 && strcmp(argv[1],"--help") == 0)
        printf("%s [exit-status]\n",argv[0]);
    
    switch(fork())
    {
        case -1:
            printf("fork");
            exit(EXIT_FAILURE);

        case 0:
            printf("Child started with PID = %ld\n",(long)getpid());
            if(argc > 1)        /* exit now! */
                exit(atoi(argv[1]));
            else                /* wait for signals */
                for(;;)
                    pause();   
            
            exit(EXIT_FAILURE); /* Not reached,but good practice */
        
        default:
            for(;;)
            {
                childPid = waitpid(-1,&status,WUNTRACED
#ifdef WCONTINUED       /* Not present on older versions of Linux */
                                            |WCONTINUED
#endif
                );

                if(childPid == -1)
                    printf("waitpid");

                printf("waitpid() returned: PID=%ld;status=0x%04x (%d,%d)\n",
                (long)childPid,
                (unsigned int)status,status >> 8,status & 0xff);
                printWaitStatus(NULL,status);

                if(WIFEXITED(status) || WIFSIGNALED(status))
                    exit(EXIT_SUCCESS);
            }
    }
}