#include "../lib/tlpi_hdr.h"

int main(int argc,char *argv[])
{
    printf("dasdsad");
    fflush(stdout);
    execlp("sleep","sleep","0",(char *)NULL);
}