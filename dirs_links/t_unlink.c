/* Code18-1 P288*/
/* ./t_unlink /tmp/tfile 1000000 */

#include <sys/stat.h>
#include <fcntl.h>
#include "../lib/tlpi_hdr.h"

#define CMD_SIZE 200
#define BUF_SIZE 1024

int main(int argc,char *argv[])
{
    int fd,j,numBlocks;
    char shellCmd[CMD_SIZE];    /* Command to be passed to system() */
    char buf[BUF_SIZE];         /* Random bytes to write to file */

    if(argc < 2 || strcmp(argv[1],"--help") == 0)
        printf("%s temp-file [num-1kb-blocks] \n",argv[0]);
    
    numBlocks = (argc > 2) ? atoi(argv[2]) :1000000;

    fd = open(argv[1],O_WRONLY|O_CREAT|O_EXCL,S_IRUSR|S_IWUSR);
    if(fd == -1)
        printf("open");
    
    if(unlink(argv[1]) == -1)   /* Remove filename */
        printf("unlink");
    
    for(j=0;j<numBlocks;j++)    /* Write lots of junks to file */
        if(write(fd,buf,BUF_SIZE) != BUF_SIZE)
            printf("partial/failed write");
    
    snprintf(shellCmd,CMD_SIZE,"df -k `dirname %s`",argv[1]);
    system(shellCmd);

    if(close(fd) == -1)
        printf("close");
    
    printf("*********Closed file descriptor \n");

    system(shellCmd);
    exit(EXIT_SUCCESS);
}