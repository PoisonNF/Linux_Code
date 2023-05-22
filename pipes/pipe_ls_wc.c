/* Code44-4 P738 */
/* ./pipe_ls_wc
    ls | wc -l
 */

#include <sys/wait.h>
#include "../lib/tlpi_hdr.h"

int main(int argc,char *argv[])
{
    int pfd[2];

    if(pipe(pfd) == -1)
        printf("pipe");
    
    switch(fork())
    {
        case -1:
            printf("fork1");
        
        case 0: /* First child:exec 'ls' to write to pipe */
            if(close(pfd[0]) == -1) /* shutdown read */
                printf("close 1");
            
            if(pfd[1] != STDOUT_FILENO)
            {
                if(dup2(pfd[1],STDOUT_FILENO) == -1)
                    printf("dup2 1");
                if(close(pfd[1]) == -1)
                    printf("close 2");
            }

            execlp("ls","ls",(char *)NULL);
            _exit(EXIT_SUCCESS);
        default: /* Parent falls through to create next child */
            break;
    }

    switch(fork())
    {
        case -1:
            printf("fork2");
        case 0: /* Second child:exec 'wc' to read from pipe */
            if(close(pfd[1]) == -1) /* shutdown write */
                printf("close 3");
            
            if(pfd[0] != STDIN_FILENO)
            {
                if(dup2(pfd[0],STDIN_FILENO) == -1)
                    printf("dup2 2");
                if(close(pfd[0]) == -1)
                    printf("close 4");
            }

            execlp("wc","wc","-l",(char *)NULL);
            _exit(EXIT_SUCCESS);
        default:
            break;           
    }

    /* Parent closes unused file descriptors for pipe ,and wait for children */
    if(close(pfd[0]) == -1)
        printf("close 5");
    if(close(pfd[1]) == -1)
        printf("close 6");
    if(wait(NULL) == -1)
        printf("wait 1");
    if(wait(NULL) == -1)
        printf("wait 2");

    exit(EXIT_SUCCESS);
}