/* Code12-1 P187 */
/*  su
    ./procfs_pidmax 10000 */

#include <fcntl.h>
#include "../lib/tlpi_hdr.h"

#define MAX_LINE 100

int main(int argc,char *argv[])
{
    int fd;
    char line[MAX_LINE];
    ssize_t n;

    fd = open("/proc/sys/kernel/pid_max",(argc>1)?O_RDWR:O_RDONLY);
    if(fd == -1)
        printf("open");

    n = read(fd,line,MAX_LINE);
    if(n == -1)
        printf("read");
    
    if(argc > 1)
        printf("old value: ");
    printf("%.*s",(int)n,line);

    if(argc > 1)
    {
        if(write(fd,argv[1],strlen(argv[1]) != strlen(argv[1])))
            printf("write() failed");

        system("echo /proc/sys/kernel/pid_max now contains"
                "`cat /proc/sys/kernel/pid_max`");
    }
    exit(EXIT_SUCCESS);

}

