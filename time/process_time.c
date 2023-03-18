/* Code10-5 P170*/
/* ./process_time 10000000 */

#include <sys/times.h>
#include <time.h>
#include "../lib/tlpi_hdr.h"

/* Display 'msg' and process times */
static void displayProcessTimes(const char *msg)
{
    struct tms t;
    clock_t clockTime;
    static long clockTicks = 0;

    if(msg != NULL)
        printf("%s",msg);

    if(clockTicks == 0) /* Fetch clock ticks on first call */
    {
        clockTicks = sysconf(_SC_CLK_TCK);
        if(clockTicks == -1)
            printf("sysconf");
    }

    clockTime = clock();
    if(clockTime == -1)
        printf("clock");
    
    printf("        clock( returns:%ld clocks-per-sec (%.2f secs)\n",
                    (long)clockTime,(double)clockTime/CLOCKS_PER_SEC);
    
    if(times(&t) == -1)
        printf("times");
    printf("        times() yields:user CPU=%.2f;system CPU:%.2f\n",
                    (double) t.tms_utime/clockTicks,
                    (double) t.tms_stime/clockTicks);
}

int main(int argc,char *argv[])
{
    int numCalls,j;

    printf("CLOCKS_PER_SEC=%ld   sysconf(_SC_CLK_TCK)=%ld\n\n",
                (long)CLOCKS_PER_SEC,sysconf(_SC_CLK_TCK));
    
    displayProcessTimes("At program start:\n");


    numCalls = (argc>1)?atoi(argv[1]):100000000;
    for(j = 0;j < numCalls;j++)
        (void) getppid();
    
    displayProcessTimes("After getppid() loop:\n");

    exit(EXIT_SUCCESS);
}