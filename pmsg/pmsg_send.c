/* Code52-4 P883 */
/* ./pmsg_send /mq xxxx prio */

#include <mqueue.h>
#include <fcntl.h>  /* For definition of O_NONBLOCK */
#include "../lib/tlpi_hdr.h"

extern int optind;

static void usageError(const char *progName)
{
    fprintf(stderr,"Usage:%s [-n] name msg [prio]\n",progName);
    fprintf(stderr,"-n          Use O_NONBLOCK flag\n");
    exit(EXIT_FAILURE);
}

int main(int argc,char *argv[])
{
    int flags,opt;
    mqd_t mqd;
    unsigned int prio;

    flags = O_WRONLY;
    
    //�����в�����ȡ
    while((opt = getopt(argc,argv,"n")) != -1)
    {
        switch(opt)
        {
            case 'n': flags |= O_NONBLOCK; break;
            default : usageError(argv[0]);
        }
    }

    //�����в���С�ڵ���2��������Ϊû����Ϣ����
    if(optind + 1 >= argc)
        usageError(argv[0]);

    //������Ϣ����
    mqd = mq_open(argv[optind],flags);
    if(mqd == (mqd_t) -1)
        printf("mq_open");
    
    //���ȼ���ȡ����argv[3]��
    prio = (argc > optind + 2)? atoi(argv[optind + 2]): 0;

    //������Ϣ�������У���Ϣ������argv[2]��
    if(mq_send(mqd,argv[optind + 1],strlen(argv[optind + 1]),prio) == -1)
        printf("mq_send");
    
    exit(EXIT_SUCCESS);
}