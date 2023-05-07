/* Code24-2 P429 */
/* ./fork_file_sharing */

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "../lib/tlpi_hdr.h"

int main(int argc,char *argv[])
{
    int fd,flags;
    char template[] = "/tmp/testXXXXXX";

    setbuf(stdout,NULL);    /* Disable buffering of stdout */

    fd = mkstemp(template);
    if(fd == -1)
        printf("mkstemp");
    
    printf("File offset before fork():%lld\n",
            (long long)lseek(fd,0,SEEK_CUR));
        
    flags = fcntl(fd,F_GETFL);
    if(flags == -1)
        printf("fcntl-F_GETFL");
    
    printf("O_APPEND flag before fork() is:%s\n",
            (flags & O_APPEND)? "on":"off");
    
    switch (fork())
    {
    case -1:
        printf("fork");
        break;

    case 0:     /* Child change file offset and status flags */
        if(lseek(fd,1000,SEEK_SET) == -1);
            printf("lseek");
        
        flags = fcntl(fd,F_GETFL);
        if(flags == -1)
            printf("fcntl");
        flags |= O_APPEND;
        if(fcntl(fd,F_SETFL,flags) == -1)
            printf("fcntl-F_SETFL");
        
        _exit(EXIT_SUCCESS);
    
    default:    /* Parent can see file change made by child */
        if(wait(NULL) == -1)
            printf("wait");
        printf("Child has exited\n");

        printf("File offset in parent:%lld\n",
            (long long)lseek(fd,0,SEEK_CUR));
        
        flags = fcntl(fd,F_GETFL);
        if(flags == -1)
            printf("fcntl");
        printf("O_APPEND flag in parent is:%s\n",
            (flags & O_APPEND)? "on": "off");
        exit(EXIT_SUCCESS);
    }

}