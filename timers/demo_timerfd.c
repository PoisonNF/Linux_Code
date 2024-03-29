/* Code23-8 P422 */
/* ./demo_timerfd 1:1 100 
    ctrl_z
    fg
*/
#define _GNU_SOURCE
#include <sys/timerfd.h>
#include <time.h>
#include <stdint.h>
#include "itimerspec_from_str.h"
#include "../lib/tlpi_hdr.h"

int main(int argc,char *argv[])
{
    struct itimerspec ts;
    struct timespec start,now;
    int maxExp,fd,secs,nanosecs;
    uint64_t numExp,totalExp;
    ssize_t s;

    if(argc < 2 || strcmp(argv[1],"--help") == 0)
        printf("%s secs[/nsecs][:int-secs[/int-nsecs]][max_exp]\n",argv[0]);
    
    itimerspecFromStr(argv[1],&ts);
    maxExp = (argc > 2)?atoi(argv[2]):1;
    
    fd = timerfd_create(CLOCK_REALTIME,0);
    if(fd == -1)
        printf("timerfd_create");
    
    if(timerfd_settime(fd,0,&ts,NULL) == -1)
        printf("timerfd_Settime");
    
    if(clock_gettime(CLOCK_MONOTONIC,&start) == -1)
        printf("clock_gettime");
    
    for(totalExp = 0;totalExp < maxExp;)
    {
        s = read(fd,&numExp,sizeof(uint64_t));
        if(s != sizeof(uint64_t))
            printf("read");

        totalExp += numExp;

        if(clock_gettime(CLOCK_MONOTONIC,&now) == -1)
            printf("clock_gettime");
        
        secs = now.tv_sec - start.tv_sec;
        nanosecs = now.tv_nsec - start.tv_nsec;
        if(nanosecs < 0)
        {
            secs--;
            nanosecs += 1000000000;
        }

        printf("%d.%03d: expirations read: %llu;total = %llu\n",
                    secs,(nanosecs + 500000)/1000000,
                    (unsigned long long)numExp,(unsigned long long)totalExp);

    }
    exit(EXIT_SUCCESS);
}

