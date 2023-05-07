/* Code27-6 P476 */
/*  ./closeonexec
    ./closeonexec n
 */

#include <fcntl.h>
#include "../lib/tlpi_hdr.h"

int main(int argc,char *argv[])
{
    int flags;

    if(argc > 1)
    {
        flags = fcntl(STDOUT_FILENO,F_GETFD);   /* Fetch flags */
        if(flags == -1)
            printf("fcntl F_GETFD");
        
        flags |= FD_CLOEXEC;

        if(fcntl(STDOUT_FILENO,F_SETFD,flags) == -1)
            printf("fcntl F_SETFD");
    }

    execlp("ls","ls","-l",argv[0],(char *)NULL);
    exit(EXIT_FAILURE);
}