/* Code44-3 P735 */
/* ./pipe_sync 4 2 6 */

#include "../time/curr_time.h"
#include "../lib/tlpi_hdr.h"

int main(int argc,char *argv[])
{
    int pfd[2];
    int j,dummy;

    if(argc < 2 || strcmp(argv[1],"--help") == 0)
        printf("%s sleep-time...\n",argv[0]);

    setbuf(stdout,NULL);    /* Make stdout unbuffered */

    printf("%s Parent start\n",currTime("%T"));

    if(pipe(pfd) == -1)
        printf("pipe");

    for(j = 1;j < argc; j++)
    {
        switch(fork())
        {
            case -1:
                printf("fork %d",j);
            case 0: /* Child */
                if(close(pfd[0]) == -1) /* Read end is unused */
                    printf("close");

                sleep(atoi(argv[j]));
                printf("%s Child %d (PID = %ld) closing pipe\n",
                        currTime("%T"),j,(long)getpid());

                if(close(pfd[1]) == -1)
                    printf("close");
                
                _exit(EXIT_SUCCESS);

            default:
                break;
        }
    }

    if(close(pfd[1]) == -1)
        printf("close");

    if(read(pfd[0],&dummy,1) != 0)
        printf("parent didn't get EOF");
    printf("%s Parent ready to go\n",currTime("%T"));

    exit(EXIT_SUCCESS);

}