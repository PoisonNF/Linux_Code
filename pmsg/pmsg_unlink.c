/* Code52-1 P877 */

#include <mqueue.h>
#include "../lib/tlpi_hdr.h"

int main(int argc,char *argv[])
{
    if(argc != 2 || strcmp(argv[1],"--help") == 0)
        printf("%s mq-name\n",argv[0]);

    if(mq_unlink(argv[1]) == -1)
        printf("mq_unlink");
    
    exit(EXIT_SUCCESS);
}