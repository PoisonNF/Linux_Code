/* Code6-2 P100 */
/* ./necho.c necho hello world */
#include "../lib/tlpi_hdr.h"

int main(int argc,char *argv[])
{
    int j;
    for(j = 0; j<argc;j++)
        printf("argv[%d] = %s\n",j,argv[j]);

    exit(EXIT_SUCCESS);

    // char **p;
    // for (p = argv ;*p != NULL;p++)
    //     puts(*p);
}