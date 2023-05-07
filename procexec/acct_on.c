/* Code28-1 P488 */

#define _DEFAULT_SOURCE
#include <unistd.h>
#include "../lib/tlpi_hdr.h"

int main(int argc, char *argv[])
{
    if(argc > 2 || (argc > 1 && strcmp(argv[1],"-help") == 0))
        printf("%s [file]\n",argv[0]);

    if(acct(argv[1]) == -1)
        printf("acct");

    printf("Process accounting %s\n",
            (argv[1] == NULL)?"disable":"enable");
    exit(EXIT_SUCCESS);
}
