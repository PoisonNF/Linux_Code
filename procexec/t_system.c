/* Code27-7 P479 */
/* ./t_system
    whoami

    ls | grep XYZ

    exit 127

    sleep 100

    ps | grep sleep

    kill pid

    fg

    ctrl+D

 */

#include <sys/wait.h>
#include "print_wait_status.h"
#include "../lib/tlpi_hdr.h" 

#define MAX_CMD_LEN 200

int main(int argc,char *argv[])
{
    char str[MAX_CMD_LEN];  /* Command to be executed by system() */

    int status;

    for(;;)
    {
        printf("Command:");
        fflush(stdout);
        if(fgets(str,MAX_CMD_LEN,stdin) == NULL)
            break;
        
        status = system(str);
        printf("system() returned: status=0x%04x (%d,%d)\n",
                (unsigned int)status,status >> 8,status & 0xff);

        if(status == -1)
            printf("system");
        else
        {
            if(WIFEXITED(status) && WEXITSTATUS(status) == 127)
                printf("(Probably)could not invoke shell\n");
            else
                printWaitStatus(NULL,status);
        }
    }

    exit(EXIT_SUCCESS);
}