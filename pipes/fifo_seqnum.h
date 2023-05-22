/* Code44-6 P747 */
#ifndef __FIFO_SEQNUM_H_
#define __FIFO_SEQNUM_H_

#include "../lib/tlpi_hdr.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SERVER_FIFO "/tmp/seqnum_sv"
                    /* Well-known name for server's FIFO */
#define CLIENT_FIFO_TEMPLATE "/tmp/seqnum_cl.%ld"
                    /* Templete for building client FIFO name */
#define CLIENT_FIFO_NAME_LEN (sizeof(CLIENT_FIFO_TEMPLATE) + 20)
                    /* Space required for client FIFO pathname */

struct request  /* Request(client --> server) */
{
    pid_t pid;  /* PID of client */
    int seqLen; /* Length of desired sequence */
};

struct response /* Response(server --> client) */
{
    int seqNum; /* Start of sequence */
};



#endif // !__FIFO_SEQNUM_H_


