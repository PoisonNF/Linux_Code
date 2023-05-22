/* Code52-6 P888 */

#define _GNU_SOURCE
#include <signal.h>
#include <mqueue.h>
#include <fcntl.h>
#include "../lib/tlpi_hdr.h"

#define NOTIFY_SIG SIGUSR1  //�Զ����ź�

static void handler(int sig)
{
    //�ж�sigsuspend()
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

    //������ģʽ����һ��ͨ��������ָ�����Ƶ���Ϣ����
    mqd = mq_open(argv[1],O_RDONLY|O_NONBLOCK);
    if(mqd == (mqd_t)-1)
        printf("mq_open");
    
    //��ȡ��Ϣ���е�mq_msgsize����
    if(mq_getattr(mqd,&attr) == -1)
        printf("mq_getattr");

    //����һ��mq_msgsize��С�Ļ�����
    buffer = malloc(attr.mq_msgsize);
    if(buffer == NULL)
        printf("malloc");

    //����֪ͨ�źţ�SIGUSR1����Ϊ�佨��һ��������
    sigemptyset(&blockMask);
    sigaddset(&blockMask,NOTIFY_SIG);
    if(sigprocmask(SIG_BLOCK,&blockMask,NULL) == -1)
        printf("sigprocmask");
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    if(sigaction(NOTIFY_SIG,&sa,NULL) == -1)
        printf("sigaction");

    //�״ε��� mq_notify()��ע����̽�����Ϣ֪ͨ
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = NOTIFY_SIG;
    if(mq_notify(mqd,&sev) == -1)
        printf("mq_notify");
    
    sigemptyset(&emptyMask);
    for(;;)
    {
        sigsuspend(&emptyMask); //�ȴ����ܵ��ź�,����˵���Ѿ�������һ����Ϣ֪ͨ

        //���� mq_notify()����ע����̽�����Ϣ֪ͨ
        if(mq_notify(mqd,&sev) == -1)
            printf("mq_notify");

        //ִ��һ�� while ѭ���Ӷ����о����ܶ�ض�ȡ��Ϣ�Ա���ն���
        while((numRead = mq_receive(mqd,buffer,attr.mq_msgsize,NULL)) >= 0)
            printf("Read %ld bytes\n",(long)numRead);
        
        if(errno != EAGAIN) //��Ԥ�ϴ���
            printf("mq_receive");
    }
}