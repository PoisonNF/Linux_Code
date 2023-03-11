/* Code4-3 P70 */
/*  touch tfile
    ./seek_io tfile s100000 wabc
    ls -l tfile
    ./seek_io tfile s10000 R5
 */
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "../lib/tlpi_hdr.h"

int main(int argc,char* argv[])
{
    size_t len;
    off_t offset;
    int fd,ap,j;
    char *buf;
    ssize_t numRead,numWritten;

    if(argc < 3 || strcmp(argv[1],"--help") == 0 )
        printf("%s file wrong\n",argv[1]);
    
    fd = open(argv[1],O_RDWR|O_CREAT,
                S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
    
    if(fd == -1)
        printf("open wrong\n");
    
    for(ap = 2;ap < argc;ap++)
    {
        switch (argv[ap][0])
        {
        case 'r': /* Display bytes at current offset,as text */
        case 'R': /* Display bytes at current offset,in hex */
            len = getLong(&argv[ap][1],GN_ANY_BASE,argv[ap]);
            buf = malloc(len);
            if(buf == NULL)
                printf("malloc\n");
            
            numRead = read(fd,buf,len);
            if(numRead == -1)
                printf("read\n");
            
            if(numRead == 0)
                printf("%s: end-of-file\n",argv[ap]);
            else
            {
                printf("%s: ",argv[ap]);
                for(j = 0;j < numRead;j++)
                {
                    if(argv[ap][0] == 'r')
                        /* printf text */
                        printf("%c",isprint((unsigned char) buf[j])?
                                        buf[j]:'?');
                    else
                        /* printf hex */
                        printf("%02x",(unsigned int) buf[j]);
                }
                printf("\n");
            }
            free(buf);
            break;

        case 'w': /* Write string at current offset */
            numWritten = write(fd,&argv[ap][1],strlen(&argv[ap][1]));
            if(numWritten == -1)
                printf("write\n");
            printf("%s: wrote %ld bytes\n",argv[ap],(long)numWritten);
            break;

        case 's': /* Change file offset */
            offset = getLong(&argv[ap][1],GN_ANY_BASE,argv[ap]);
            if(lseek(fd,offset,SEEK_SET) == -1)
                printf("lseek");
            printf("%s: seek successed\n",argv[ap]);
            break;

        default:
            printf("Argument must start with [rRws] : %s\n",argv[ap]);
        }
    }

    exit(EXIT_SUCCESS);
}
