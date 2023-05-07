/* Code24-2 P434 */
/* ./t_vfork */

#include "../lib/tlpi_hdr.h"

int main(int argc,char *argv[])
{
    int istack = 222;

    switch (vfork())
    {
    case -1:
        printf("vfork");
        break;
    
    case 0:
        sleep(1);       /* Even if we sleep for while */
        write(STDOUT_FILENO,"Child executing\n",16);
        istack *= 3;
        _exit(EXIT_SUCCESS);
    default:
        write(STDOUT_FILENO,"Parent executing\n",17);
        printf("istack=%d\n",istack);
        exit(EXIT_SUCCESS);
        break;
    }
}
