/* Code23-6 P416 */

#define _POSIX_C_SOURCE 199309
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "itimerspec_from_str.h"


/* Convert a string 
    value.sec[/value.nanosec][:interval.sec[/interval.nanosec]]    
 */

void itimerspecFromStr(char *str,struct itimerspec *tsp)
{
    char *cptr,*sptr;

    /* judge ':' */
    cptr = strchr(str,':');
    if(cptr != NULL)
        *cptr = '\0';
    
    /* gain it_value */
    sptr = strchr(str,'/');
    if(sptr != NULL)
        *sptr = '\0';

    tsp->it_value.tv_sec = atoi(str);
    tsp->it_value.tv_nsec = (sptr != NULL) ? atoi(sptr+1) : 0;

    if(cptr == NULL)
    {
        tsp->it_interval.tv_nsec = 0;
        tsp->it_interval.tv_sec = 0;
    }
    else
    {
        sptr = strchr(cptr+1,'/');
        if(sptr != NULL)
            *sptr = '\0';
        tsp->it_interval.tv_sec = atoi(cptr+1);
        tsp->it_interval.tv_nsec = (sptr != NULL)?atoi(sptr+1):0;
    }
}