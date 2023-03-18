/* Code13-1 P202*/
/*  ./direct_read ./test/x 512
    ./direct_read ./test/x 256
    ./direct_read ./test/x 512 1
    ./direct_read ./test/x 4096 8192 512
    ./direct_read ./test/x 4096 512 256 */

#define _GNU_SOURCE
#include <fcntl.h>
#include <malloc.h>
#include "../lib/tlpi_hdr.h"

int main(int argc,char *argv[])
{
    int fd;
    ssize_t numRead;
    ssize_t numWrite;
    size_t length,alignment;
    off_t offset;
    void *buf;

    if(argc < 3 || strcmp(argv[1],"--help") == 0)
        printf("%s file length [offset [alignment]]\n",argv[0]);
    length = atol(argv[2]);
    offset = (argc > 3)?atol(argv[3]):0;
    alignment = (argc > 4)?atol(argv[4]):4096;

    fd = open(argv[1],O_RDWR|O_CREAT);
    if(fd == -1)
        printf("open write");
        
    if(lseek(fd,0,SEEK_SET) == -1)
        printf("lseek");

    numWrite = write(fd,"111dddd",512);
    if(numWrite == -1)
        printf("write");

    printf("write success %ld",(long)numWrite);
    close(fd);

    fd = open(argv[1],O_RDWR|O_DIRECT|O_CREAT);
    if(fd == -1)
        printf("open");

    buf = (char *)memalign(alignment * 2,length + alignment)+alignment;
    if(buf == NULL)
        printf("memalign");
    
    if(lseek(fd,offset,SEEK_SET) == -1)
        printf("lseek");
    
    numRead = read(fd,buf,length);
    if(numRead == -1)
        printf("read");
    
    printf("Read %ld bytes\n",(long)numRead);

    exit(EXIT_SUCCESS);
}