/* Code6-1 P95 */
/* ./mem_segments */

#include <stdio.h>
#include <stdlib.h>

char globBuf[65536];        /* Uninitialized data segment */
int primes[] = {2,3,5,7};   /* Initialized data segmeny */

static int square(int x)
{
    int result;             /* Allocated in frame for square() */

    result = x*x;
    return result;          /* Return value passed via register */
}

static void doCalc(int val)
{
    printf("The square of %d is %d\n",val,square(val));

    if(val < 1000)
    {
        int t;
        
        t = val*val*val;    /* Allocated in frame for doCalc() */
        printf("The cube of %d is %d\n",val,t);
    }
}

int main(int argc,char *argv[])
{
    static int key = 9973;
    static char mbuf[10240000];
    char *p;

    p = malloc(1024);

    doCalc(key);

    exit(EXIT_SUCCESS);
}