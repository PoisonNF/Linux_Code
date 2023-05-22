/* Code52-5 P884 */
/*  ��ͨ����    ./pmsg_receive /mq
    ����������  ./pmsg_receive -n /mq
 */

#include <mqueue.h>
#include <fcntl.h>      //���O_NONBLOCK�Ķ���
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

    //�����в�������
    while ((opt = getopt(argc,argv,"n")) != -1)
    {
        switch(opt)
        {
            case 'n':flags |= O_NONBLOCK;   break;
            default: usageError(argv[0]);
        }
    }

    //argcС��1,��ʾû��������Ϣ����������
    if(optind >= argc)
        usageError(argv[0]);
    
    //����Ϣ����
    mqd = mq_open(argv[optind],flags);
    if(mqd == (mqd_t) -1)
        printf("mq_open");
    
    //��ȡ��Ϣ�����е�����
    if(mq_getattr(mqd,&attr) == -1)
        printf("mq_getattr");

    //������Ϣ������󳤶ȳ�ʼ��buffer
    buffer = malloc(attr.mq_msgsize);
    if(buffer == NULL)
        printf("malloc");

    //����Ϣ�����ж�ȡ��Ϣ��buffer��
    numRead = mq_receive(mqd,buffer,attr.mq_msgsize,&prio);
    if(numRead == -1)
        printf("mq_receive");
    printf("Read %ld bytes; priority = %u\n",(long)numRead,prio);

    //���׼�����д��buffer����
    if(write(STDOUT_FILENO,buffer,numRead) == -1)
        printf("write");
    write(STDOUT_FILENO,"\n",1);    //���з�

    exit(EXIT_SUCCESS);
}

