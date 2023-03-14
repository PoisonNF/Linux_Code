/* Code6-4 P106 */
/*  ./modify_env "GREET=Guten Tag" SHELL=/bin/bash BYE=Ciao
    ./modify_env SHELL=/bin/sh BYE=byebye
 */

#define _GUN_SOURCE     /* To get various declarations from <stdlib.h> */
#include <stdlib.h>
#include "../lib/tlpi_hdr.h"

extern char **environ;

int main(int argc,char *argv[])
{
    int j;
    char **ep;

    clearenv();         /* Erase entire environment */

    for(j = 1;j<argc;j++)
        if(putenv(argv[j]) != 0)
            printf("putenv:%s",argv[j]);

    if(setenv("GREET","Hello world",0) == -1)
        printf("setenv");

    unsetenv("BYE");

    for(ep = environ;*ep != NULL;ep++)
        puts(*ep);

    exit(EXIT_SUCCESS);

}