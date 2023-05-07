/* Code26-4 P458 */
/* ./make_zombie */

#include <signal.h>
#include <libgen.h> /* For basename() declaration */
#include "../lib/tlpi_hdr.h"

#define CMD_SIZE 200

int main(int argc,char *argv[])
{
    char cmd[CMD_SIZE];
    pid_t childPid;

    setbuf(stdout,NULL);

    printf("Parent PID=%ld\n",(long)getpid());

    switch(childPid = fork())
    {
        case -1:
            printf("fork");
            exit(EXIT_FAILURE);
        case 0: /* Child immediately exits to become zombie */
            printf("Child (PID=%ld) exiting\n",(long)getpid());
            _exit(EXIT_SUCCESS);
        default:
            sleep(3);
            snprintf(cmd,CMD_SIZE,"ps | grep %s",basename(argv[0]));
            cmd[CMD_SIZE] = '\0';
            system(cmd);    /* View zombie child */

            if(kill(childPid,SIGKILL) == -1)
                printf("kill");
            
            sleep(3);   /* Give child a chance to react to signal */

            printf("After sending SIGKILL to zombie (PID=%ld):\n",
                        (long)childPid);
            system(cmd);

            exit(EXIT_SUCCESS);

    }
}