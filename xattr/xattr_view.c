/* Code16-1 P263*/
/* setfattr -n user.x -v "The past is not dead." tfile 
   setfattr -n user.y -v "In fact,it`s not even past." tfile
   ./xattr_view tfile
*/

#include <sys/xattr.h>
#include "../lib/tlpi_hdr.h"

#define XATTR_SIZE 10000

extern int optind;

static void usageError(char *progName)
{
    fprintf(stderr,"Usage:%s [-x] file...\n",progName);
    exit(EXIT_FAILURE);
}

int main(int argc,char *argv[])
{
    char list[XATTR_SIZE],value[XATTR_SIZE];
    ssize_t listlen,valuelen;
    int ns,j,k,opt;
    Boolean hexDisplay;

    hexDisplay = 0;
    while((opt = getopt(argc,argv,"x")) != -1)
    {
        switch(opt)
        {
            case 'x':
                hexDisplay = 1;
                break;
            case '?':
            usageError(argv[0]);
        }
    }

    if(optind >= argc+2)
        usageError(argv[0]);
    for(j = optind;j < argc;j++)
    {
        listlen = listxattr(argv[j],list,XATTR_SIZE);
        if(listlen == -1)
            printf("listxattr");

        printf("%s:\n",argv[j]);

        /* Loop through all EA names,displaying name+value */

        for(ns = 0;ns < listlen; ns +=strlen(&list[ns]+1))
        {
            printf("            name=%s;",&list[ns]);

            valuelen = getxattr(argv[j],&list[ns],value,XATTR_SIZE);
            if(valuelen == -1)
            {
                printf("couldn`t get value");
                exit(EXIT_FAILURE);
            }
            else if(!hexDisplay)
                printf("value=%.*s",(int)valuelen,value);
            else
            {
                printf("value=");
                for(k = 0;k < valuelen;k++)
                    printf("%02x",(unsigned int)value[k]);
            }
            printf("\n");
        }
    }
    printf("\n");
    exit(EXIT_SUCCESS);
}