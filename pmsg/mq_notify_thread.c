/* Code52-7 P890 */

#include <pthread.h>
#include <mqueue.h>
#include <fcntl.h>
#include <signal.h>
#include "../lib/tlpi_hdr.h"

static void notifySetup(mqd_t *mqdp);

static void threadFunc(union sigval sv)
{
    ssize_t numRead;
    mqd_t *mqdp;
    void *buffer;
    struct mq_attr attr;

    mqdp = sv.sival_ptr;

    //得到mq_msgsize
    if(mq_getattr(*mqdp,&attr) == -1)
        printf("mq_getattr");

    //为buffer分配mq_msgsize大小的内存空间
    buffer = malloc(attr.mq_msgsize);
    if(buffer == NULL)
        printf("malloc");

    //设置通知函数
    notifySetup(mqdp);

    //一直从消息队列读数据，保证队列为空
    while((numRead = mq_receive(*mqdp,buffer,attr.mq_msgsize,NULL)) >= 0)
        printf("Read %ld bytes\n",(long)numRead);

    //非意料的错误
    if(errno != EAGAIN)
        printf("mq_receive");
    
    free(buffer);
    pthread_exit(NULL);
}

static void notifySetup(mqd_t *mqdp)
{
    struct sigevent sev;
    sev.sigev_notify = SIGEV_THREAD;
    sev.sigev_notify_function = threadFunc;
    sev.sigev_notify_attributes = NULL;
    sev.sigev_value.sival_ptr = mqdp; //threadFunc()的参数

    if(mq_notify(*mqdp,&sev) == -1)
        printf("mq_notify");
}

int main(int argc,char *argv[])
{
    mqd_t mqd;

    if(argc != 2 || strcmp(argv[1],"--help") == 0)
        printf("%s mq-name\n",argv[0]);

    //打开消息队列
    mqd = mq_open(argv[1],O_RDONLY | O_NONBLOCK);
    if(mqd == (mqd_t) -1)
        printf("mq_open");

    notifySetup(&mqd);  //第一次注册消息通知

    pause();    //等待通知到来启动线程通知
}

