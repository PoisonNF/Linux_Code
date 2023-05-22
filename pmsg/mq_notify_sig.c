/* Code52-6 P888 */

#define _GNU_SOURCE
#include <signal.h>
#include <mqueue.h>
#include <fcntl.h>
#include "../lib/tlpi_hdr.h"

#define NOTIFY_SIG SIGUSR1  //自定义信号

static void handler(int sig)
{
    //中断sigsuspend()
}

int main(int argc,char *argv[])
{
    struct sigevent sev;
    mqd_t mqd;
    struct mq_attr attr;
    void *buffer;
    ssize_t numRead;
    sigset_t blockMask,emptyMask;
    struct sigaction sa;

    if(argc != 2 || strcmp(argv[1],"--help") == 0)
        printf("%s mq-name\n",argv[0]);

    //非阻塞模式打开了一个通过命令行指定名称的消息队列
    mqd = mq_open(argv[1],O_RDONLY|O_NONBLOCK);
    if(mqd == (mqd_t)-1)
        printf("mq_open");
    
    //获取消息队列的mq_msgsize特性
    if(mq_getattr(mqd,&attr) == -1)
        printf("mq_getattr");

    //申请一个mq_msgsize大小的缓冲区
    buffer = malloc(attr.mq_msgsize);
    if(buffer == NULL)
        printf("malloc");

    //阻塞通知信号（SIGUSR1）并为其建立一个处理器
    sigemptyset(&blockMask);
    sigaddset(&blockMask,NOTIFY_SIG);
    if(sigprocmask(SIG_BLOCK,&blockMask,NULL) == -1)
        printf("sigprocmask");
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    if(sigaction(NOTIFY_SIG,&sa,NULL) == -1)
        printf("sigaction");

    //首次调用 mq_notify()来注册进程接收消息通知
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = NOTIFY_SIG;
    if(mq_notify(mqd,&sev) == -1)
        printf("mq_notify");
    
    sigemptyset(&emptyMask);
    for(;;)
    {
        sigsuspend(&emptyMask); //等待接受到信号,返回说明已经发生了一个消息通知

        //调用 mq_notify()重新注册进程接收消息通知
        if(mq_notify(mqd,&sev) == -1)
            printf("mq_notify");

        //执行一个 while 循环从队列中尽可能多地读取消息以便清空队列
        while((numRead = mq_receive(mqd,buffer,attr.mq_msgsize,NULL)) >= 0)
            printf("Read %ld bytes\n",(long)numRead);
        
        if(errno != EAGAIN) //非预料错误
            printf("mq_receive");
    }
}