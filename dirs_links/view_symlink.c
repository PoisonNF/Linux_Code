/* Code18-4 P306 */
/* touch x
    ln -s x y
    ./view_symlink y
*/

#include <sys/stat.h>
#include <limits.h>
#include "../lib/tlpi_hdr.h"

#define BUF_SIZE PATH_MAX

int main(int argc,char *argv[])
{
    struct stat statbuf;
    char buf[BUF_SIZE];
    ssize_t numBytes;

    if(argc != 2 || strcmp(argv[1],"--help") == 0)
        printf("%s pathname\n",argv[0]);
    
    if(lstat(argv[1],&statbuf) == -1)
        printf("lstat");
    
    if(!S_ISLNK(statbuf.st_mode))
        printf("%s is not a symbolic link",argv[1]);

    numBytes = readlink(argv[1],buf,BUF_SIZE-1);
    if(numBytes == -1)
        printf("readlink");
    
    buf[numBytes] = '\0';       /* Add terminating null bype */
    printf("readlink:%s --> %s \n",argv[1],buf);

    if(realpath(argv[1],buf) == NULL)
        printf("realpath");
    
    printf("realpath:%s --> %s \n",argv[1],buf);

    exit(EXIT_SUCCESS);
}
