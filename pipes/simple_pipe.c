/* Code44-2 P734 */
/* ./simple_pipe 'The full name of STM32 is the STMicroelectronics 32-bit microcontroller series products.' */

#include <sys/wait.h>
#include "../lib/tlpi_hdr.h"

#define BUF_SIZE 10

int main(int argc,char *argv[])
{
    int pfd[2]; /* Pipe file descriptors */
    char buf[BUF_SIZE];
    ssize_t numRead;

    if(argc != 2 || strcmp(argv[1],"--help") == 0)
        printf("%s string\n",argv[0]);

    if(pipe(pfd) == -1) /* Create the pipe */
        printf("pipe");

    switch(fork())
    {
        case -1:
            printf("fork");
        case 0:    /* Child - read from pipe */
            if(close(pfd[1]) == -1) /* Write end is unused */
                printf("close -child");

            for(;;)
            {
                numRead = read(pfd[0],buf,BUF_SIZE);
                if(numRead == -1)
                    printf("read");
                if(numRead == 0)
                    break;  /* End of file */
                if(write(STDOUT_FILENO,buf,numRead) != numRead)
                    printf("child-partial/failed write");        
            }

            write(STDOUT_FILENO,"\n",1);
            if(close(pfd[0]) == -1)
                printf("close");
            _exit(EXIT_SUCCESS);
        
        default:    /* Parent - writes to pipe */
            if(close(pfd[0]) == -1) /* Read end is unused */
                printf("close - parent");
            
            if(write(pfd[1],argv[1],strlen(argv[1])) != strlen(argv[1]));
                printf("parent - partial/failed write");

            if(close(pfd[1]) == -1) /* Child will see EOF */
                printf("close");
            
            wait(NULL);
            exit(EXIT_SUCCESS);
    }

}