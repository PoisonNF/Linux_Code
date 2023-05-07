/* Code30-2 P525 */
/* ./thread_incr_mutex num */

#include <pthread.h>
#include "../lib/tlpi_hdr.h"

static int glob = 0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

static void *threadFunc(void *arg)
{
    int loops = *((int *)arg);  //loops == arg
    int loc,j,s;
    
    for ( j = 0; j < loops; j++)
    {
        s = pthread_mutex_lock(&mtx);

        loc = glob;
        loc++;
        glob = loc;

        s = pthread_mutex_unlock(&mtx);
        //glob++;
    }

    return NULL;
}

int main(int argc,char *argv[])
{
    pthread_t t1,t2;
    int loops,s;

    loops = (argc > 1)?atoi(argv[1]):10000000;

    s = pthread_create(&t1,NULL,threadFunc,&loops);
    if(s != 0)
        printf("pthread_create");
    s = pthread_create(&t2,NULL,threadFunc,&loops);
    if(s != 0)
        printf("pthread_create");

    s = pthread_join(t1,NULL);
    if(s != 0)
        printf("pthread_join");
    s = pthread_join(t2,NULL);
    if(s != 0)
        printf("pthread_join");

    printf("glob = %ld\n",(long)glob);

    exit(EXIT_SUCCESS);
}