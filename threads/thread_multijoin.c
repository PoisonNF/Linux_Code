/* Code30-4 P535 */
/* ./thread_multijoin 1 1 2 3 3 */

#include <pthread.h>
#include "../lib/tlpi_hdr.h"

static pthread_cond_t threadDied = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t threadMutex = PTHREAD_MUTEX_INITIALIZER;

static int totTheads = 0;   //Total number of threads created
static int numLive = 0;     /* Total numer of threads  still alive or terminated but not join */
static int numUnjoined = 0; 

enum tstate{
    TS_ALIVE,
    TS_TERMINATED,
    TS_JOINED
};

static struct {
    pthread_t tid;
    enum tstate state;
    int sleepTime;
} *thread;

static void * threadFunc(void *arg)
{
    int idx = *((int *)arg);
    int s;
    sleep(thread[idx].sleepTime);   //Simulate doing some work
    printf("Thread %d terminating\n",idx);

    s = pthread_mutex_lock(&threadMutex);
    if(s != 0)
        printf("pthread_mutex_lock");
    
    numUnjoined++;
    thread[idx].state = TS_TERMINATED;

    s = pthread_mutex_unlock(&threadMutex);
    if(s != 0)
        printf("pthread_mutex_unlock");
    
    s = pthread_cond_signal(&threadDied);
    if(s != 0)
        printf("pthread_cond_signal");
    
    return NULL;

}

int main(int argc,char *argv[])
{
    int s,idx;

    if(argc < 2 || strcmp(argv[1],"--help") == 0)
        printf("%s nsecs...\n",argv[0]);

    thread = calloc(argc -1 ,sizeof(*thread));
    if(thread == NULL)
        printf("calloc");

    /* Create all threads */
    for(idx = 0;idx < argc-1;idx++)
    {
        thread[idx].sleepTime = atoi(argv[idx+1]);
        thread[idx].state = TS_ALIVE;
        s = pthread_create(&thread[idx].tid,NULL,threadFunc,&idx);
        if(s != 0)
            printf("pthread_create");
    }

    totTheads = argc -1;
    numLive = totTheads;
    
    /* Join with terminated threads */

    while(numLive > 0)
    {
        s = pthread_mutex_lock(&threadMutex);
        if( s != 0)
            printf("pthread_mutex_lock");
        
        while(numUnjoined == 0)
        {
            s = pthread_cond_wait(&threadDied,&threadMutex);
            if(s != 0)
                printf("pthread_cond_wait");
        }

        for(idx = 0;idx < totTheads;idx++)
        {
            if(thread[idx].state == TS_TERMINATED)
            {
                s = pthread_join(thread[idx].tid,NULL);
                if(s != 0)
                    printf("pthread_join");

                thread[idx].state = TS_JOINED;
                numLive--;
                numUnjoined--;
                printf("Reaped thread %d (numLive=%d)\n",idx,numLive);

            }
        }

        s = pthread_mutex_unlock(&threadMutex);
        if(s != 0)
            printf("pthread_mutex_unlock");
    }

    exit(EXIT_SUCCESS);

}