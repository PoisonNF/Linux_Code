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

    //�õ�mq_msgsize
    if(mq_getattr(*mqdp,&attr) == -1)
        printf("mq_getattr");

    //Ϊbuffer����mq_msgsize��С���ڴ�ռ�
    buffer = malloc(attr.mq_msgsize);
    if(buffer == NULL)
        printf("malloc");

    //����֪ͨ����
    notifySetup(mqdp);

    //һֱ����Ϣ���ж����ݣ���֤����Ϊ��
    while((numRead = mq_receive(*mqdp,buffer,attr.mq_msgsize,NULL)) >= 0)
        printf("Read %ld bytes\n",(long)numRead);

    //�����ϵĴ���
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
    sev.sigev_value.sival_ptr = mqdp; //threadFunc()�Ĳ���

    if(mq_notify(*mqdp,&sev) == -1)
        printf("mq_notify");
}

int main(int argc,char *argv[])
{
    mqd_t mqd;

    if(argc != 2 || strcmp(argv[1],"--help") == 0)
        printf("%s mq-name\n",argv[0]);

    //����Ϣ����
    mqd = mq_open(argv[1],O_RDONLY | O_NONBLOCK);
    if(mqd == (mqd_t) -1)
        printf("mq_open");

    notifySetup(&mqd);  //��һ��ע����Ϣ֪ͨ

    pause();    //�ȴ�֪ͨ���������߳�֪ͨ
}

