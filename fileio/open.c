/* Code4-2 open P59*/
/* ./open */
#include <sys/stat.h>
#include <fcntl.h>
#include "../lib/tlpi_hdr.h"

int fd;

int main(int argc,char *argv[])
{
    /* Open existing file for reading */

    fd = open("startup",O_RDONLY);
    if(fd == -1)
        printf("open startup wrong\n");
    
    /* Open new or existing file for reading and writing,truncating 
    to zero bytes;file permissions read+write for owner,nothing for all others */

    fd = open("myfile",O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);
    if(fd == -1)
        printf("open myfile wrong\n");
    
    /* Open new or existing file for writing;writes should always
        append to end of file */
    
    fd = open("w.log",O_WRONLY|O_CREAT|O_TRUNC|O_APPEND,
                        S_IRUSR|S_IWUSR);
    if(fd == -1)
        printf("open w.log wrong\n");

    close(fd);
    return 0;
}