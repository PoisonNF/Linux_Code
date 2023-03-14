/* Code6-3 P103 */
/* ./display_env.c */

#include "../lib/tlpi_hdr.h"

extern char **environ;

int main(int argc,char *argv[])
{
    char **ep;

    for(ep = environ;*ep != NULL;ep++)
        puts(*ep);
        //printf("%s\n",*ep);
    exit(EXIT_SUCCESS);
}

