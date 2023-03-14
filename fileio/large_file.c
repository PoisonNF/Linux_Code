/* Code5-3 P86 */
/* ./large_file x 10111222333 */
/* ls -l x */

#define _LARGEFILE64_SOURCE
#include <sys/stat.h>
#include <fcntl.h>
#include "../lib/tlpi_hdr.h"

int main(int argc,char *argv[])
{
    int fd;
    off64_t off;
    if(argc != 3 || strcmp(argv[1],"--help") == 0)
        printf("%s pathname offset\n",argv[0]);
    
    fd = open64(argv[1],O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);

    if(fd == -1)
        printf("open64\n");
    
    off = atoll(argv[2]);
    if(lseek64(fd,off,SEEK_SET) == -1)
        printf("lseek64\n");
    
    if(write(fd,"test",4) == -1)
        printf("write\n");
    
    exit(EXIT_SUCCESS);
}