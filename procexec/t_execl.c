/* Code 27-5 P471 */
/* echo $USER $SHELL */

#include <stdlib.h>
#include "../lib/tlpi_hdr.h"

int main(int argc,char *argv[])
{
    printf("Initial value of USER: %s\n",getenv("USER"));
    if(putenv("USER=britta") != 0)
        printf("putenv");

    execl("/usr/bin/printenv","printenv","USER","SHELL",(char *)NULL);
    exit(EXIT_FAILURE);
}