/* Code27-1 P467 */
/* ./t_execve ./envargs */
#define _GNU_SOURCE
#include "../lib/tlpi_hdr.h"

int main(int argc,char *argv[])
{
    char *argVec[10];           /* Larger than required */
    char *envVec[] = {"GREET=salut","BYE=adieu",NULL};

    if(argc != 2 || strcmp(argv[1],"--help") == 0)
        printf("%s pathname\n",argv[0]);
    
    /* find '/' */
    argVec[0] = strchr(argv[1],'/');
    if(argVec[0] != NULL)
        argVec[0]++;    /* finded '/' */
    else
        argVec[0] = argv[1];
    
    argVec[1] = "hello world";
    argVec[2] = "goodbye";
    argVec[3] = NULL;       /* List must be NULL-terminated */

    execve(argv[1],argVec,envVec);

    exit(EXIT_FAILURE);     /* If we get here,something went wrong */

}