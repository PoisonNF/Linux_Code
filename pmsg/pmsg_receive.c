/* Code52-5 P884 */
/*  普通接收    ./pmsg_receive /mq
    非阻塞接收  ./pmsg_receive -n /mq
 */

#include <mqueue.h>
#include <fcntl.h>      //获得O_NONBLOCK的定义
#include "../lib/tlpi_hdr.h"

extern int optind;

static void usageError(const char *progName)
{
    fprintf(stderr,"Usage: %s [-n] name\n",progName);
    fprintf(stderr,"-n      Use O_NONBLOCK flag\n");
    exit(EXIT_SUCCESS);
}

int main(int argc,char *argv[])
{
    int flags,opt;
    mqd_t mqd;
    unsigned int prio;
    void *buffer;
    struct mq_attr attr;
    ssize_t numRead;

    flags = O_RDONLY;

    //命令行参数解析
    while ((opt = getopt(argc,argv,"n")) != -1)
    {
        switch(opt)
        {
            case 'n':flags |= O_NONBLOCK;   break;
            default: usageError(argv[0]);
        }
    }

    //argc小于1,表示没有输入消息队列描述符
    if(optind >= argc)
        usageError(argv[0]);
    
    //打开消息队列
    mqd = mq_open(argv[optind],flags);
    if(mqd == (mqd_t) -1)
        printf("mq_open");
    
    //获取消息队列中的特性
    if(mq_getattr(mqd,&attr) == -1)
        printf("mq_getattr");

    //根据消息队列最大长度初始化buffer
    buffer = malloc(attr.mq_msgsize);
    if(buffer == NULL)
        printf("malloc");

    //从消息队列中读取消息到buffer中
    numRead = mq_receive(mqd,buffer,attr.mq_msgsize,&prio);
    if(numRead == -1)
        printf("mq_receive");
    printf("Read %ld bytes; priority = %u\n",(long)numRead,prio);

    //向标准输出中写入buffer内容
    if(write(STDOUT_FILENO,buffer,numRead) == -1)
        printf("write");
    write(STDOUT_FILENO,"\n",1);    //换行符

    exit(EXIT_SUCCESS);
}

