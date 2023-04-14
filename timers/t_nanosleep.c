/* Code23-3 P405 */
/*  ./t_nanosleep 10 0
    ctrl+c
*/

#define _GNU_SOURCE
#define _POSIX_C_SOURCE 199309
#include <sys/time.h>
#include <time.h>
#include <signal.h>
#include "../lib/tlpi_hdr.h"

static void sigintHandler(int sig)
{
    return;         /* just interrupt nanosleep() */
}

int main(int argc,char *argv[])
{
    struct timeval start,finish;
    struct timespec request,remain;
    struct sigaction sa;
    int s;

    if(argc > 3 || strcmp(argv[1],"--help") == 0)
        printf("%s secs nanosecs\n",argv[0]);

    request.tv_sec = atol(argv[1]);
    request.tv_nsec = atol(argv[2]);

    /* Allow SIGINT handler to interrupt nanosleep() */

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = sigintHandler;
    if(sigaction(SIGINT,&sa,NULL) == -1)
        printf("sigaction");
    
    if(gettimeofday(&start,NULL) == -1)
        printf("gettimeofday");

    for(;;)
    {
        s = nanosleep(&request,&remain);

        /* signal is not provided by interrupt */
        if(s == -1 && errno != EINTR)
            printf("nanosleep");

        if(gettimeofday(&finish,NULL) == -1)
            printf("gettimeofday");

        printf("Slept for:%9.6f secs\n",finish.tv_sec- start.tv_sec +
                            (finish.tv_usec - start.tv_usec)/1000000.0);

        if(s == 0)
            break;
        
        printf("Remaining: %2ld.%09ld\n",(long)remain.tv_sec,
                        remain.tv_nsec);
        request = remain;
    }

    printf("Sleep complete\n");
    exit(EXIT_SUCCESS);
}