/* Code25-2 P445 */
/*  ./fork_stdio_buf

    ./fork_stdio_buf > a
    cat a
 */

#include "../lib/tlpi_hdr.h"

int main(int argc,char *argv[])
{
    printf("Hello world\n");
    write(STDOUT_FILENO,"Ciao\n",5);

    if(fork() == -1)
        printf("fork");
    
    exit(EXIT_SUCCESS);
}