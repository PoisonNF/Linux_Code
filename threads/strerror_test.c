/* Code31-2 P546 */

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "../lib/tlpi_hdr.h"

static void *threadFunc(void *arg)
{
    char *str;

    printf("Other thread about to call strerror()\n");
    str = strerror(EPERM);
    printf("Other thread:str(%p) = %s\n",str,str);

    return NULL;
}

int main(int argc,char *argv[])
{
    pthread_t t;
    int s;
    char *str;

    str = strerror(EINVAL);
    printf("Main thread has called strerror()\n");

    s = pthread_create(&t,NULL,threadFunc,NULL);
    if(s != 0)
        printf("pthread_create");
    
    s = pthread_join(t,NULL);
    if(s != 0)
        printf("pthread_join");  

    printf("Main thread:str(%p) = %s\n",str,str);

    exit(EXIT_SUCCESS);
}