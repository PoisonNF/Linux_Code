/* Code44-8 P750 */
/* fifo_seqnum_server &
    fifo_seqnum_client 3
    fifo_seqnum_client 3
    fifo_seqnum_client
 */

#include "fifo_seqnum.h"

static char clientFifo[CLIENT_FIFO_NAME_LEN];

static void removeFifo(void)
{
    unlink(clientFifo);
}

int main(int argc,char *argv[])
{
    int serverFd,clientFd;

    struct request req;
    struct response resp;

    if(argc > 1 && strcmp(argv[1],"--help") == 0)
        printf("%s [seq-len...]\n",argv[0]);

    /* Create our FIFO (before sending request,to avoid a race) */
    umask(0);
    snprintf(clientFifo,CLIENT_FIFO_NAME_LEN,CLIENT_FIFO_TEMPLATE,
            (long)getpid());
    if(mkfifo(clientFifo,S_IRUSR|S_IWUSR|S_IWGRP) == -1
            && errno != EEXIST);
        printf("mkfifo %s",clientFifo);

    if(atexit(removeFifo) != 0)
        printf("atexit");

    /* Construct request message,open server FIFO,and send request */
    req.pid = getpid();
    req.seqLen = (argc > 1)?atoi(argv[1]):1;

    serverFd = open(SERVER_FIFO,O_WRONLY);
    if(serverFd == -1)
        printf("open %s",SERVER_FIFO);

    if(write(serverFd,&req,sizeof(struct request)) !=
                sizeof(struct request))
        printf("Can't write to server");

    clientFd = open(clientFifo,O_RDONLY);
    if(clientFd == -1)
        printf("open %s",clientFifo);
    
    if(read(clientFd,&resp,sizeof(struct response)) !=
            sizeof(struct response))
        printf("Can't read response from server");
    
    printf("%d\n",resp.seqNum);

    exit(EXIT_SUCCESS);
}