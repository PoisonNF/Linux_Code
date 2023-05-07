/* Code27-3 P470 */
/* which echo 
    ls -l /bin/echo
    echo #PATH

    ./t_execlp echo
    ./t_execlp /bin/echo

*/

#include "../lib/tlpi_hdr.h"

int main(int argc,char *argv[])
{
    if(argc != 2 || strcmp(argv[1],"--help") == 0)
        printf("%s pathname\n",argv[0]);
    
    execlp(argv[1],argv[1],"hello world",(char *)NULL);
    exit(EXIT_FAILURE);
}