/* Code28-3 P496 */
/*  ./t_clone
    ./t_clone x 带有命令行参数运行程序时，两个进程将共享文件描述符表
 */

#define _GNU_SOURCE
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sched.h>
#include "../lib/tlpi_hdr.h"
#include "../lib/error_functions.h"

//#ifdef CHILD_SIG
#define CHILD_SIG SIGUSR1
//#endif // CHILD_SIG

static int childFunc(void *arg)
{
    if(close(*((int *)arg)) == -1)
    {
        printf("close");
        _exit(EXIT_FAILURE);
    }


    return 0 ;
}

int main(int argc,char *argv[])
{
    const int STACK_SIZE = 65535;   /* Stack size for cloned child */
    char *stack;
    char *stackTop;
    int s,fd,flags;

    fd = open("./clone_fd",O_RDWR | O_CREAT);
    if(fd == -1)
        printf("open");
    
    flags = (argc > 1)?CLONE_FILES : 0;

    //Allocate stack for child
    stack = malloc(STACK_SIZE);
    if(stack == NULL)
        printf("malloc");
    stackTop = stack + STACK_SIZE;

    if(CHILD_SIG != 0 && CHILD_SIG != SIGCHLD)
        if(signal(CHILD_SIG,SIG_IGN) == SIG_ERR)
            printf("signal");

    if(clone(childFunc,stackTop,flags | CHILD_SIG ,(void *)&fd) == -1)
        printf("clone");
    
    if(waitpid(-1,NULL,(CHILD_SIG != SIGCHLD) ? __WCLONE : 0) == -1)
        printf("waitpid");
    printf("child has terminated\n");

    //Did close() of file descriptor in child affect parent?

    s = write(fd,"x",1);
    if(s == -1 && errno == EBADF)
        printf("file descriptor %d has been closed\n",fd);
    else if(s == -1)
        printf("write() on file descriptor %d failed"
                "unexpextedly (%s)\n",fd,strerror(errno));
    else
        printf("write() on file descriptor %d succeeded\n",fd);
}