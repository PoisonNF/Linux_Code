/* Code26-1 P448 */
/* ./multi_wait 7 1 4 */

#include <sys/wait.h>
#include <time.h>
#include "../lib/tlpi_hdr.h"
#include "../time/curr_time.h"

int main(int argc,char *argv[])
{
    int numDead;
    pid_t childPid;
    int j;

    if(argc < 2 || strcmp(argv[1],"--help") == 0)
        printf("%s sleep-time...\n",argv[0]);
    
    setbuf(stdout,NULL);

    for(j = 1; j < argc ;j++)
    {
        switch (fork())
        {
        case -1:
            printf("fork");
            break;
        
        case 0:
            printf("[%s]child %d started with PID %ld,sleeping %s"
                    "seconds\n",currTime("%T"),j,(long)getpid(),argv[j]);
            sleep(atoi(argv[j]));
            _exit(EXIT_SUCCESS);
        default:
            break;
        }
    }

    numDead = 0;
    for(;;)
    {
        childPid = wait(NULL);      /* Parent waits for each child to exit */
        if(childPid == -1)
        {
            if(errno == ECHILD)
            {
                printf("No more children -bye!\n");
                exit(EXIT_SUCCESS);
            }
        }
        else
        {
            printf("wait");
        }

        numDead++;
        printf("[%s] wait() returned child PID %ld (numDead = %d)\n",
                currTime("%T"),(long)childPid,numDead);
    }
}