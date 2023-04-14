/* Code23-2 P403 */
/* ./timed_read 10
*/

#define _GNU_SOURCE
#include <signal.h>
#include "../lib/tlpi_hdr.h"

#define BUF_SIZE 200

static void handler(int sig)
{
    printf("Caught signal\n");
}

int main(int argc,char *argv[])
{
    struct sigaction sa;
    char buf[BUF_SIZE];
    ssize_t numRead;
    int savedErrno;

    if(argc > 1 && strcmp(argv[1],"--help") == 0)
        printf("%s [num-secs [restart-flag]]\n",argv[0]);

    /* Set up handler for SIGALRM */

    sa.sa_flags = (argc > 2)?SA_RESTART:0;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = handler;
    if(sigaction(SIGALRM,&sa,NULL) == -1)
        printf("sigaction");
    
    alarm((argc > 1)? atoi(argv[1]) : 10);

    numRead = read(STDIN_FILENO,buf,BUF_SIZE -1);

    savedErrno = errno;
    alarm(0);
    errno = savedErrno;

    /* Determine result of read() */

    if(numRead == -1)
    {
        if(errno == EINTR)
            printf("Read timed out\n");
        else
            printf("read");
    }
    else
    {
        printf("Successful read (%ld bytes): %.*s",
                (long)numRead,(int)numRead,buf);
    }
    exit(EXIT_SUCCESS);
}