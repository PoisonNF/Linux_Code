/* Code52-2 P879 */

#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../lib/tlpi_hdr.h"

static void usageError(const char *progName)
{
    fprintf(stderr,"Usage: %s [-cx] [-m maxmsg] [-s msgsize] mq-name"
            "[octal-perms]\n",progName);

    exit(EXIT_FAILURE);
}

extern char *optarg;
extern int optind;

int main(int argc,char *argv[])
{
    int flags,opt;
    mode_t perms;
    mqd_t mqd;
    struct mq_attr attr,*attrp;

    attrp = NULL;
    attr.mq_maxmsg = 50;
    attr.mq_msgsize = 2048;
    flags = O_RDWR;

    while((opt = getopt(argc,argv,"cm:s:x")) != -1)
    {
        switch (opt)
        {
            case 'c':   //新建队列
                flags |= O_CREAT;
                break;
            
            case 'm':   //最大消息数量
                attr.mq_maxmsg = atoi(optarg);
                break;
            
            case 's':   //每个消息的最大大小
                attr.mq_msgsize = atoi(optarg);
                break;
            
            case 'x':   //保证是独占的
                flags |= O_EXCL;
                break;

            default:
                usageError(argv[0]);
        }
    }

    if(optind >= argc)
        usageError(argv[0]);

    perms = (argc <= optind + 1)?(S_IRUSR | S_IWUSR): atoi(argv[optind + 1]);

    mqd = mq_open(argv[optind],flags,perms,attrp);
    if(mqd == (mqd_t) -1)
        printf("mq_open");

    exit(EXIT_SUCCESS);
}